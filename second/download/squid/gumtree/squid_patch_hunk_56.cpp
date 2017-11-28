 {
     return !writer;
 }
 
 bool Adaptation::Icap::Xaction::doneWithIo() const
 {
-    return connection >= 0 && // or we could still be waiting to open it
+    return haveConnection() &&
            !connector && !reader && !writer && // fast checks, some redundant
            doneReading() && doneWriting();
 }
 
+bool Adaptation::Icap::Xaction::haveConnection() const
+{
+    return connection != NULL && connection->isOpen();
+}
+
 // initiator aborted
 void Adaptation::Icap::Xaction::noteInitiatorAborted()
 {
 
     if (theInitiator.set()) {
+        debugs(93,4, HERE << "Initiator gone before ICAP transaction ended");
         clearInitiator();
+        detailError(ERR_DETAIL_ICAP_INIT_GONE);
+        setOutcome(xoGone);
         mustStop("initiator aborted");
     }
 
 }
 
 void Adaptation::Icap::Xaction::setOutcome(const Adaptation::Icap::XactOutcome &xo)
