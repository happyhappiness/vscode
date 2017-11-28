     proxyingAb = opComplete;
 }
 
 void
 Adaptation::Ecap::XactionRep::noteMoreBodyDataAvailable(RefCount<BodyPipe> bp)
 {
-    Must(proxyingVb == opOn);
+    Must(makingVb == opOn); // or we would not be registered as a consumer
     Must(theMaster);
     theMaster->noteVbContentAvailable();
 }
 
 void
 Adaptation::Ecap::XactionRep::noteBodyProductionEnded(RefCount<BodyPipe> bp)
 {
-    Must(proxyingVb == opOn);
+    Must(makingVb == opOn); // or we would not be registered as a consumer
     Must(theMaster);
     theMaster->noteVbContentDone(true);
-    proxyingVb = opComplete;
+    vbProductionFinished = true;
 }
 
 void
 Adaptation::Ecap::XactionRep::noteBodyProducerAborted(RefCount<BodyPipe> bp)
 {
-    Must(proxyingVb == opOn);
+    Must(makingVb == opOn); // or we would not be registered as a consumer
     Must(theMaster);
     theMaster->noteVbContentDone(false);
-    proxyingVb = opComplete;
+    vbProductionFinished = true;
 }
 
 void
 Adaptation::Ecap::XactionRep::noteInitiatorAborted()
 {
     mustStop("initiator aborted");
