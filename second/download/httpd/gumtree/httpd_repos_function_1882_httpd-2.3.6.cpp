static int send_headers(request_rec *r, proxy_conn_rec *conn)
{
    char *buf, *cp, *bodylen;
    const char *ns_len;
    const apr_array_header_t *env_table;
    const apr_table_entry_t *env;
    int j;
    apr_size_t len, bodylen_size;
    apr_size_t headerlen =   sizeof(CONTENT_LENGTH)
                           + sizeof(SCGI_MAGIC)
                           + sizeof(SCGI_PROTOCOL_VERSION);

    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    /*
     * The header blob basically takes the environment and concatenates
     * keys and values using 0 bytes. There are special treatments here:
     *   - GATEWAY_INTERFACE and SCGI_MAGIC are dropped
     *   - CONTENT_LENGTH is always set and must be sent as the very first
     *     variable
     *
     * Additionally it's wrapped into a so-called netstring (see SCGI spec)
     */
    env_table = apr_table_elts(r->subprocess_env);
    env = (apr_table_entry_t *)env_table->elts;
    for (j = 0; j < env_table->nelts; ++j) {
        if (   (!strcmp(env[j].key, GATEWAY_INTERFACE))
            || (!strcmp(env[j].key, CONTENT_LENGTH))
            || (!strcmp(env[j].key, SCGI_MAGIC))) {
            continue;
        }
        headerlen += strlen(env[j].key) + strlen(env[j].val) + 2;
    }
    bodylen = apr_psprintf(r->pool, "%" APR_OFF_T_FMT, r->remaining);
    bodylen_size = strlen(bodylen) + 1;
    headerlen += bodylen_size;

    ns_len = apr_psprintf(r->pool, "%" APR_SIZE_T_FMT ":", headerlen);
    len = strlen(ns_len);
    headerlen += len + 1; /* 1 == , */
    cp = buf = apr_palloc(r->pool, headerlen);
    memcpy(cp, ns_len, len);
    cp += len;

    memcpy(cp, CONTENT_LENGTH, sizeof(CONTENT_LENGTH));
    cp += sizeof(CONTENT_LENGTH);
    memcpy(cp, bodylen, bodylen_size);
    cp += bodylen_size;
    memcpy(cp, SCGI_MAGIC, sizeof(SCGI_MAGIC));
    cp += sizeof(SCGI_MAGIC);
    memcpy(cp, SCGI_PROTOCOL_VERSION, sizeof(SCGI_PROTOCOL_VERSION));
    cp += sizeof(SCGI_PROTOCOL_VERSION);

    for (j = 0; j < env_table->nelts; ++j) {
        if (   (!strcmp(env[j].key, GATEWAY_INTERFACE))
            || (!strcmp(env[j].key, CONTENT_LENGTH))
            || (!strcmp(env[j].key, SCGI_MAGIC))) {
            continue;
        }
        len = strlen(env[j].key) + 1;
        memcpy(cp, env[j].key, len);
        cp += len;
        len = strlen(env[j].val) + 1;
        memcpy(cp, env[j].val, len);
        cp += len;
    }
    *cp++ = ',';

    return sendall(conn, buf, headerlen, r);
}