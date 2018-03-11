#include "key_sequence_tool.h"
#include <tools/pcb_tool.h>
#include <tool/tool_interactive.h>
#include <pcb_base_frame.h>

#include <wx/log.h>

#include <class_draw_panel_gal.h>
#include <view/view_controls.h>
#include <view/view.h>
#include <tool/tool_manager.h>
#include <board_commit.h>

// For frame ToolID values
#include <pcbnew_id.h>

// For action icons
#include "pcb_actions.h"

#include <vector>
#include <map>
#include <string>

#include <tool/tool_manager.h>

/*
 * Tool-specific action defintions
 */

TOOL_ACTION PCB_ACTIONS::keySequenceCollect(
        "pcbnew.KeySequence.Collect",
        AS_GLOBAL, MD_CTRL + WXK_SPACE,
        _( "Move item left" ), _( "Select and move item left" ), NULL, AF_NOTIFY);

//KEY_SEQUENCE::KEY_SEQUENCE( )
//{
//
//}

//KEY_SEQUENCE::KEY_SEQUENCE( std::vector<int> aKeySequence):
//    m_keySequence( aKeySequence )
//{
//}

//KEY_SEQUENCE::KEY_SEQUENCE( std::string aKeySequence)
//{
//    for( auto c : aKeySequence )
//    {
//        m_keySequence.push_back( (int) c );
//    }
//}
//
//KEY_SEQUENCE::~KEY_SEQUENCE()
//{
//
//}
//
//std::string KEY_SEQUENCE::GetKeySequenceStr( )
//{
//    std::string s;
//
//    for( auto i : m_keySequence )
//    {
//        s.push_back( (char) i );
//    }
//
//    return s;
//}
//
//void KEY_SEQUENCE::push_back( int aKey )
//{
//    m_keySequence.push_back( aKey );
//}
//
//void KEY_SEQUENCE::clear()
//{
//    m_keySequence.clear();
//}
//
//int KEY_SEQUENCE::size()
//{
//    return m_keySequence.size();
//}
//
//int KEY_SEQUENCE::back()
//{
//    return m_keySequence.back();
//}
//
//std::vector<int>::iterator KEY_SEQUENCE::begin()
//{
//    return m_keySequence.begin();
//}
//

std::string KEY_SEQUENCE_TOOL::intVectorToStr( std::vector<int>& aVector )
{
    std::string s;

    for( auto i : aVector )
    {
        s.push_back( (char) i );
    }

    return s;

}

// Key sequence implementation
KEY_SEQUENCE_TOOL::KEY_SEQUENCE_TOOL():
    PCB_TOOL( "pcbnew.KeySequence" )
{

}


bool KEY_SEQUENCE_TOOL::Init()
{
    //m_sequenceAction.insert( std::make_pair({(int)'p', (int)'p'}, "pcbnew.EditorControl.placeModule") );
    return true;

}

void KEY_SEQUENCE_TOOL::Reset( RESET_REASON )
{

}


int KEY_SEQUENCE_TOOL::collect(const TOOL_EVENT& aEvent)
{
    auto& frame = *getEditFrame<PCB_EDIT_FRAME>();

    Activate();
    wxString line = "Key Sequence :";
    frame.DisplayToolMsg(line);
    m_collectedKeys.clear();

    std::string tool_action_to_launch;
    int matches = 0;

    wxLogDebug( "Started key sequence tool" );
    while( OPT_TOOL_EVENT evt = Wait() )
    {
        wxLogDebug( "Running event loop" );
        wxLogDebug( wxString::Format( "Event keyCode : %c", evt->KeyCode() ) );
        wxLogDebug( wxString::Format( "EventFormat : %s", evt->Format().c_str() ) );
        if( evt->IsCancel() )
        {
            wxLogDebug( "Tool canceled" );
            m_collectedKeys.clear();
            break;
        }
        else if( evt->IsKeyPressed() )
        {
            wxLogDebug( "Button pressed" );
            m_collectedKeys.push_back( evt->KeyCode() ); 
            wxLogDebug( wxString::Format( "Collected keyCode: %c", (char)m_collectedKeys.back() ) );

            line += char( m_collectedKeys.back() );
            frame.DisplayToolMsg( line);

            matches = 0;

            //Check the collected sequence agianst the list of tool actions
            for( auto it : m_sequenceAction )
            {
                auto key_sequence = it.first;
                int minLength = std::min( key_sequence.size(), m_collectedKeys.size() );

                //Run first action that matches
                if( std::equal(key_sequence.begin(), key_sequence.begin() + minLength, m_collectedKeys.begin() ) )
                {
                    wxLogDebug( "Found matching sequence" );
                    matches++;
                    if( key_sequence == m_collectedKeys )
                    {
                        tool_action_to_launch = m_sequenceAction[key_sequence];
                        break;
                    }

                }
            }
            
            if( tool_action_to_launch.size() != 0 || matches == 0)
            {
                break;
            }
        }
        else
        {
            wxLogDebug( "Event not handled" );

        }
        wxLogDebug( wxString::Format( "Collected characters %s", intVectorToStr(m_collectedKeys) ) );
    }




    wxLogDebug(line);
    frame.DisplayToolMsg( wxEmptyString );

    if( tool_action_to_launch.size() != 0 )
    {
        m_toolMgr->RunAction(tool_action_to_launch);
        wxLogDebug( wxString::Format( "Running tool : %s", tool_action_to_launch ) );
    }
    else
    {
        wxLogDebug( "Exited key sequence tool" );
        m_collectedKeys.clear();
    }
    return 0;


}


void KEY_SEQUENCE_TOOL::setTransitions( )
{
    Go( &KEY_SEQUENCE_TOOL::collect, PCB_ACTIONS::keySequenceCollect.MakeEvent() );
}
