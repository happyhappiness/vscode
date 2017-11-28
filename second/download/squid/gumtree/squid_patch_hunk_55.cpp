     closer = NULL;
     handleCommClosed();
 }
 
 void Adaptation::Icap::Xaction::handleCommClosed()
 {
+    detailError(ERR_DETAIL_ICAP_XACT_CLOSE);
     mustStop("ICAP service connection externally closed");
 }
 
 void Adaptation::Icap::Xaction::callException(const std::exception  &e)
 {
     setOutcome(xoError);
+    service().noteFailure();
     Adaptation::Initiate::callException(e);
 }
 
 
 void Adaptation::Icap::Xaction::callEnd()
 {
