+/*
+ * Copyright (C) 1996-2017 The Squid Software Foundation and contributors
+ *
+ * Squid software is distributed under GPLv2+ license and includes
+ * contributions from numerous individuals and organizations.
+ * Please see the COPYING and CONTRIBUTORS files for details.
+ */
+
 #include "squid.h"
 #include "adaptation/Config.h"
 #include "adaptation/History.h"
 #include "base/TextException.h"
 #include "Debug.h"
 #include "globals.h"
 #include "SquidTime.h"
 
 /// impossible services value to identify unset theNextServices
 const static char *TheNullServices = ",null,";
 
 Adaptation::History::Entry::Entry(const String &serviceId, const timeval &when):
-        service(serviceId), start(when), theRptm(-1), retried(false)
+    service(serviceId), start(when), theRptm(-1), retried(false)
 {
 }
 
 Adaptation::History::Entry::Entry():
-        start(current_time), theRptm(-1), retried(false)
+    start(current_time), theRptm(-1), retried(false)
 {
 }
 
 void Adaptation::History::Entry::stop()
 {
     // theRptm may already be set if the access log entry has already been made
