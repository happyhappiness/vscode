void
clientStoreIdDoneWrapper(void *data, const HelperReply &result)
{
    ClientRequestContext *calloutContext = (ClientRequestContext *)data;

    if (!calloutContext->httpStateIsValid())
        return;

    calloutContext->clientStoreIdDone(result);
}