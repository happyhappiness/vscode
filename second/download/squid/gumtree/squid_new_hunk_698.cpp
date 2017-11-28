/*
 * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

/* DEBUG: section 28    Access Control */

#include "squid.h"
#include "acl/Checklist.h"
#include "acl/TimeData.h"
#include "cache_cf.h"
#include "Debug.h"
#include "wordlist.h"

ACLTimeData::ACLTimeData () : weekbits (0), start (0), stop (0), next (NULL) {}

