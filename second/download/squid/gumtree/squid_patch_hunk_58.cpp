         buf.append(";", 1);
     }
 }
 
 void Adaptation::Icap::Xaction::fillDoneStatus(MemBuf &buf) const
 {
-    if (connection >= 0 && commEof)
-        buf.Printf("Comm(%d)", connection);
+    if (haveConnection() && commEof)
+        buf.Printf("Comm(%d)", connection->fd);
 
     if (stopReason != NULL)
         buf.Printf("Stopped");
 }
 
 bool Adaptation::Icap::Xaction::fillVirginHttpHeader(MemBuf &buf) const
