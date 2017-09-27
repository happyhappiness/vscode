                set_session_auth(r, sent_user, sent_pw, conf->site);
                if (sent_loc) {
                    apr_table_set(r->headers_out, "Location", sent_loc);
                    return HTTP_MOVED_TEMPORARILY;
                }
                if (conf->loginsuccess) {
                    apr_table_set(r->headers_out, "Location", conf->loginsuccess);
                    return HTTP_MOVED_TEMPORARILY;
                }
            }
        }

    }

    /*
     * did the admin prefer to be redirected to the login page on failure
     * instead?
     */
    if (HTTP_UNAUTHORIZED == rv && conf->loginrequired) {
        apr_table_set(r->headers_out, "Location", conf->loginrequired);
        return HTTP_MOVED_TEMPORARILY;
    }

    /* did the user ask to be redirected on login success? */
    if (sent_loc) {
        apr_table_set(r->headers_out, "Location", sent_loc);
        rv = HTTP_MOVED_TEMPORARILY;
