static void
sslBumpAccessCheckDoneWrapper(int answer, void *data)
{
    ClientRequestContext *calloutContext = static_cast<ClientRequestContext *>(data);

    if (!calloutContext->httpStateIsValid())
        return;
    calloutContext->sslBumpAccessCheckDone(answer == ACCESS_ALLOWED);
}