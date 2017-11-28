void
clientStoreIdDoneWrapper(void *data, const Helper::Reply &result)
{
    ClientRequestContext *calloutContext = (ClientRequestContext *)data;

    if (!calloutContext->httpStateIsValid())
        return;

    calloutContext->clientStoreIdDone(result);
}