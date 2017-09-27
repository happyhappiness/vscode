        }
        else if (body && !strcmp(pair->name, body) && sent_body) {
            *sent_body = pair->value;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "from form: user: %s, pw: %s, method: %s, mimetype: %s, location: %s",
                  sent_user ? *sent_user : "<null>", sent_pw ? *sent_pw : "<null>",
                  sent_method ? *sent_method : "<null>",
                  sent_mimetype ? *sent_mimetype : "<null>",
                  sent_loc ? *sent_loc : "<null>");

    /* set the user, even though the user is unauthenticated at this point */
    if (sent_user && *sent_user) {
        r->user = (char *) *sent_user;
    }

    /* a missing username or missing password means auth denied */
    if (!sent_user || !*sent_user) {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "form parsed, but username field '%s' was missing or empty, unauthorized",
                      username);

        return HTTP_UNAUTHORIZED;
    }
    if (!sent_pw || !*sent_pw) {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "form parsed, but password field '%s' was missing or empty, unauthorized",
                      password);

        return HTTP_UNAUTHORIZED;
    }

    /*
     * save away the username, password, mimetype and method, so that they
     * are available should the auth need to be run again.
