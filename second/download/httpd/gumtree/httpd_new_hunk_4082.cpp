    apr_sha1_ctx_t sha1;
    char           *encoded;
    int encoded_len;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    key = apr_table_get(r->headers_in, "Sec-WebSocket-Key");
    if (key != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03011) 
                      "Websocket: Got websocket key: %s", key);
        key = apr_pstrcat(r->pool, key, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 
                NULL);
        apr_sha1_init(&sha1);
        apr_sha1_update(&sha1, key, strlen(key));
        apr_sha1_final(digest, &sha1);
        encoded_len = apr_base64_encode_len(APR_SHA1_DIGESTSIZE);
