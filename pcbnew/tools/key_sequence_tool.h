/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013-2017 CERN
 * @author Johannes Wågen <johannes@wagen.no>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef __KEY_SEQUENCE_H
#define __KEY_SEQUENCE_H

#include <tool/tool_interactive.h>
#include <tools/pcb_tool.h>
#include "pcb_actions.h"
#include <vector>
#include <map>
#include <string>

//class KEY_SEQUENCE : std::vector<int>
//{
//public:
//    KEY_SEQUENCE();
//    //KEY_SEQUENCE( std::vector<int> aKeySequence);
//    KEY_SEQUENCE( std::string aKeySequence);
//    ~KEY_SEQUENCE();
//
//    std::string GetKeySequenceStr( );
//
//    void push_back( int aKey );
//
//    void clear();
//    int size();
//    int back();
//    std::vector<int>::iterator begin();
//private:
//    std::vector<int> m_keySequence;
//};


class KEY_SEQUENCE_TOOL : public PCB_TOOL
{
public:
    KEY_SEQUENCE_TOOL();

    void Reset( RESET_REASON aReason) override;

    bool Init() override;

    void setTransitions() override;


   int collect(const TOOL_EVENT& aEvent);

    
private:

   //std::vector<int> m_collectedKeys;
   std::map<std::vector<int>, std::string> m_sequenceAction =
   {
       {{(int)'p',(int)'t'}, "pcbnew.InteractiveRouter.SingleTrack"},
       {{(int)'p',(int)'a'}, "pcbnew.InteractiveRouter.SingleTrack"},
       {{(int)'p',(int)'d'}, "pcbnew.InteractiveRouter.DiffPair"}
   };
   std::string intVectorToStr( std::vector<int>& aVector );
   
   //std::map<std::vector<int>, std::string> m_sequenceAction;

   std::vector<int> m_collectedKeys;


};
#endif
