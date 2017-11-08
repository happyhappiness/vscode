static const char *construct_key(request_rec *r, const char *context,
                                 const char *user, const char *realm)
{
    /* handle "special" context values */
    if (!strcmp(context, "directory")) {
        /* FIXME: are we at risk of this blowing up? */
        char *slash = strrchr(r->uri, '/');
        context = apr_pstrndup(r->pool, r->uri, slash - r->uri + 1);
    }
    else if (!strcmp(context, "server")) {
        context = r->server->server_hostname;
    }
    /* any other context value is literal */

    if (realm == NULL) {                              /* basic auth */
        return apr_pstrcat(r->pool, context, ":", user, NULL);
    }
    else {                                            /* digest auth */
        return apr_pstrcat(r->pool, context, ":", user, ":", realm, NULL);
    }
}