void
Adaptation::Ecap::XactionRep::vbMake()
{
    Must(proxyingVb == opUndecided);
    BodyPipePointer &p = theVirginRep.raw().body_pipe;
    Must(p != NULL);
    Must(p->setConsumerIfNotLate(this)); // to make vb, we must receive vb
    proxyingVb = opOn;
}