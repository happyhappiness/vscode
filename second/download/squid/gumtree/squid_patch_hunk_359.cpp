 {
     Must(!theXaction);
     ++theLaunches;
     debugs(93,4, HERE << "launching " << xkind << " xaction #" << theLaunches);
     Adaptation::Icap::Xaction *x = createXaction();
     x->attempts = theLaunches;
-    if (theLaunches > 1)
+    if (theLaunches > 1) {
+        x->clearError();
         x->disableRetries();
+    }
     if (theLaunches >= TheConfig.repeat_limit)
         x->disableRepeats("over icap_retry_limit");
     theXaction = initiateAdaptation(x);
     Must(initiated(theXaction));
 }
 
