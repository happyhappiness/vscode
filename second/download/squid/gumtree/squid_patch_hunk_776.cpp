 /*
- * DEBUG: section --    External DISKD process implementation.
- * AUTHOR: Harvest Derived
- *
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
+ * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
  *
+ * Squid software is distributed under GPLv2+ license and includes
+ * contributions from numerous individuals and organizations.
+ * Please see the COPYING and CONTRIBUTORS files for details.
  */
 
+/* DEBUG: section --    External DISKD process implementation. */
+
 #include "squid.h"
 #include "DiskIO/DiskDaemon/diomsg.h"
 #include "hash.h"
 
-#if HAVE_ERRNO_H
-#include <errno.h>
-#endif
+#include <cerrno>
+#include <iostream>
 #if HAVE_SYS_IPC_H
 #include <sys/ipc.h>
 #endif
 #if HAVE_SYS_MSG_H
 #include <sys/msg.h>
 #endif
 #if HAVE_SYS_SHM_H
 #include <sys/shm.h>
 #endif
-#if HAVE_IOSTREAM
-#include <iostream>
-#endif
 
 void
 xassert(const char *msg, const char *file, int line)
 {
     fprintf(stderr,"assertion failed: %s:%d: \"%s\"\n", file, line, msg);
 
