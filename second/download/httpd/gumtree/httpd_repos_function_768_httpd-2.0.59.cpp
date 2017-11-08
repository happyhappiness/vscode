static void ssl_configure_env(request_rec *r, SSLConnRec *sslconn)
{
    int i;
    const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
    const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;

    sslconn->shutdown_type = SSL_SHUTDOWN_TYPE_STANDARD;

    for (i = 0; i < arr->nelts; i++) {
        const char *key = elts[i].key;

        switch (*key) {
          case 's':
            /* being case-sensitive here.
             * and not checking for the -shutdown since these are the only
             * SetEnvIf "flags" we support
             */
            if (!strncmp(key+1, "sl-", 3)) {
                key += 4;
                if (!strncmp(key, "unclean", 7)) {
                    sslconn->shutdown_type = SSL_SHUTDOWN_TYPE_UNCLEAN;
                }
                else if (!strncmp(key, "accurate", 8)) {
                    sslconn->shutdown_type = SSL_SHUTDOWN_TYPE_ACCURATE;
                }
                return; /* should only ever be one ssl-*-shutdown */
            }
            break;
        }
    }
}