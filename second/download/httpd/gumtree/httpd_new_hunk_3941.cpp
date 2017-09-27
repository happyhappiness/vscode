        r->user = (char *) *sent_user;
    }

    /* a missing username or missing password means auth denied */
    if (!sent_user || !*sent_user) {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02982)
                      "form parsed, but username field '%s' was missing or empty, unauthorized",
                      username);

        return HTTP_UNAUTHORIZED;
    }
    if (!sent_pw || !*sent_pw) {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02983)
                      "form parsed, but password field '%s' was missing or empty, unauthorized",
                      password);

        return HTTP_UNAUTHORIZED;
    }

