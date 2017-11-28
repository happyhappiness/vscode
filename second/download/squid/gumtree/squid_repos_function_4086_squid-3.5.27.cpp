void
Adaptation::Ecap::XactionRep::vbMake()
{
    Must(makingVb == opUndecided);
    BodyPipePointer &p = theVirginRep.raw().body_pipe;
    Must(p != NULL);
    Must(p->setConsumerIfNotLate(this)); // to deliver vb, we must receive vb
    makingVb = opOn;
}