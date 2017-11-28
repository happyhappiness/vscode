void
Adaptation::Ecap::XactionRep::sinkVb(const char *reason)
{
    debugs(93,4, HERE << "sink for " << reason << "; status:" << status());

    // we reset raw().body_pipe when we are done, so use this one for checking
    const BodyPipePointer &permPipe = theVirginRep.raw().header->body_pipe;
    if (permPipe != NULL)
        permPipe->enableAutoConsumption();

    forgetVb(reason);
}