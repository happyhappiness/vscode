void
AuthNegotiateConfig::fixHeader(AuthUserRequest *auth_user_request, HttpReply *rep, http_hdr_type reqType, HttpRequest * request)
{
    AuthNegotiateUserRequest *negotiate_request;

    if (!authenticate)
        return;

    /* Need keep-alive */
    if (!request->flags.proxy_keepalive && request->flags.must_keepalive)
        return;

    /* New request, no user details */
    if (auth_user_request == NULL) {
        debugs(29, 9, "AuthNegotiateConfig::fixHeader: Sending type:" << reqType << " header: 'Negotiate'");
        httpHeaderPutStrf(&rep->header, reqType, "Negotiate");

        if (!keep_alive) {
            /* drop the connection */
            rep->header.delByName("keep-alive");
            request->flags.proxy_keepalive = 0;
        }
    } else {
        negotiate_request = dynamic_cast<AuthNegotiateUserRequest *>(auth_user_request);

        assert(negotiate_request != NULL);

        switch (negotiate_request->auth_state) {

        case AUTHENTICATE_STATE_FAILED:
            /* here it makes sense to drop the connection, as auth is
             * tied to it, even if MAYBE the client could handle it - Kinkie */
            rep->header.delByName("keep-alive");
            request->flags.proxy_keepalive = 0;
            /* fall through */

        case AUTHENTICATE_STATE_DONE:
            /* Special case: authentication finished OK but disallowed by ACL.
             * Need to start over to give the client another chance.
             */

            if (negotiate_request->server_blob) {
                debugs(29, 9, "authenticateNegotiateFixErrorHeader: Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
                httpHeaderPutStrf(&rep->header, reqType, "Negotiate %s", negotiate_request->server_blob);
                safe_free(negotiate_request->server_blob);
            } else {
                debugs(29, 9, "authenticateNegotiateFixErrorHeader: Connection authenticated");
                httpHeaderPutStrf(&rep->header, reqType, "Negotiate");
            }

            break;

        case AUTHENTICATE_STATE_NONE:
            /* semantic change: do not drop the connection.
             * 2.5 implementation used to keep it open - Kinkie */
            debugs(29, 9, "AuthNegotiateConfig::fixHeader: Sending type:" << reqType << " header: 'Negotiate'");
            httpHeaderPutStrf(&rep->header, reqType, "Negotiate");
            break;

        case AUTHENTICATE_STATE_IN_PROGRESS:
            /* we're waiting for a response from the client. Pass it the blob */
            debugs(29, 9, "AuthNegotiateConfig::fixHeader: Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
            httpHeaderPutStrf(&rep->header, reqType, "Negotiate %s", negotiate_request->server_blob);
            safe_free(negotiate_request->server_blob);
            break;


        default:
            debugs(29, 0, "AuthNegotiateConfig::fixHeader: state " << negotiate_request->auth_state << ".");
            fatal("unexpected state in AuthenticateNegotiateFixErrorHeader.\n");
        }
    }
}