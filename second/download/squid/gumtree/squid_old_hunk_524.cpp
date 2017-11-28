    if (auth_user_request == NULL) {
        debugs(29, 9, HERE << "Sending type:" << hdrType << " header: 'NTLM'");
        httpHeaderPutStrf(&rep->header, hdrType, "NTLM");

        if (!keep_alive) {
            /* drop the connection */
            request->flags.proxyKeepalive = 0;
        }
    } else {
        Auth::Ntlm::UserRequest *ntlm_request = dynamic_cast<Auth::Ntlm::UserRequest *>(auth_user_request.getRaw());
        assert(ntlm_request != NULL);

        switch (ntlm_request->user()->credentials()) {

        case Auth::Failed:
            /* here it makes sense to drop the connection, as auth is
             * tied to it, even if MAYBE the client could handle it - Kinkie */
            request->flags.proxyKeepalive = 0;
            /* fall through */

        case Auth::Ok:
            /* Special case: authentication finished OK but disallowed by ACL.
             * Need to start over to give the client another chance.
             */
