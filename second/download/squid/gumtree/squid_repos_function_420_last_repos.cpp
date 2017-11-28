static void
clientRedirectAccessCheckDone(allow_t answer, void *data)
{
    ClientRequestContext *context = (ClientRequestContext *)data;
    ClientHttpRequest *http = context->http;
    context->acl_checklist = NULL;

    if (answer.allowed())
        redirectStart(http, clientRedirectDoneWrapper, context);
    else {
        Helper::Reply const nilReply(Helper::Error);
        context->clientRedirectDone(nilReply);
    }
}