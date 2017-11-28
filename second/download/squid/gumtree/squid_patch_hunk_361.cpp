 void Adaptation::Icap::ServiceRep::suspend(const char *reason)
 {
     if (isSuspended) {
         debugs(93,4, HERE << "keeping suspended, also for " << reason);
     } else {
         isSuspended = reason;
-        debugs(93,1, "suspending ICAP service for " << reason);
+        debugs(93, DBG_IMPORTANT, "suspending ICAP service for " << reason);
         scheduleUpdate(squid_curtime + TheConfig.service_revival_delay);
         announceStatusChange("suspended", true);
     }
 }
 
 bool Adaptation::Icap::ServiceRep::probed() const
