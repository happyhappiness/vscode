        /* we have been given a blob to send to the client */
        if (arg) {
            *arg = '\0';
            ++arg;
        }
        safe_free(lm_request->server_blob);
        lm_request->request->flags.must_keepalive = 1;
        if (lm_request->request->flags.proxy_keepalive) {
            lm_request->server_blob = xstrdup(blob);
            auth_user_request->user()->credentials(Auth::Handshake);
            auth_user_request->denyMessage("Authentication in progress");
            debugs(29, 4, HERE << "Need to challenge the client with a server blob '" << blob << "'");
        } else {
            auth_user_request->user()->credentials(Auth::Failed);
