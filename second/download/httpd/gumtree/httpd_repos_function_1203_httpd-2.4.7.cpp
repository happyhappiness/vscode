static int lua_websocket_read(lua_State *L) 
{
    apr_socket_t *sock;
    apr_status_t rv;
    int n = 0;
    apr_size_t len = 1;
    apr_size_t plen = 0;
    unsigned short payload_short = 0;
    apr_uint64_t payload_long = 0;
    unsigned char *mask_bytes;
    char byte;
    int plaintext;
    
    
    request_rec *r = (request_rec *) lua_unboxpointer(L, 1);
    plaintext = ap_lua_ssl_is_https(r->connection) ? 0 : 1;

    
    mask_bytes = apr_pcalloc(r->pool, 4);
    sock = ap_get_conn_socket(r->connection);

    /* Get opcode and FIN bit */
    if (plaintext) {
        rv = apr_socket_recv(sock, &byte, &len);
    }
    else {
        rv = lua_websocket_readbytes(r->connection, &byte, 1);
    }
    if (rv == APR_SUCCESS) {
        unsigned char fin, opcode, mask, payload;
        fin = byte >> 7;
        opcode = (byte << 4) >> 4;
        
        /* Get the payload length and mask bit */
        if (plaintext) {
            rv = apr_socket_recv(sock, &byte, &len);
        }
        else {
            rv = lua_websocket_readbytes(r->connection, &byte, 1);
        }
        if (rv == APR_SUCCESS) {
            mask = byte >> 7;
            payload = byte - 128;
            plen = payload;
            
            /* Extended payload? */
            if (payload == 126) {
                len = 2;
                if (plaintext) {
                    rv = apr_socket_recv(sock, (char*) &payload_short, &len);
                }
                else {
                    rv = lua_websocket_readbytes(r->connection, 
                        (char*) &payload_short, 2);
                }
                payload_short = ntohs(payload_short);
                
                if (rv == APR_SUCCESS) {
                    plen = payload_short;
                }
                else {
                    return 0;
                }
            }
            /* Super duper extended payload? */
            if (payload == 127) {
                len = 8;
                if (plaintext) {
                    rv = apr_socket_recv(sock, (char*) &payload_long, &len);
                }
                else {
                    rv = lua_websocket_readbytes(r->connection, 
                            (char*) &payload_long, 8);
                }
                if (rv == APR_SUCCESS) {
                    plen = ap_ntoh64(&payload_long);
                }
                else {
                    return 0;
                }
            }
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                    "Websocket: Reading %lu (%s) bytes, masking is %s. %s", 
                    plen,
                    (payload >= 126) ? "extra payload" : "no extra payload", 
                    mask ? "on" : "off", 
                    fin ? "This is a final frame" : "more to follow");
            if (mask) {
                len = 4;
                if (plaintext) {
                    rv = apr_socket_recv(sock, (char*) mask_bytes, &len);
                }
                else {
                    rv = lua_websocket_readbytes(r->connection, 
                            (char*) mask_bytes, 4);
                }
                if (rv != APR_SUCCESS) {
                    return 0;
                }
            }
            if (plen < (HUGE_STRING_LEN*1024) && plen > 0) {
                apr_size_t remaining = plen;
                apr_size_t received;
                apr_off_t at = 0;
                char *buffer = apr_palloc(r->pool, plen+1);
                buffer[plen] = 0;
                
                if (plaintext) {
                    while (remaining > 0) {
                        received = remaining;
                        rv = apr_socket_recv(sock, buffer+at, &received);
                        if (received > 0 ) {
                            remaining -= received;
                            at += received;
                        }
                    }
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                    "Websocket: Frame contained %lu bytes, pushed to Lua stack", 
                        at);
 