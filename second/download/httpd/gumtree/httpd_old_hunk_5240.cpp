        }
        else if (body && !strcmp(pair->name, body) && sent_body) {
            *sent_body = pair->value;
        }
    }

    /* set the user, even though the user is unauthenticated at this point */
    if (*sent_user) {
        r->user = (char *) *sent_user;
    }

    /* a missing username or missing password means auth denied */
    if (!sent_user || !*sent_user || !sent_pw || !*sent_pw) {
        return HTTP_UNAUTHORIZED;
    }

    /*
     * save away the username, password, mimetype and method, so that they
     * are available should the auth need to be run again.
