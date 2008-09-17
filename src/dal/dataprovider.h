/*
 *  The Mana World Server
 *  Copyright 2004 The Mana World Development Team
 *
 *  This file is part of The Mana World.
 *
 *  The Mana World  is free software; you can redistribute  it and/or modify it
 *  under the terms of the GNU General  Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or any later version.
 *
 *  The Mana  World is  distributed in  the hope  that it  will be  useful, but
 *  WITHOUT ANY WARRANTY; without even  the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 *  more details.
 *
 *  You should  have received a  copy of the  GNU General Public  License along
 *  with The Mana  World; if not, write to the  Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  $Id$
 */


#ifndef _TMWSERV_DATA_PROVIDER_H_
#define _TMWSERV_DATA_PROVIDER_H_


#include <string>
#include <stdexcept>

#include "recordset.h"

namespace dal
{

/**
 * Enumeration type for the database backends.
 */
typedef enum {
    DB_BKEND_MYSQL,
    DB_BKEND_SQLITE,
    DB_BKEND_POSTGRESQL
} DbBackends;


/**
 * An abstract data provider.
 *
 * Notes:
 *     - depending on the database backend, the connection to an unexisting
 *       database may actually create it as a side-effect (e.g. SQLite).
 *
 * Limitations:
 *     - this class does not provide APIs for:
 *         - remote connections,
 *         - creating new databases,
 *         - dropping existing databases.
 */
class DataProvider
{
    public:
        /**
         * Constructor.
         */
        DataProvider(void)
            throw();


        /**
         * Destructor.
         */
        virtual
        ~DataProvider(void)
            throw();


        /**
         * Get the connection status.
         *
         * @return true if connected.
         */
        bool
        isConnected(void) const
            throw();


        /**
         * Get the name of the database backend.
         *
         * @return the database backend name.
         */
        virtual DbBackends
        getDbBackend(void) const
            throw() = 0;


        /**
         * Create a connection to the database.
         *
         * Each dataprovider is responsible to have default values and load
         * necessary options from the config file.
         *
         * @exception DbConnectionFailure if unsuccessful connection.
         */
        virtual void connect(void) = 0;


        /**
         * Execute a SQL query.
         *
         * @param sql the SQL query.
         * @param refresh if true, refresh the cache (default = false).
         *
         * @return a recordset.
         *
         * @exception DbSqlQueryExecFailure if unsuccessful execution.
         * @exception std::runtime_error if trying to query a closed database.
         */
        virtual const RecordSet&
        execSql(const std::string& sql,
                const bool refresh = false) = 0;


        /**
         * Close the connection to the database.
         *
         * @exception DbDisconnectionFailure if unsuccessful disconnection.
         */
        virtual void
        disconnect(void) = 0;

        /**
         * Get the Database Name.
         */
        std::string
        getDbName(void);

        /**
         * Starts a transaction.
         *
         * @exception std::runtime_error if a transaction is still open
         */
        virtual void
        beginTransaction(void)
            throw (std::runtime_error) = 0;

        /**
         * Commits a transaction.
         *
         * @exception std::runtime_error if no connection is currently open.
         */
        virtual void
        commitTransaction(void)
            throw (std::runtime_error) = 0;

        /**
         * Rollback a transaction.
         *
         * @exception std::runtime_error if no connection is currently open.
         */
        virtual void
        rollbackTransaction(void)
            throw (std::runtime_error) = 0;

        /**
         * Returns the number of changed rows by the last executed SQL
         * statement.
         *
         * @return Number of rows that have changed.
         */
        virtual const unsigned int
        getModifiedRows(void) const = 0;

        /**
         * Returns the last inserted value of an autoincrement column after an
         * INSERT statement.
         *
         * @return last autoincrement value.
         */
        virtual const unsigned int
        getLastId(void) const = 0;

    protected:
        std::string mDbName;  /**< the database name */
        bool mIsConnected;    /**< the connection status */
        std::string mSql;     /**< cache the last SQL query */
        RecordSet mRecordSet; /**< cache the result of the last SQL query */
};


} // namespace dal

#endif // _TMWSERV_DATA_PROVIDER_H_
