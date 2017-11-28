        }

        if (connection_auth_blocked)
            hdr->refreshMask();
    }

#if USE_AUTH
    /* Handle authentication headers */
    if (http->logType == LOG_TCP_DENIED &&
            ( reply->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED ||
              reply->sline.status == HTTP_UNAUTHORIZED)
       ) {
        /* Add authentication header */
        /*! \todo alter errorstate to be accel on|off aware. The 0 on the next line
         * depends on authenticate behaviour: all schemes to date send no extra
         * data on 407/401 responses, and do not check the accel state on 401/407
         * responses
         */
        authenticateFixHeader(reply, request->auth_user_request, request, 0, 1);
    } else if (request->auth_user_request != NULL)
        authenticateFixHeader(reply, request->auth_user_request, request, http->flags.accel, 0);
#endif

    /* Append X-Cache */
    httpHeaderPutStrf(hdr, HDR_X_CACHE, "%s from %s",
                      is_hit ? "HIT" : "MISS", getMyHostname());

#if USE_CACHE_DIGESTS
