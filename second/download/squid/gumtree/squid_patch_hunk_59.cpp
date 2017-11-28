 {
     announceInitiatorAbort(theLauncher); // propogate to the transaction
     clearInitiator();
     mustStop("initiator gone");
 }
 
-void Adaptation::Iterator::noteAdaptationQueryAbort(bool final)
+void Adaptation::Iterator::handleAdaptationBlock(const Answer &answer)
+{
+    debugs(93,5, HERE << "blocked by " << answer);
+    clearAdaptation(theLauncher);
+    updatePlan(false);
+    sendAnswer(answer);
+    mustStop("blocked");
+}
+
+void Adaptation::Iterator::handleAdaptationError(bool final)
 {
     debugs(93,5, HERE << "final: " << final << " plan: " << thePlan);
     clearAdaptation(theLauncher);
     updatePlan(false);
 
     // can we replace the failed service (group-level bypass)?
