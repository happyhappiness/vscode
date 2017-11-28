            fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply.other().content());
            break;
        }

        /* we're finished, release the helper */
        auth_user_request->user()->username(userNote);
        auth_user_request->setDenyMessage("Login successful");
        safe_free(lm_request->server_blob);
        lm_request->server_blob = xstrdup(tokenNote);
        lm_request->releaseAuthServer();

        /* connection is authenticated */
        debugs(29, 4, HERE << "authenticated user " << auth_user_request->user()->username());
        auto local_auth_user = lm_request->user();
        auto cached_user = Auth::Negotiate::User::Cache()->lookup(auth_user_request->user()->userKey());
        if (!cached_user) {
            local_auth_user->addToNameCache();
        } else {
            /* we can't seamlessly recheck the username due to the
             * challenge-response nature of the protocol.
             * Just free the temporary auth_user after merging as
             * much of it new state into the existing one as possible */
            cached_user->absorb(local_auth_user);
            /* from here on we are working with the original cached credentials. */
            local_auth_user = cached_user;
            auth_user_request->user(local_auth_user);
        }
        /* set these to now because this is either a new login from an
         * existing user or a new user */
        local_auth_user->expiretime = current_time.tv_sec;
        auth_user_request->user()->credentials(Auth::Ok);
        debugs(29, 4, HERE << "Successfully validated user via Negotiate. Username '" << auth_user_request->user()->username() << "'");
    }
    break;

    case Helper::Error:
        /* authentication failure (wrong password, etc.) */
        auth_user_request->denyMessageFromHelper("Negotiate", reply);
        auth_user_request->user()->credentials(Auth::Failed);
        safe_free(lm_request->server_blob);
        if (const char *tokenNote = reply.notes.findFirst("token"))
            lm_request->server_blob = xstrdup(tokenNote);
        lm_request->releaseAuthServer();
        debugs(29, 4, "Failed validating user via Negotiate. Result: " << reply);
        break;

    case Helper::Unknown:
        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication Helper '" << reply.whichServer << "' crashed!.");
    /* continue to the next case */

    case Helper::TimedOut:
    case Helper::BrokenHelper:
        /* TODO kick off a refresh process. This can occur after a YR or after
         * a KK. If after a YR release the helper and resubmit the request via
         * Authenticate Negotiate start.
         * If after a KK deny the user's request w/ 407 and mark the helper as
         * Needing YR. */
        if (reply.result == Helper::Unknown)
            auth_user_request->setDenyMessage("Internal Error");
        else
            auth_user_request->denyMessageFromHelper("Negotiate", reply);
        auth_user_request->user()->credentials(Auth::Failed);
        safe_free(lm_request->server_blob);
        lm_request->releaseAuthServer();
        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication validating user. Result: " << reply);
        break;
    }

    if (lm_request->request) {
        HTTPMSGUNLOCK(lm_request->request);
        lm_request->request = NULL;
    }
