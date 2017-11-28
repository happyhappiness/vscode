 
     if (Comm::IsConnOpen(serverConn))
         closeServerConnection("~FwdState");
 
     serverDestinations.clear();
 
-    debugs(17, 3, HERE << "FwdState destructor done");
+    debugs(17, 3, "FwdState destructed, this=" << this);
 }
 
 /**
  * This is the entry point for client-side to start forwarding
  * a transaction.  It is a static method that may or may not
  * allocate a FwdState.
