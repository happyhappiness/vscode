        *method = (char *) apr_table_get(r->notes, apr_pstrcat(r->pool, authname, "-method", NULL));
    }
    if (mimetype) {
        *mimetype = (char *) apr_table_get(r->notes, apr_pstrcat(r->pool, authname, "-mimetype", NULL));
    }

}

/**
 * Set the auth username and password into the session.
 *
 * If either the username, or the password are NULL, the username
