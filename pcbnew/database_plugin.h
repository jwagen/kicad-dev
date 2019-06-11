/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2019 KiCad Developers, see AUTHORS.txt for contributors.
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

#ifndef DATABASE_PLUGIN_H_
#define DATABASE_PLUGIN_H_

#include <kicad_plugin.h>

class DATABASE_PLUGIN : public PCB_IO
{
public:
    //-----<PLUGIN API>----------------------------------------------------------
    const wxString PluginName() const override;

    const wxString GetFileExtension() const override;

    void FootprintEnumerate( wxArrayString& aFootprintNames, const wxString& aLibraryPath,
            const PROPERTIES* aProperties = NULL ) override;

    void PrefetchLib( const wxString& aLibraryPath, const PROPERTIES* aProperties = NULL ) override;

    MODULE* FootprintLoad( const wxString& aLibraryPath, const wxString& aFootprintName,
            const PROPERTIES* aProperties ) override;

    void FootprintSave( const wxString& aLibraryPath, const MODULE* aFootprint,
            const PROPERTIES* aProperties = NULL ) override;

    void FootprintDelete( const wxString& aLibraryPath, const wxString& aFootprintName,
            const PROPERTIES* aProperties = NULL ) override;

    bool IsFootprintLibWritable( const wxString& aLibraryPath ) override;

    long long GetLibraryTimestamp( const wxString& aLibraryPath ) const override;

    void FootprintLibOptions( PROPERTIES* aListToAppendTo ) const override;

    void FootprintLibCreate( const wxString& aLibraryPath, const PROPERTIES* aProperties ) override;

    bool FootprintLibDelete( const wxString& aLibraryPath, const PROPERTIES* aProperties ) override;

    //-----</PLUGIN API>---------------------------------------------------------

    DATABASE_PLUGIN(); // constructor, if any, must be zero arg
    ~DATABASE_PLUGIN();

protected:
};


#endif // GITHUB_PLUGIN_H_
