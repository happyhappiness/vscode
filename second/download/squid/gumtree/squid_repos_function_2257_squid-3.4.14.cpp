void
ServerStateData::completeForwarding()
{
    debugs(11,5, HERE << "completing forwarding for "  << fwd);
    assert(fwd != NULL);
    fwd->complete();
}