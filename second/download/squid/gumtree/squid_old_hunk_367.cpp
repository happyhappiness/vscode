Auth::Negotiate::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type reqType, HttpRequest * request)
{
    if (!authenticateProgram)
        return;

    /* Need keep-alive */
    if (!request->flags.proxy_keepalive && request->flags.must_keepalive)
        return;

    /* New request, no user details */
    if (auth_user_request == NULL) {
        debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate'");
        httpHeaderPutStrf(&rep->header, reqType, "Negotiate");

        if (!keep_alive) {
            /* drop the connection */
            rep->header.delByName("keep-alive");
            request->flags.proxy_keepalive = 0;
        }
    } else {
        Auth::Negotiate::UserRequest *negotiate_request = dynamic_cast<Auth::Negotiate::UserRequest *>(auth_user_request.getRaw());
        assert(negotiate_request != NULL);

        switch (negotiate_request->user()->credentials()) {

        case Auth::Failed:
            /* here it makes sense to drop the connection, as auth is
             * tied to it, even if MAYBE the client could handle it - Kinkie */
            rep->header.delByName("keep-alive");
            request->flags.proxy_keepalive = 0;
            /* fall through */

        case Auth::Ok:
            /* Special case: authentication finished OK but disallowed by ACL.
             * Need to start over to give the client another chance.
             */
