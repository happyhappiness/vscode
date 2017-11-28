     if (state.serviceWaiting)
         buf.append("U", 1);
 
     if (virgin.body_pipe != NULL)
         buf.append("R", 1);
 
-    if (connection > 0 && !doneReading())
+    if (haveConnection() && !doneReading())
         buf.append("r", 1);
 
     if (!state.doneWriting() && state.writing != State::writingInit)
         buf.Printf("w(%d)", state.writing);
 
     if (preview.enabled()) {
