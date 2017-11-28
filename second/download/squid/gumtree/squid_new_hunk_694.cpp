/*
 * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

/* DEBUG: section 28    Access Control */

#include "squid.h"
#include "acl/FilledChecklist.h"
#include "acl/HttpStatus.h"
#include "cache_cf.h"
#include "Debug.h"
#include "HttpReply.h"

#include <climits>

static void aclParseHTTPStatusList(Splay<acl_httpstatus_data *> **curlist);
static int aclHTTPStatusCompare(acl_httpstatus_data * const &a, acl_httpstatus_data * const &b);
static int aclMatchHTTPStatus(Splay<acl_httpstatus_data*> **dataptr, Http::StatusCode status);

acl_httpstatus_data::acl_httpstatus_data(int x) : status1(x), status2(x) { ; }

acl_httpstatus_data::acl_httpstatus_data(int x, int y) : status1(x), status2(y) { ; }

SBuf
acl_httpstatus_data::toStr() const
{
    SBuf rv;
    if (status2 == INT_MAX)
        rv.Printf("%d-", status1);
    else if (status1 == status2)
        rv.Printf("%d", status1);
    else
        rv.Printf("%d-%d", status1, status2);
    return rv;
}

int acl_httpstatus_data::compare(acl_httpstatus_data* const& a, acl_httpstatus_data* const& b)
{
    int ret;
    ret = aclHTTPStatusCompare(b, a);

    if (ret != 0)
        ret = aclHTTPStatusCompare(a, b);

    if (ret == 0) {
        const SBuf sa = a->toStr();
        const SBuf sb = b->toStr();
        debugs(28, DBG_CRITICAL, "WARNING: '" << sa << "' is a subrange of '" << sb << "'");
        debugs(28, DBG_CRITICAL, "WARNING: because of this '" << sa << "' is ignored to keep splay tree searching predictable");
        debugs(28, DBG_CRITICAL, "WARNING: You should probably remove '" << sb << "' from the ACL named '" << AclMatchedName << "'");
    }

    return ret;
}

ACL *
