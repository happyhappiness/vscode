void
Auth::Negotiate::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type reqType, HttpRequest * request)
{
    if (!authenticateProgram)
        return;

    /* Need keep-alive */
    if (!request->flags.proxyKeepalive && request->flags.mustKeepalive)
        return;

    /* New request, no user details */
    if (auth_user_request == NULL) {
        debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate'");
        httpHeaderPutStrf(&rep->header, reqType, "Negotiate");

        if (!keep_alive) {
            /* drop the connection */
            rep->header.delByName("keep-alive");
            request->flags.proxyKeepalive = 0;
        }
    } else {
        Auth::Negotiate::UserRequest *negotiate_request = dynamic_cast<Auth::Negotiate::UserRequest *>(auth_user_request.getRaw());
        assert(negotiate_request != NULL);

        switch (negotiate_request->user()->credentials()) {

        case Auth::Failed:
            /* here it makes sense to drop the connection, as auth is
             * tied to it, even if MAYBE the client could handle it - Kinkie */
            rep->header.delByName("keep-alive");
            request->flags.proxyKeepalive = 0;
            /* fall through */

        case Auth::Ok:
            /* Special case: authentication finished OK but disallowed by ACL.
             * Need to start over to give the client another chance.
             */
            if (negotiate_request->server_blob) {
                debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
                httpHeaderPutStrf(&rep->header, reqType, "Negotiate %s", negotiate_request->server_blob);
                safe_free(negotiate_request->server_blob);
            } else {
                debugs(29, 9, HERE << "Connection authenticated");
                httpHeaderPutStrf(&rep->header, reqType, "Negotiate");
            }
            break;

        case Auth::Unchecked:
            /* semantic change: do not drop the connection.
             * 2.5 implementation used to keep it open - Kinkie */
            debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate'");
            httpHeaderPutStrf(&rep->header, reqType, "Negotiate");
            break;

        case Auth::Handshake:
            /* we're waiting for a response from the client. Pass it the blob */
            debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
            httpHeaderPutStrf(&rep->header, reqType, "Negotiate %s", negotiate_request->server_blob);
            safe_free(negotiate_request->server_blob);
            break;

        default:
            debugs(29, DBG_CRITICAL, "ERROR: Negotiate auth fixHeader: state " << negotiate_request->user()->credentials() << ".");
            fatal("unexpected state in AuthenticateNegotiateFixErrorHeader.\n");
        }
    }
}