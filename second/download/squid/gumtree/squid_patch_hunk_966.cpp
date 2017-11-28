 
     inCall = &call; // XXX: ugly, but safe if callStart/callEnd,Ex are paired
     debugs(inCall->debugSection, inCall->debugLevel,
            typeName << " status in:" << status());
 }
 
-void AsyncJob::callException(const std::exception &e)
+void
+AsyncJob::callException(const std::exception &ex)
 {
+    debugs(93, 2, ex.what());
     // we must be called asynchronously and hence, the caller must lock us
     Must(cbdataReferenceValid(toCbdata()));
 
     mustStop("exception");
 }
 
