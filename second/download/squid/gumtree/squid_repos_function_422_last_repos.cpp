static void
clientStoreIdAccessCheckDone(allow_t answer, void *data)
{
    ClientRequestContext *context = static_cast<ClientRequestContext *>(data);
    ClientHttpRequest *http = context->http;
    context->acl_checklist = NULL;

    if (answer.allowed())
        storeIdStart(http, clientStoreIdDoneWrapper, context);
    else {
        debugs(85, 3, "access denied expected ERR reply handling: " << answer);
        Helper::Reply const nilReply(Helper::Error);
        context->clientStoreIdDone(nilReply);
    }
}