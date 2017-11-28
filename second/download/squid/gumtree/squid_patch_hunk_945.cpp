 
     if (state.doneWriting())
         buf.append("w", 1);
 
     if (preview.enabled()) {
         if (preview.done())
-            buf.Printf("P%s", preview.ieof() ? "(ieof)" : "");
+            buf.appendf("P%s", preview.ieof() ? "(ieof)" : "");
     }
 
     if (doneReading())
         buf.append("r", 1);
 
     if (state.doneParsing())
