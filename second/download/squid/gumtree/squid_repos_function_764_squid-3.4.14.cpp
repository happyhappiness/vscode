static void
clientStoreIdAccessCheckDone(allow_t answer, void *data)
{
    ClientRequestContext *context = static_cast<ClientRequestContext *>(data);
    ClientHttpRequest *http = context->http;
    context->acl_checklist = NULL;

    if (answer == ACCESS_ALLOWED)
        storeIdStart(http, clientStoreIdDoneWrapper, context);
    else {
        debugs(85, 3, "access denied expected ERR reply handling: " << answer);
        HelperReply nilReply;
        nilReply.result = HelperReply::Error;
        context->clientStoreIdDone(nilReply);
    }
}