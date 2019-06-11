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

#include <database_plugin.h>
//#include <soci/soci.h>
//#include <soci/postgresql/soci-postgresql.h>
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

DATABASE_PLUGIN::DATABASE_PLUGIN()
{
}


DATABASE_PLUGIN::~DATABASE_PLUGIN()
{
}


const wxString DATABASE_PLUGIN::PluginName() const
{
    return "Database";
}


const wxString DATABASE_PLUGIN::GetFileExtension() const
{
    return wxEmptyString;
}


void DATABASE_PLUGIN::FootprintEnumerate( wxArrayString& aFootprintNames,
        const wxString& aLibraryPath, const PROPERTIES* aProperties )
{
    Poco::Data::SQLite::Connector::registerConnector();
    Session session("SQLite", "sample.db");
    //s/oci::session sql("postgresql://dbname=mydb");
    //sql.open("postgresql://dbname=mydb");
}


void DATABASE_PLUGIN::PrefetchLib( const wxString& aLibraryPath, const PROPERTIES* aProperties )
{
}


MODULE* DATABASE_PLUGIN::FootprintLoad( const wxString& aLibraryPath,
        const wxString& aFootprintName, const PROPERTIES* aProperties )
{
}


bool DATABASE_PLUGIN::IsFootprintLibWritable( const wxString& aLibraryPath )
{
}


void DATABASE_PLUGIN::FootprintSave(
        const wxString& aLibraryPath, const MODULE* aFootprint, const PROPERTIES* aProperties )
{
}


void DATABASE_PLUGIN::FootprintDelete( const wxString& aLibraryPath, const wxString& aFootprintName,
        const PROPERTIES* aProperties )
{
}


void DATABASE_PLUGIN::FootprintLibCreate(
        const wxString& aLibraryPath, const PROPERTIES* aProperties )
{
}


bool DATABASE_PLUGIN::FootprintLibDelete(
        const wxString& aLibraryPath, const PROPERTIES* aProperties )
{
}


void DATABASE_PLUGIN::FootprintLibOptions( PROPERTIES* aListToAppendTo ) const
{
}


long long DATABASE_PLUGIN::GetLibraryTimestamp( const wxString& aLibraryPath ) const
{
}
