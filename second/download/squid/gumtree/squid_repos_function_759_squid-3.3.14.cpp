void
ClientRequestContext::clientRedirectDone(char *result)
{
    HttpRequest *old_request = http->request;
    debugs(85, 5, "clientRedirectDone: '" << http->uri << "' result=" << (result ? result : "NULL"));
    assert(redirect_state == REDIRECT_PENDING);
    redirect_state = REDIRECT_DONE;

    if (result) {
        http_status status = (http_status) atoi(result);

        if (status == HTTP_MOVED_PERMANENTLY
                || status == HTTP_MOVED_TEMPORARILY
                || status == HTTP_SEE_OTHER
                || status == HTTP_PERMANENT_REDIRECT
                || status == HTTP_TEMPORARY_REDIRECT) {
            char *t = result;

            if ((t = strchr(result, ':')) != NULL) {
                http->redirect.status = status;
                http->redirect.location = xstrdup(t + 1);
                // TODO: validate the URL produced here is RFC 2616 compliant absolute URI
            } else {
                debugs(85, DBG_CRITICAL, "ERROR: URL-rewrite produces invalid " << status << " redirect Location: " << result);
            }
        } else if (strcmp(result, http->uri)) {
            // XXX: validate the URL properly *without* generating a whole new request object right here.
            // XXX: the clone() should be done only AFTER we know the new URL is valid.
            HttpRequest *new_request = old_request->clone();
            if (urlParse(old_request->method, result, new_request)) {
                debugs(61,2, HERE << "URL-rewriter diverts URL from " << urlCanonical(old_request) << " to " << urlCanonical(new_request));

                // update the new request to flag the re-writing was done on it
                new_request->flags.redirected = 1;

                // unlink bodypipe from the old request. Not needed there any longer.
                if (old_request->body_pipe != NULL) {
                    old_request->body_pipe = NULL;
                    debugs(61,2, HERE << "URL-rewriter diverts body_pipe " << new_request->body_pipe <<
                           " from request " << old_request << " to " << new_request);
                }

                // update the current working ClientHttpRequest fields
                safe_free(http->uri);
                http->uri = xstrdup(urlCanonical(new_request));
                HTTPMSGUNLOCK(old_request);
                http->request = HTTPMSGLOCK(new_request);
            } else {
                debugs(85, DBG_CRITICAL, "ERROR: URL-rewrite produces invalid request: " <<
                       old_request->method << " " << result << " " << old_request->http_ver);
                delete new_request;
            }
        }
    }

    /* FIXME PIPELINE: This is innacurate during pipelining */

    if (http->getConn() != NULL && Comm::IsConnOpen(http->getConn()->clientConnection))
        fd_note(http->getConn()->clientConnection->fd, http->uri);

    assert(http->uri);

    http->doCallouts();
}