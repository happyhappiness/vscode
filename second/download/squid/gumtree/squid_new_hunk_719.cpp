        } else {
            auth_user_request->user()->credentials(Auth::Failed);
            auth_user_request->denyMessage("NTLM authentication requires a persistent connection");
        }
        break;

    case Helper::Okay: {
        /* we're finished, release the helper */
        const char *userLabel = reply.notes.findFirst("user");
        if (!userLabel) {
            auth_user_request->user()->credentials(Auth::Failed);
            safe_free(lm_request->server_blob);
            lm_request->releaseAuthServer();
