void
clientRedirectDoneWrapper(void *data, char *result)
{
    ClientRequestContext *calloutContext = (ClientRequestContext *)data;

    if (!calloutContext->httpStateIsValid())
        return;

    calloutContext->clientRedirectDone(result);
}