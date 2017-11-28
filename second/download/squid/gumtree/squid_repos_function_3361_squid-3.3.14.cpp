void
clientReplyContext::setReplyToError(
    err_type err, http_status status, const HttpRequestMethod& method, char const *uri,
    Ip::Address &addr, HttpRequest * failedrequest, const char *unparsedrequest,
#if USE_AUTH
    Auth::UserRequest::Pointer auth_user_request
#else
    void*
#endif
)
{
    ErrorState *errstate = clientBuildError(err, status, uri, addr, failedrequest);

    if (unparsedrequest)
        errstate->request_hdrs = xstrdup(unparsedrequest);

#if USE_AUTH
    errstate->auth_user_request = auth_user_request;
#endif
    setReplyToError(method, errstate);
}