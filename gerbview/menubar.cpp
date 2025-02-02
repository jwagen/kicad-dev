/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2017 Jean-Pierre Charras, jp.charras at wanadoo.fr
 * Copyright (C) 2009-2013 Wayne Stambaugh <stambaughw@verizon.net>
 * Copyright (C) 1992-2017 KiCad Developers, see AUTHORS.txt for contributors.
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

/**
 * @file gerbview/menubar.cpp
 * @brief (Re)Create the main menubar for GerbView
 */


#include <kiface_i.h>
#include <pgm_base.h>

#include "gerbview_frame.h"
#include "gerbview_id.h"
#include "hotkeys.h"
#include <menus_helpers.h>


void GERBVIEW_FRAME::ReCreateMenuBar()
{
    // Create and try to get the current menubar
    wxMenuBar* menuBar = GetMenuBar();
    wxString   text;

    if( !menuBar )
        menuBar = new wxMenuBar();

    // Delete all existing menus so they can be rebuilt.
    // This allows language changes of the menu text on the fly.
    menuBar->Freeze();

    while( menuBar->GetMenuCount() )
        delete menuBar->Remove( 0 );

    // Recreate all menus:

    // Menu File:
    wxMenu* fileMenu = new wxMenu;

    // Open Gerber file(s)
    AddMenuItem( fileMenu, wxID_FILE,
                 _( "Open &Gerber File(s)..." ),
                 _( "Open Gerber file(s) on the current layer. Previous data will be deleted" ),
                 KiBitmap( load_gerber_xpm ) );

    // Open Excellon drill file(s)
    AddMenuItem( fileMenu, ID_GERBVIEW_LOAD_DRILL_FILE,
                 _( "Open &Excellon Drill File(s)..." ),
                 _( "Open Excellon drill file(s) on the current layer. Previous data will be deleted" ),
                 KiBitmap( gerbview_drill_file_xpm ) );

    // Open Gerber job files
    AddMenuItem( fileMenu, ID_GERBVIEW_LOAD_JOB_FILE,
                 _( "Open Gerber &Job File..." ),
                 _( "Open a Gerber job file, and it's associated gerber files depending on the job" ),
                 KiBitmap( gerber_job_file_xpm ) );

    // Open Zip archive files
    AddMenuItem( fileMenu, ID_GERBVIEW_LOAD_ZIP_ARCHIVE_FILE,
                 _( "Open &Zip Archive File..." ),
                 _( "Open a zipped archive (Gerber and Drill) file" ),
                 KiBitmap( zip_xpm ) );

    // Recent gerber files
    static wxMenu* openRecentGbrMenu;

    // Add this menu to list menu managed by m_fileHistory
    // (the file history will be updated when adding/removing files in history
    if( openRecentGbrMenu )
        Kiface().GetFileHistory().RemoveMenu( openRecentGbrMenu );

    openRecentGbrMenu = new wxMenu();

    Kiface().GetFileHistory().UseMenu( openRecentGbrMenu );
    Kiface().GetFileHistory().AddFilesToMenu();

    AddMenuItem( fileMenu, openRecentGbrMenu, wxID_ANY,
                 _( "Open &Recent Gerber File" ),
                 _( "Open a recently opened Gerber file" ),
                 KiBitmap( recent_xpm ) );

    // Recent drill files
    static wxMenu* openRecentDrlMenu;

    if( openRecentDrlMenu )
        m_drillFileHistory.RemoveMenu( openRecentDrlMenu );

    openRecentDrlMenu = new wxMenu();
    m_drillFileHistory.UseMenu( openRecentDrlMenu );
    m_drillFileHistory.AddFilesToMenu( );
    AddMenuItem( fileMenu, openRecentDrlMenu, wxID_ANY,
                 _( "Open Recent Excellon Dri&ll File" ),
                 _( "Open a recently opened Excellon drill file" ),
                 KiBitmap( recent_xpm ) );

    // Recent job files
    static wxMenu* openRecentJobFilesMenu;

    if( openRecentJobFilesMenu )
        m_jobFileHistory.RemoveMenu( openRecentJobFilesMenu );

    openRecentJobFilesMenu = new wxMenu();
    m_jobFileHistory.UseMenu( openRecentJobFilesMenu );
    m_jobFileHistory.AddFilesToMenu( );
    AddMenuItem( fileMenu, openRecentJobFilesMenu, wxID_ANY,
                 _( "Open Recent Gerber &Job File" ),
                 _( "Open a recently opened gerber job file" ),
                 KiBitmap( recent_xpm ) );

    // Recent Zip archive
    static wxMenu* openRecentZipArchiveMenu;

    if( openRecentZipArchiveMenu )
        m_zipFileHistory.RemoveMenu( openRecentZipArchiveMenu );

    openRecentZipArchiveMenu = new wxMenu();
    m_zipFileHistory.UseMenu( openRecentZipArchiveMenu );
    m_zipFileHistory.AddFilesToMenu( );
    AddMenuItem( fileMenu, openRecentZipArchiveMenu, wxID_ANY,
                 _( "Open Recent Zip &Archive File" ),
                 _( "Open a recently opened zip archive file" ),
                 KiBitmap( recent_xpm ) );

    // Separator
    fileMenu->AppendSeparator();

    // Clear all
    AddMenuItem( fileMenu,
                 ID_GERBVIEW_ERASE_ALL,
                 _( "Clear &All Layers" ),
                 _( "Clear all layers. All data will be deleted" ),
                 KiBitmap( delete_gerber_xpm ) );

    // Separator
    fileMenu->AppendSeparator();

    // Export to Pcbnew
    AddMenuItem( fileMenu,
                 ID_GERBVIEW_EXPORT_TO_PCBNEW,
                 _( "E&xport to Pcbnew..." ),
                 _( "Export data in Pcbnew format" ),
                 KiBitmap( export_xpm ) );

    // Separator
    fileMenu->AppendSeparator();

    // Print
    AddMenuItem( fileMenu, wxID_PRINT,
                 _( "&Print..." ), _( "Print layers" ),
                 KiBitmap( print_button_xpm ) );

    // Separator
    fileMenu->AppendSeparator();

    // Exit
    AddMenuItem( fileMenu, wxID_EXIT,
                 _( "&Close" ), _( "Close GerbView" ),
                 KiBitmap( exit_xpm ) );

    // Menu for configuration and preferences
    wxMenu* configMenu = new wxMenu;

    // Hide layer manager
    AddMenuItem( configMenu, ID_MENU_GERBVIEW_SHOW_HIDE_LAYERS_MANAGER_DIALOG,
                 _( "Hide &Layers Manager" ),
                 m_show_layer_manager_tools ?
                           _( "Hide &Layers Manager" ) : _("Show &Layers Manager" ),
                 KiBitmap( layers_manager_xpm ) );

    // Options (Preferences on WXMAC)
#ifdef __WXMAC__
    configMenu->Append(wxID_PREFERENCES);
#else
    AddMenuItem( configMenu, wxID_PREFERENCES,
                 _( "&Options" ),
                 _( "Set options to draw items" ),
                 KiBitmap( preference_xpm ) );
#endif // __WXMAC__

    // Language submenu
    Pgm().AddMenuLanguageList( configMenu );

    // Icons options submenu
    AddMenuIconsOptions( configMenu );

    // Hotkey submenu
    AddHotkeyConfigMenu( configMenu );

    // Canvas selection
    configMenu->AppendSeparator();

    text = AddHotkeyName( _( "Legacy Tool&set" ), GerbviewHokeysDescr,
                          HK_CANVAS_LEGACY );
    AddMenuItem( configMenu, ID_MENU_CANVAS_LEGACY,
                 text, _( "Use Legacy Toolset (not all features will be available)" ),
                 KiBitmap( tools_xpm ), wxITEM_RADIO );

    text = AddHotkeyName( _( "Modern Toolset (&Accelerated)" ), GerbviewHokeysDescr,
                          HK_CANVAS_OPENGL );
    AddMenuItem( configMenu, ID_MENU_CANVAS_OPENGL, text,
                 _( "Use Modern Toolset with hardware-accelerated graphics (recommended)" ),
                 KiBitmap( tools_xpm ), wxITEM_RADIO );

    text = AddHotkeyName( _( "Modern Toolset (Fallba&ck)" ), GerbviewHokeysDescr,
                          HK_CANVAS_CAIRO );
    AddMenuItem( configMenu, ID_MENU_CANVAS_CAIRO, text,
                 _( "Use Modern Toolset with software graphics (fall-back)" ),
                 KiBitmap( tools_xpm ), wxITEM_RADIO );

    // Menu miscellaneous
    wxMenu* miscellaneousMenu = new wxMenu;

    // List dcodes
    AddMenuItem( miscellaneousMenu, ID_GERBVIEW_SHOW_LIST_DCODES,
                 _( "&List DCodes" ),
                 _( "List D-codes defined in Gerber files" ),
                 KiBitmap( show_dcodenumber_xpm ) );

    // Show source
    AddMenuItem( miscellaneousMenu, ID_GERBVIEW_SHOW_SOURCE,
                 _( "&Show Source" ),
                 _( "Show source file for the current layer" ),
                 KiBitmap( tools_xpm ) );

    // Separator
    miscellaneousMenu->AppendSeparator();

    // Erase graphic layer
    AddMenuItem( miscellaneousMenu, ID_GERBVIEW_ERASE_CURR_LAYER,
                 _( "&Clear Current Layer" ),
                 _( "Clear the graphic layer currently selected" ),
                 KiBitmap( delete_sheet_xpm ) );

    // Separator
    miscellaneousMenu->AppendSeparator();

    // Text editor (usefull to browse source files)
    AddMenuItem( miscellaneousMenu, ID_MENU_GERBVIEW_SELECT_PREFERED_EDITOR,
                 _( "Set &Text Editor..." ),
                 _( "Select your preferred text editor" ),
                 KiBitmap( editor_xpm ) );

    // Help menu
    wxMenu* helpMenu = new wxMenu;

    AddMenuItem( helpMenu, wxID_HELP,
                 _( "Gerbview &Manual" ),
                 _( "Open the GerbView Manual" ),
                 KiBitmap( online_help_xpm ) );

    AddMenuItem( helpMenu, ID_PREFERENCES_HOTKEY_SHOW_CURRENT_LIST,
                 _( "&List Hotkeys..." ),
                 _( "Displays the current hotkeys list and corresponding commands" ),
                 KiBitmap( hotkeys_xpm ) );

    // Separator
    helpMenu->AppendSeparator();

    // Get involved with KiCad
    AddMenuItem( helpMenu, ID_HELP_GET_INVOLVED,
                 _( "Get &Involved" ),
                 _( "Contribute to KiCad (opens a web browser)" ),
                 KiBitmap( info_xpm ) );

    helpMenu->AppendSeparator();

    // About Kicad
    AddMenuItem( helpMenu, wxID_ABOUT,
                 _( "&About KiCad" ), _( "About KiCad" ),
                 KiBitmap( about_xpm ) );

    // Append menus to the menubar
    menuBar->Append( fileMenu, _( "&File" ) );
    menuBar->Append( configMenu, _( "&Preferences" ) );
    menuBar->Append( miscellaneousMenu, _( "&Miscellaneous" ) );
    menuBar->Append( helpMenu, _( "&Help" ) );

    menuBar->Thaw();

    // Associate the menu bar with the frame, if no previous menubar
    if( GetMenuBar() == NULL )
        SetMenuBar( menuBar );
    else
        menuBar->Refresh();
}
