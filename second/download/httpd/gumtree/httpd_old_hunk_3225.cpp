        else {
            /* If pok is not NULL response was direct from a responder and
             * the times should be valide. If pok is NULL the response was
             * retrieved from cache and it is expected to subsequently expire
             */
            if (pok) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                             "stapling_check_response: response times invalid");
            } 
            else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "stapling_check_response: cached response expired");
            }

            OCSP_BASICRESP_free(bs);
            return SSL_TLSEXT_ERR_NOACK;
        }
