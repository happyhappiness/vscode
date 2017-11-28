static void
sslBumpAccessCheckDoneWrapper(allow_t answer, void *data)
{
    ClientRequestContext *calloutContext = static_cast<ClientRequestContext *>(data);

    if (!calloutContext->httpStateIsValid())
        return;
    calloutContext->sslBumpAccessCheckDone(answer);
}