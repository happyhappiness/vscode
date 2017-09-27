
    /* set the user, even though the user is unauthenticated at this point */
    if (user && *user) {
        r->user = (char *) *user;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                  "from session: " MOD_SESSION_USER ": %s, " MOD_SESSION_PW
                  ": %s, " MOD_AUTH_FORM_HASH ": %s",
                  user ? *user : "<null>", pw ? *pw : "<null>",
                  hash ? *hash : "<null>");

    return APR_SUCCESS;

}

/**
 * Isolate the username and password in a POSTed form with the
