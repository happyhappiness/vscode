static void
adaptationAclCheckDoneWrapper(Adaptation::ServiceGroupPointer g, void *data)
{
    ClientRequestContext *calloutContext = (ClientRequestContext *)data;

    if (!calloutContext->httpStateIsValid())
        return;

    calloutContext->adaptationAclCheckDone(g);
}