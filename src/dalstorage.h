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


#ifndef _TMWSERV_DALSTORAGE_H_
#define _TMWSERV_DALSTORAGE_H_


#include <vector>

#include "dal/dataproviderfactory.h"
#include "storage.h"


namespace tmwserv
{


/**
 * A storage class that relies on DAL.
 */
class DALStorage: public Storage
{
    public:
        /**
         * Constructor.
         */
        DALStorage(void);


        /**
         * Destructor.
         */
        ~DALStorage(void)
            throw();


        /**
         * Save changes to the database permanently.
         */
        void
        flush(void);


        /**
         * Get the number of Accounts saved in database (test function).
         *
         * @return the number of Accounts.
         */
        unsigned int
        getAccountCount(void);


        /**
         * Get an account by user name.
         *
         * @param userName the owner of the account.
         *
         * @return the account associated to the user name.
         */
        Account*
        getAccount(const std::string& userName);


    private:
        /**
         * Connect to the database and initialize it if necessary.
         */
        void
        connect(void);


    private:
        std::auto_ptr<dal::DataProvider> mDb; /**< the data provider */
        typedef std::vector<Account*> Accounts;
        Accounts mAccounts;                   /**< the loaded accounts */
        typedef std::vector<Being*> Beings;
        Beings mCharacters;                   /**< the loaded characters */
};


} // namespace tmwserv


#endif // _TMWSERV_DALSTORAGE_H_