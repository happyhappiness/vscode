         buf.append("R", 1);
 
     if (haveConnection() && !doneReading())
         buf.append("r", 1);
 
     if (!state.doneWriting() && state.writing != State::writingInit)
-        buf.Printf("w(%d)", state.writing);
+        buf.appendf("w(%d)", state.writing);
 
     if (preview.enabled()) {
         if (!preview.done())
-            buf.Printf("P(%d)", (int) preview.debt());
+            buf.appendf("P(%d)", (int) preview.debt());
     }
 
     if (virginBodySending.active())
         buf.append("B", 1);
 
     if (!state.doneParsing() && state.parsing != State::psIcapHeader)
-        buf.Printf("p(%d)", state.parsing);
+        buf.appendf("p(%d)", state.parsing);
 
     if (!doneSending() && state.sending != State::sendingUndecided)
-        buf.Printf("S(%d)", state.sending);
+        buf.appendf("S(%d)", state.sending);
 
     if (state.readyForUob)
         buf.append("6", 1);
 
     if (canStartBypass)
         buf.append("Y", 1);
