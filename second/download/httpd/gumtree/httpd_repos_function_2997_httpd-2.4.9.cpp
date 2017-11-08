static const char *construct_key(request_rec *r, const char *context,
                                 const char *user, const char *realm)
{
    /* handle "special" context values */
    if (!strcmp(context, "directory")) {
        /* FIXME: are we at risk of this blowing up? */
        char *new_context;
        char *slash = strrchr(r->uri, '/');
        new_context = apr_palloc(r->pool, slash - r->uri +
                                 strlen(r->server->server_hostname) + 1);
        strcpy(new_context, r->server->server_hostname);
        strncat(new_context, r->uri, slash - r->uri);
        context = new_context;
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