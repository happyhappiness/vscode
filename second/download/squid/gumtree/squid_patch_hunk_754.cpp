 
     case STREAM_NONE:
         pullData();
         break;
 
     case STREAM_COMPLETE:
-        debugs(33, 5, HERE << conn << " Keeping Alive");
-        keepaliveNextRequest();
+        debugs(33, 5, conn << " Stream complete, keepalive is " << http->request->flags.proxyKeepalive);
+        if (http->request->flags.proxyKeepalive)
+            keepaliveNextRequest();
+        else
+            initiateClose("STREAM_COMPLETE NOKEEPALIVE");
         return;
 
     case STREAM_UNPLANNED_COMPLETE:
         initiateClose("STREAM_UNPLANNED_COMPLETE");
         return;
 
