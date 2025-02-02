/*
 * This program source code file is part of KICAD, a free EDA CAD application.
 *
 * Copyright (C) 2015 CERN
 * Copyright (C) 2016 KiCad Developers, see AUTHORS.txt for contributors.
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
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

#include <io_mgr.h>

#include <tool/tool_manager.h>
#include <tool/common_tools.h>
#include <tool/zoom_tool.h>

#include <tools/selection_tool.h>
#include <tools/picker_tool.h>
#include <tools/edit_tool.h>
#include <tools/drawing_tool.h>
#include <tools/point_editor.h>
#include <tools/pcbnew_control.h>
#include <tools/pcb_editor_control.h>
#include <tools/placement_tool.h>
#include <tools/pad_tool.h>
#include <tools/microwave_tool.h>
#include <tools/position_relative_tool.h>
#include <tools/zone_filler_tool.h>
#include <tools/pcb_actions.h>
#include <tools/key_sequence_tool.h>

#include <router/router_tool.h>
#include <router/length_tuner_tool.h>

void PCB_ACTIONS::RegisterAllTools( TOOL_MANAGER* aToolManager )
{
    aToolManager->RegisterTool( new COMMON_TOOLS );
    aToolManager->RegisterTool( new SELECTION_TOOL );
    aToolManager->RegisterTool( new ZOOM_TOOL );
    aToolManager->RegisterTool( new PICKER_TOOL );
    aToolManager->RegisterTool( new ROUTER_TOOL );
    aToolManager->RegisterTool( new LENGTH_TUNER_TOOL );
    aToolManager->RegisterTool( new EDIT_TOOL );
    aToolManager->RegisterTool( new PAD_TOOL );
    aToolManager->RegisterTool( new DRAWING_TOOL );
    aToolManager->RegisterTool( new POINT_EDITOR );
    aToolManager->RegisterTool( new PCBNEW_CONTROL );
    aToolManager->RegisterTool( new PCB_EDITOR_CONTROL );
    aToolManager->RegisterTool( new ALIGN_DISTRIBUTE_TOOL );
    aToolManager->RegisterTool( new MICROWAVE_TOOL );
    aToolManager->RegisterTool( new POSITION_RELATIVE_TOOL );
    aToolManager->RegisterTool( new ZONE_FILLER_TOOL );
    aToolManager->RegisterTool( new KEY_SEQUENCE_TOOL );
}
