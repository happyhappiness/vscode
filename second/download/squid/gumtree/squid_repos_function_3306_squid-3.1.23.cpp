void
clientReplyContext::setReplyToError(
    err_type err, http_status status, const HttpRequestMethod& method, char const *uri,
    IpAddress &addr, HttpRequest * failedrequest, const char *unparsedrequest,
    AuthUserRequest * auth_user_request)
{
    ErrorState *errstate =
        clientBuildError(err, status, uri, addr, failedrequest);

    if (unparsedrequest)
        errstate->request_hdrs = xstrdup(unparsedrequest);

    if (status == HTTP_NOT_IMPLEMENTED && http->request)
        /* prevent confusion over whether we default to persistent or not */
        http->request->flags.proxy_keepalive = 0;

    http->al.http.code = errstate->httpStatus;

    createStoreEntry(method, request_flags());

    if (auth_user_request) {
        errstate->auth_user_request = auth_user_request;
        AUTHUSERREQUESTLOCK(errstate->auth_user_request, "errstate");
    }

    assert(errstate->callback_data == NULL);
    errorAppendEntry(http->storeEntry(), errstate);
    /* Now the caller reads to get this */
}