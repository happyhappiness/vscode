
    /* set the user, even though the user is unauthenticated at this point */
    if (user && *user) {
        r->user = (char *) *user;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "from notes: user: %s, pw: %s, method: %s, mimetype: %s",
                  user ? *user : "<null>", pw ? *pw : "<null>",
                  method ? *method : "<null>", mimetype ? *mimetype : "<null>");

}

