     disableRepeats("sent headers");
     disableBypass("sent headers", true);
     sendAnswer(Answer::Forward(adapted.header));
 
     if (state.sending == State::sendingVirgin)
         echoMore();
+    else {
+        // If we are not using the virgin HTTP object update the
+        // HttpMsg::sources flag.
+        // The state.sending may set to State::sendingVirgin in the case
+        // of 206 responses too, where we do not want to update HttpMsg::sources
+        // flag. However even for 206 responses the state.sending is
+        // not set yet to sendingVirgin. This is done in later step
+        // after the parseBody method called.
+        updateSources();
+    }
 }
 
 void Adaptation::Icap::ModXact::parseIcapHead()
 {
     Must(state.sending == State::sendingUndecided);
 
