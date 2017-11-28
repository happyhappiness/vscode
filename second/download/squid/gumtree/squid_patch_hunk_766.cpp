         last_timeout = squid_curtime;
         checkTimeouts();
     }
 
     switch (Comm::DoSelect(timeout)) {
 
-    case COMM_OK:
+    case Comm::OK:
 
-    case COMM_TIMEOUT:
+    case Comm::TIMEOUT:
         return 0;
 
-    case COMM_IDLE:
+    case Comm::IDLE:
 
-    case COMM_SHUTDOWN:
+    case Comm::SHUTDOWN:
         return EVENT_IDLE;
 
-    case COMM_ERROR:
+    case Comm::COMM_ERROR:
         return EVENT_ERROR;
 
     default:
         fatal_dump("comm.cc: Internal error -- this should never happen.");
         return EVENT_ERROR;
     };
