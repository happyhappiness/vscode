     writeOffset += params.size;
     if (!doneAll())
         scheduleStoreCopy(); // retrieve the next data portion
 }
 
 void
-Mgr::StoreToCommWriter::noteCommClosed(const CommCloseCbParams& params)
+Mgr::StoreToCommWriter::noteCommClosed(const CommCloseCbParams &)
 {
     debugs(16, 6, HERE);
     Must(!Comm::IsConnOpen(clientConnection));
     mustStop("commClosed");
 }
 
