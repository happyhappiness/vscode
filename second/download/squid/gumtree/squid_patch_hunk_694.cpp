 /*
- * DEBUG: section 28    Access Control
- * AUTHOR: Duane Wessels
+ * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
  *
- * SQUID Web Proxy Cache          http://www.squid-cache.org/
- * ----------------------------------------------------------
- *
- *  Squid is the result of efforts by numerous individuals from
- *  the Internet community; see the CONTRIBUTORS file for full
- *  details.   Many organizations have provided support for Squid's
- *  development; see the SPONSORS file for full details.  Squid is
- *  Copyrighted (C) 2001 by the Regents of the University of
- *  California; see the COPYRIGHT file for full details.  Squid
- *  incorporates software developed and/or copyrighted by other
- *  sources; see the CREDITS file for full details.
- *
- *  This program is free software; you can redistribute it and/or modify
- *  it under the terms of the GNU General Public License as published by
- *  the Free Software Foundation; either version 2 of the License, or
- *  (at your option) any later version.
- *
- *  This program is distributed in the hope that it will be useful,
- *  but WITHOUT ANY WARRANTY; without even the implied warranty of
- *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
- *  GNU General Public License for more details.
- *
- *  You should have received a copy of the GNU General Public License
- *  along with this program; if not, write to the Free Software
- *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
- *
- *
- * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
+ * Squid software is distributed under GPLv2+ license and includes
+ * contributions from numerous individuals and organizations.
+ * Please see the COPYING and CONTRIBUTORS files for details.
  */
 
+/* DEBUG: section 28    Access Control */
+
 #include "squid.h"
-#include "acl/HttpStatus.h"
 #include "acl/FilledChecklist.h"
+#include "acl/HttpStatus.h"
 #include "cache_cf.h"
 #include "Debug.h"
 #include "HttpReply.h"
-#include "wordlist.h"
 
-#if HAVE_LIMITS_H
-#include <limits.h>
-#endif
+#include <climits>
 
-static void aclParseHTTPStatusList(SplayNode<acl_httpstatus_data *> **curlist);
+static void aclParseHTTPStatusList(Splay<acl_httpstatus_data *> **curlist);
 static int aclHTTPStatusCompare(acl_httpstatus_data * const &a, acl_httpstatus_data * const &b);
-static int aclMatchHTTPStatus(SplayNode<acl_httpstatus_data*> **dataptr, Http::StatusCode status);
+static int aclMatchHTTPStatus(Splay<acl_httpstatus_data*> **dataptr, Http::StatusCode status);
 
 acl_httpstatus_data::acl_httpstatus_data(int x) : status1(x), status2(x) { ; }
 
 acl_httpstatus_data::acl_httpstatus_data(int x, int y) : status1(x), status2(y) { ; }
 
-void acl_httpstatus_data::toStr(char* buf, int len) const
+SBuf
+acl_httpstatus_data::toStr() const
 {
+    SBuf rv;
     if (status2 == INT_MAX)
-        snprintf(buf, len, "%d-", status1);
+        rv.Printf("%d-", status1);
     else if (status1 == status2)
-        snprintf(buf, len, "%d", status1);
+        rv.Printf("%d", status1);
     else
-        snprintf(buf, len, "%d-%d", status1, status2);
+        rv.Printf("%d-%d", status1, status2);
+    return rv;
 }
 
 int acl_httpstatus_data::compare(acl_httpstatus_data* const& a, acl_httpstatus_data* const& b)
 {
     int ret;
     ret = aclHTTPStatusCompare(b, a);
 
     if (ret != 0)
         ret = aclHTTPStatusCompare(a, b);
 
     if (ret == 0) {
-        char bufa[8];
-        char bufb[8];
-        a->toStr(bufa, sizeof(bufa));
-        b->toStr(bufb, sizeof(bufb));
-        debugs(28, DBG_CRITICAL, "WARNING: '" << bufa << "' is a subrange of '" << bufb << "'");
-        debugs(28, DBG_CRITICAL, "WARNING: because of this '" << bufa << "' is ignored to keep splay tree searching predictable");
-        debugs(28, DBG_CRITICAL, "WARNING: You should probably remove '" << bufb << "' from the ACL named '" << AclMatchedName << "'");
+        const SBuf sa = a->toStr();
+        const SBuf sb = b->toStr();
+        debugs(28, DBG_CRITICAL, "WARNING: '" << sa << "' is a subrange of '" << sb << "'");
+        debugs(28, DBG_CRITICAL, "WARNING: because of this '" << sa << "' is ignored to keep splay tree searching predictable");
+        debugs(28, DBG_CRITICAL, "WARNING: You should probably remove '" << sb << "' from the ACL named '" << AclMatchedName << "'");
     }
 
     return ret;
 }
 
 ACL *
