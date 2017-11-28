        safe_free(lm_request->server_blob);
        lm_request->request->flags.mustKeepalive = true;
        if (lm_request->request->flags.proxyKeepalive) {
            const char *tokenNote = reply.notes.findFirst("token");
            lm_request->server_blob = xstrdup(tokenNote);
            auth_user_request->user()->credentials(Auth::Handshake);
            auth_user_request->setDenyMessage("Authentication in progress");
            debugs(29, 4, HERE << "Need to challenge the client with a server token: '" << tokenNote << "'");
        } else {
            auth_user_request->user()->credentials(Auth::Failed);
            auth_user_request->setDenyMessage("Negotiate authentication requires a persistent connection");
        }
        break;

    case Helper::Okay: {
        const char *userNote = reply.notes.findFirst("user");
        const char *tokenNote = reply.notes.findFirst("token");
