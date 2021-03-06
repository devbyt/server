/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: ft=cpp:expandtab:ts=8:sw=4:softtabstop=4:
#ident "$Id$"
/*======
This file is part of PerconaFT.


Copyright (c) 2006, 2015, Percona and/or its affiliates. All rights reserved.

    PerconaFT is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2,
    as published by the Free Software Foundation.

    PerconaFT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PerconaFT.  If not, see <http://www.gnu.org/licenses/>.

----------------------------------------

    PerconaFT is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License, version 3,
    as published by the Free Software Foundation.

    PerconaFT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with PerconaFT.  If not, see <http://www.gnu.org/licenses/>.
======= */

#ident "Copyright (c) 2006, 2015, Percona and/or its affiliates. All rights reserved."

#pragma once

#include "ft/txn/txn.h"

#include "util/omt.h"

namespace toku {

class txnid_set {
public:
    // effect: Creates an empty set. Does not malloc space for
    //         any entries yet. That is done lazily on add().
    void create(void);

    // effect: Destroy the set's internals.
    void destroy(void);

    // returns: True if the given txnid is a member of the set.
    bool contains(TXNID id) const;

    // effect: Adds a given txnid to the set if it did not exist
    void add(TXNID txnid);

    // effect: Deletes a txnid from the set if it exists.
    void remove(TXNID txnid);

    // returns: Size of the set
    size_t size(void) const;

    // returns: The "i'th" id in the set, as if it were sorted.
    TXNID get(size_t i) const;

private:
    toku::omt<TXNID> m_txnids;

    friend class txnid_set_unit_test;
};
ENSURE_POD(txnid_set);

} /* namespace toku */
