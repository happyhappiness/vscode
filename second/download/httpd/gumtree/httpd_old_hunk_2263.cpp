
    /* set the user, even though the user is unauthenticated at this point */
    if (user && *user) {
        r->user = (char *) *user;
    }

    return APR_SUCCESS;

}

/**
 * Isolate the username and password in a POSTed form with the
