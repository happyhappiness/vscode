
                    last_broken_addr = request->client_addr;
                }
            }
        } else {
            auth_user->credentials(Auth::Failed);
            digest_request->flags.invalid_password = true;
            digest_request->setDenyMessage("Incorrect password");
            return;
        }
    }

    /* check for stale nonce */
    /* check Auth::Pending to avoid loop */

    if (!authDigestNonceIsValid(digest_request->nonce, digest_request->nc) && user()->credentials() != Auth::Pending) {
        debugs(29, 3, auth_user->username() << "' validated OK but nonce stale: " << digest_request->nonceb64);
        /* Pending prevent banner and makes a ldap control */
        auth_user->credentials(Auth::Pending);
        nonce->flags.valid = false;
        authDigestNoncePurge(nonce);
        return;
    }

    auth_user->credentials(Auth::Ok);

    /* password was checked and did match */
