void
Adaptation::Ecap::XactionRep::forgetVb(const char *reason)
{
    debugs(93,9, HERE << "forget vb " << reason << "; status:" << status());

    BodyPipePointer &p = theVirginRep.raw().body_pipe;
    if (p != NULL && p->stillConsuming(this))
        stopConsumingFrom(p);

    if (makingVb == opUndecided)
        makingVb = opNever;
    else if (makingVb == opOn)
        makingVb = opComplete;
}