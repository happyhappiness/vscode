 
     estimateVirginBody(); // before virgin disappears!
 
     canStartBypass = service().cfg().bypass;
 
     // it is an ICAP violation to send request to a service w/o known OPTIONS
-
-    if (service().up())
+    // and the service may is too busy for us: honor Max-Connections and such
+    if (service().up() && service().availableForNew())
         startWriting();
     else
         waitForService();
 }
 
 void Adaptation::Icap::ModXact::waitForService()
 {
+    const char *comment;
     Must(!state.serviceWaiting);
-    debugs(93, 7, HERE << "will wait for the ICAP service" << status());
-    typedef NullaryMemFunT<ModXact> Dialer;
-    AsyncCall::Pointer call = JobCallback(93,5,
-                                          Dialer, this, Adaptation::Icap::ModXact::noteServiceReady);
-    service().callWhenReady(call);
+
+    if (!service().up()) {
+        AsyncCall::Pointer call = JobCallback(93,5,
+                                              ConnWaiterDialer, this, Adaptation::Icap::ModXact::noteServiceReady);
+
+        service().callWhenReady(call);
+        comment = "to be up";
+    } else {
+        //The service is unavailable because of max-connection or other reason
+
+        if (service().cfg().onOverload != srvWait) {
+            // The service is overloaded, but waiting to be available prohibited by
+            // user configuration (onOverload is set to "block" or "bypass")
+            if (service().cfg().onOverload == srvBlock)
+                disableBypass("not available", true);
+            else //if (service().cfg().onOverload == srvBypass)
+                canStartBypass = true;
+
+            disableRetries();
+            disableRepeats("ICAP service is not available");
+
+            debugs(93, 7, HERE << "will not wait for the service to be available" <<
+                   status());
+
+            throw TexcHere("ICAP service is not available");
+        }
+
+        AsyncCall::Pointer call = JobCallback(93,5,
+                                              ConnWaiterDialer, this, Adaptation::Icap::ModXact::noteServiceAvailable);
+        service().callWhenAvailable(call, state.waitedForService);
+        comment = "to be available";
+    }
+
+    debugs(93, 7, HERE << "will wait for the service " << comment <<  status());
     state.serviceWaiting = true; // after callWhenReady() which may throw
+    state.waitedForService = true;
 }
 
 void Adaptation::Icap::ModXact::noteServiceReady()
 {
     Must(state.serviceWaiting);
     state.serviceWaiting = false;
 
-    if (service().up()) {
-        startWriting();
-    } else {
+    if (!service().up()) {
         disableRetries();
         disableRepeats("ICAP service is unusable");
         throw TexcHere("ICAP service is unusable");
     }
+
+    if (service().availableForOld())
+        startWriting();
+    else
+        waitForService();
+}
+
+void Adaptation::Icap::ModXact::noteServiceAvailable()
+{
+    Must(state.serviceWaiting);
+    state.serviceWaiting = false;
+
+    if (service().up() && service().availableForOld())
+        startWriting();
+    else
+        waitForService();
 }
 
 void Adaptation::Icap::ModXact::startWriting()
 {
     state.writing = State::writingConnect;
 
