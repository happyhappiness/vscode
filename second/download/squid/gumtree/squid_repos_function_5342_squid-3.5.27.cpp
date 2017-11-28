void
Client::completeForwarding()
{
    debugs(11,5, HERE << "completing forwarding for "  << fwd);
    assert(fwd != NULL);
    doneWithFwd = "completeForwarding()";
    fwd->complete();
}