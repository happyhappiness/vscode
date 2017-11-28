 #include "globals.h"
 #include "SquidTime.h"
 
 Adaptation::Icap::History::History():
     logType(LOG_TAG_NONE),
     req_sz(0),
-    pastTime(0),
     concurrencyLevel(0)
 {
     memset(&currentStart, 0, sizeof(currentStart));
+    memset(&pastTime, 0, sizeof(pastTime));
 }
 
 void Adaptation::Icap::History::start(const char *context)
 {
     if (!concurrencyLevel++)
         currentStart = current_time;
 
     debugs(93,4, HERE << "start " << context << " level=" << concurrencyLevel
-           << " time=" << pastTime << ' ' << this);
+           << " time=" << tvToMsec(pastTime) << ' ' << this);
 }
 
 void Adaptation::Icap::History::stop(const char *context)
 {
     if (!concurrencyLevel) {
         debugs(93, DBG_IMPORTANT, HERE << "Internal error: poor history accounting " << this);
         return;
     }
 
-    const int current = currentTime();
+    struct timeval current;
+    currentTime(current);
     debugs(93,4, HERE << "stop " << context << " level=" << concurrencyLevel <<
-           " time=" << pastTime << '+' << current << ' ' << this);
+           " time=" << tvToMsec(pastTime) << '+' << tvToMsec(current) << ' ' << this);
 
     if (!--concurrencyLevel)
-        pastTime += current;
+        tvAssignAdd(pastTime, current);
 }
 
-int Adaptation::Icap::History::processingTime() const
+void
+Adaptation::Icap::History::processingTime(timeval &total) const
 {
-    const int total = pastTime + currentTime();
-    debugs(93,7, HERE << " current total: " << total << ' ' << this);
-    return total;
+    currentTime(total);
+    tvAssignAdd(total, pastTime);
+    debugs(93,7, HERE << " current total: " << tvToMsec(total) << ' ' << this);
 }
 
-int Adaptation::Icap::History::currentTime() const
+void
+Adaptation::Icap::History::currentTime(timeval &current) const
 {
-    return concurrencyLevel > 0 ?
-           max(0, tvSubMsec(currentStart, current_time)) : 0;
+    if (concurrencyLevel > 0)
+        tvSub(current, currentStart, current_time);
+    else {
+        current.tv_sec = 0;
+        current.tv_usec = 0;
+    }
 }
 
