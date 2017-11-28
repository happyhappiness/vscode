static void
clientRedirectAccessCheckDone(int answer, void *data)
{
    ClientRequestContext *context = (ClientRequestContext *)data;
    ClientHttpRequest *http = context->http;
    context->acl_checklist = NULL;

    if (answer == ACCESS_ALLOWED)
        redirectStart(http, clientRedirectDoneWrapper, context);
    else
        context->clientRedirectDone(NULL);
}