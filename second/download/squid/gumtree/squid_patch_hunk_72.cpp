 
     buf.append(" [", 2);
     if (stopReason != NULL) {
         buf.Printf("Stopped, reason:");
         buf.Printf("%s",stopReason);
     }
-    buf.Printf(" job%d]", id);
+    buf.Printf(" %s%u]", id.Prefix, id.value);
     buf.terminate();
 
     return buf.content();
 }
 
 
