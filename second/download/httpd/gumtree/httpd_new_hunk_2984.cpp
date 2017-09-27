            /* Allow "error-notes" string to be printed by ap_send_error_response()
             * Note; this goes nowhere, canned error response need an overhaul.
             */
            apr_table_setn(r->notes, "error-notes",
                           "TRACE with request body is not allowed");
            apr_table_setn(r->notes, "verbose-error-to", "*");
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01140)
                          "TRACE with request body is not allowed");
            return HTTP_REQUEST_ENTITY_TOO_LARGE;
        }
    }

    uri = r->filename + 6;
    p = strchr(uri, ':');
    if (p == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01141)
                      "proxy_handler no URL in %s", r->filename);
        return HTTP_BAD_REQUEST;
    }

    /* If the host doesn't have a domain name, add one and redirect. */
    if (conf->domain != NULL) {
