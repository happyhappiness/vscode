 Adaptation::Ecap::XactionRep::adaptationAborted()
 {
     tellQueryAborted(true); // should eCAP support retries?
     mustStop("adaptationAborted");
 }
 
-bool
-Adaptation::Ecap::XactionRep::callable() const
-{
-    return !done();
-}
-
 void
 Adaptation::Ecap::XactionRep::noteMoreBodySpaceAvailable(RefCount<BodyPipe> bp)
 {
     Must(proxyingAb == opOn);
     moveAbContent();
 }
