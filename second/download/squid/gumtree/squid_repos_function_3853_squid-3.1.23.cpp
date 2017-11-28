void
Adaptation::Ecap::XactionRep::dropVirgin(const char *reason)
{
    debugs(93,4, HERE << "because " << reason << "; status:" << status());
    Must(proxyingVb = opOn);

    BodyPipePointer &p = theVirginRep.raw().body_pipe;
    Must(p != NULL);
    Must(p->stillConsuming(this));
    stopConsumingFrom(p);
    p->enableAutoConsumption();
    proxyingVb = opComplete;
    canAccessVb = false;

    // called from adapter handler so does not inform adapter
}