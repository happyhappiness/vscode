void
Auth::Ntlm::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, Http::HdrType hdrType, HttpRequest * request)
{
    if (!authenticateProgram)
        return;

    /* Need keep-alive */
    if (!request->flags.proxyKeepalive && request->flags.mustKeepalive)
        return;

    /* New request, no user details */
    if (auth_user_request == NULL) {
        debugs(29, 9, HERE << "Sending type:" << hdrType << " header: 'NTLM'");
        httpHeaderPutStrf(&rep->header, hdrType, "NTLM");

        if (!keep_alive) {
            /* drop the connection */
            request->flags.proxyKeepalive = false;
        }
    } else {
        Auth::Ntlm::UserRequest *ntlm_request = dynamic_cast<Auth::Ntlm::UserRequest *>(auth_user_request.getRaw());
        assert(ntlm_request != NULL);

        switch (ntlm_request->user()->credentials()) {

        case Auth::Failed:
            /* here it makes sense to drop the connection, as auth is
             * tied to it, even if MAYBE the client could handle it - Kinkie */
            request->flags.proxyKeepalive = false;
        /* fall through */

        case Auth::Ok:
        /* Special case: authentication finished OK but disallowed by ACL.
         * Need to start over to give the client another chance.
         */
        /* fall through */

        case Auth::Unchecked:
            /* semantic change: do not drop the connection.
             * 2.5 implementation used to keep it open - Kinkie */
            debugs(29, 9, HERE << "Sending type:" << hdrType << " header: 'NTLM'");
            httpHeaderPutStrf(&rep->header, hdrType, "NTLM");
            break;

        case Auth::Handshake:
            /* we're waiting for a response from the client. Pass it the blob */
            debugs(29, 9, HERE << "Sending type:" << hdrType << " header: 'NTLM " << ntlm_request->server_blob << "'");
            httpHeaderPutStrf(&rep->header, hdrType, "NTLM %s", ntlm_request->server_blob);
            safe_free(ntlm_request->server_blob);
            break;

        default:
            debugs(29, DBG_CRITICAL, "NTLM Auth fixHeader: state " << ntlm_request->user()->credentials() << ".");
            fatal("unexpected state in AuthenticateNTLMFixErrorHeader.\n");
        }
    }
}