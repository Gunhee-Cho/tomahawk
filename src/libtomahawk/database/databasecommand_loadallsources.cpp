/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "databasecommand_loadallsources.h"

#include <QSqlQuery>

#include "network/servent.h"
#include "Source.h"
#include "databaseimpl.h"
#include "utils/logger.h"

using namespace Tomahawk;


void
DatabaseCommand_LoadAllSources::exec( DatabaseImpl* dbi )
{
    TomahawkSqlQuery query = dbi->newquery();

    query.exec( QString( "SELECT id, name, friendlyname "
                         "FROM source" ) );

    QList<source_ptr> sources;
    while ( query.next() )
    {
        source_ptr src( new Source( query.value( 0 ).toUInt(), query.value( 1 ).toString() ) );
        src->setFriendlyName( query.value( 2 ).toString() );
        sources << src;
    }

    emit done( sources );
}

