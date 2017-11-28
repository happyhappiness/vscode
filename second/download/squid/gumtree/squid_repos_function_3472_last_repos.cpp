void
Adaptation::Ecap::XactionRep::preserveVb(const char *reason)
{
    debugs(93,4, HERE << "preserve for " << reason << "; status:" << status());

    // we reset raw().body_pipe when we are done, so use this one for checking
    const BodyPipePointer &permPipe = theVirginRep.raw().header->body_pipe;
    if (permPipe != NULL) {
        // if libecap consumed, we cannot preserve
        Must(!permPipe->consumedSize());
    }

    forgetVb(reason);
}