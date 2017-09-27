    }
    apr_pool_userdata_set(object, raw_key, NULL, r->server->process->pool);
    apr_thread_mutex_unlock(lua_ivm_mutex);
    return 0;
}

static int lua_get_cookie(lua_State *L) 
{
    const char *key, *cookie;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    key = luaL_checkstring(L, 2);
    cookie = NULL;
    ap_cookie_read(r, key, &cookie, 0);
    if (cookie != NULL) {
        lua_pushstring(L, cookie);
        return 1;
    }
    return 0;
}

static int lua_set_cookie(lua_State *L) 
{
    const char *key, *value, *out, *strexpires;
    int secure, expires;
    char cdate[APR_RFC822_DATE_LEN+1];
    apr_status_t rv;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    key = luaL_checkstring(L, 2);
    value = luaL_checkstring(L, 3);
    secure = 0;
    if (lua_isboolean(L, 4)) {
        secure = lua_toboolean(L, 4);
    }
    expires = luaL_optinteger(L, 5, 0);
    strexpires = "";
    if (expires > 0) {
        rv = apr_rfc822_date(cdate, apr_time_from_sec(expires));
        if (rv == APR_SUCCESS) {
            strexpires = apr_psprintf(r->pool, "Expires=%s", cdate);
        }
    }
    out = apr_psprintf(r->pool, "%s=%s; %s %s", key, value, secure ? "Secure;" : "", expires ? strexpires : "");
    apr_table_set(r->headers_out, "Set-Cookie", out);
    return 0;
}

static apr_uint64_t ap_ntoh64(const apr_uint64_t *input)
{
    apr_uint64_t rval;
    unsigned char *data = (unsigned char *)&rval;
    if (APR_IS_BIGENDIAN) {
        return *input;
    }

    data[0] = *input >> 56;
    data[1] = *input >> 48;
    data[2] = *input >> 40;
    data[3] = *input >> 32;
    data[4] = *input >> 24;
    data[5] = *input >> 16;
    data[6] = *input >> 8;
    data[7] = *input >> 0;

    return rval;
}

static int lua_websocket_greet(lua_State *L)
{
    const char *key = NULL;
    unsigned char digest[APR_SHA1_DIGESTSIZE];
    apr_sha1_ctx_t sha1;
    char           *encoded;
    int encoded_len;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    key = apr_table_get(r->headers_in, "Sec-WebSocket-Key");
    if (key != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                    "Websocket: Got websocket key: %s", key);
        key = apr_pstrcat(r->pool, key, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 
                NULL);
        apr_sha1_init(&sha1);
        apr_sha1_update(&sha1, key, strlen(key));
        apr_sha1_final(digest, &sha1);
        encoded_len = apr_base64_encode_len(APR_SHA1_DIGESTSIZE);
        if (encoded_len) {
            encoded = apr_palloc(r->pool, encoded_len);
            encoded_len = apr_base64_encode(encoded, (char*) digest, APR_SHA1_DIGESTSIZE);
            r->status = 101;
            apr_table_set(r->headers_out, "Upgrade", "websocket");
            apr_table_set(r->headers_out, "Connection", "Upgrade");
            apr_table_set(r->headers_out, "Sec-WebSocket-Accept", encoded);
            
            /* Trick httpd into NOT using the chunked filter, IMPORTANT!!!111*/
            apr_table_set(r->headers_out, "Transfer-Encoding", "chunked");
            
            r->clength = 0;
            r->bytes_sent = 0;
            r->read_chunked = 0;
            ap_rflush(r);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                    "Websocket: Upgraded from HTTP to Websocket");
            lua_pushboolean(L, 1);
            return 1;
        }
    }
    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, 
                    "Websocket: Upgrade from HTTP to Websocket failed");
    return 0;
}

static apr_status_t lua_websocket_readbytes(conn_rec* c, char* buffer, 
        apr_off_t len) 
{
    apr_bucket_brigade *brigade = apr_brigade_create(c->pool, c->bucket_alloc);
    apr_status_t rv;
    rv = ap_get_brigade(c->input_filters, brigade, AP_MODE_READBYTES, 
            APR_BLOCK_READ, len);
    if (rv == APR_SUCCESS) {
        if (!APR_BRIGADE_EMPTY(brigade)) {
            apr_bucket* bucket = APR_BRIGADE_FIRST(brigade);
            const char* data = NULL;
            apr_size_t data_length = 0;
            rv = apr_bucket_read(bucket, &data, &data_length, APR_BLOCK_READ);
            if (rv == APR_SUCCESS) {
                memcpy(buffer, data, len);
            }
            apr_bucket_delete(bucket);
        }
    }
    apr_brigade_cleanup(brigade);
    return rv;
}

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
                }
                else {
                    rv = lua_websocket_readbytes(r->connection, buffer, 
                            remaining);
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                    "Websocket: SSL Frame contained %lu bytes, "\
                            "pushed to Lua stack", 
                        remaining);
                }
                if (mask) {
                    for (n = 0; n < plen; n++) {
                        buffer[n] ^= mask_bytes[n%4];
                    }
                }
                
                lua_pushlstring(L, buffer, (size_t) plen); /* push to stack */
                lua_pushboolean(L, fin); /* push FIN bit to stack as boolean */
                return 2;
            }
            
            
            /* Decide if we need to react to the opcode or not */
            if (opcode == 0x09) { /* ping */
                char frame[2];
                plen = 2;
                frame[0] = 0x8A;
                frame[1] = 0;
                apr_socket_send(sock, frame, &plen); /* Pong! */
                lua_websocket_read(L); /* read the next frame instead */
            }
        }
    }
    return 0;
}


static int lua_websocket_write(lua_State *L) 
{
    const char *string;
    apr_status_t rv;
    size_t len;
    int raw = 0;
    char prelude;
    request_rec *r = (request_rec *) lua_unboxpointer(L, 1);
    
    if (lua_isboolean(L, 3)) {
        raw = lua_toboolean(L, 3);
    }
    string = lua_tolstring(L, 2, &len);
    
    if (raw != 1) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                        "Websocket: Writing framed message to client");
        
        prelude = 0x81; /* text frame, FIN */
        ap_rputc(prelude, r);
        if (len < 126) {
            ap_rputc(len, r);
        } 
        else if (len < 65535) {
            apr_uint16_t slen = len;
            ap_rputc(126, r); 
            slen = htons(slen);
            ap_rwrite((char*) &slen, 2, r);
        }
        else {
            apr_uint64_t llen = len;
            ap_rputc(127, r);
            llen = ap_ntoh64(&llen); /* ntoh doubles as hton */
            ap_rwrite((char*) &llen, 8, r);
        }
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                        "Websocket: Writing raw message to client");
    }
    ap_rwrite(string, len, r);
    rv = ap_rflush(r);
    if (rv == APR_SUCCESS) {
        lua_pushboolean(L, 1);
    }
    else {
        lua_pushboolean(L, 0);
    }
    return 1;
}


static int lua_websocket_close(lua_State *L) 
{
    apr_socket_t *sock;
    char prelude[2];
    request_rec *r = (request_rec *) lua_unboxpointer(L, 1);
    
    sock = ap_get_conn_socket(r->connection);
    
    /* Send a header that says: socket is closing. */
    prelude[0] = 0x88; /* closing socket opcode */
    prelude[1] = 0; /* zero length frame */
    ap_rwrite(prelude, 2, r);
    
    /* Close up tell the MPM and filters to back off */
    apr_socket_close(sock);
    r->output_filters = NULL;
    r->connection->keepalive = AP_CONN_CLOSE;
    ap_destroy_sub_req(r);
    return DONE;
}


static int lua_websocket_ping(lua_State *L) 
{
    apr_socket_t *sock;
    apr_size_t plen;
    char prelude[2];
    apr_status_t rv;
    request_rec *r = ap_lua_check_request_rec(L, 1);
    sock = ap_get_conn_socket(r->connection);
    
    /* Send a header that says: PING. */
    prelude[0] = 0x89; /* ping  opcode */
    prelude[1] = 0;
    plen = 2;
    apr_socket_send(sock, prelude, &plen);
    
    
    /* Get opcode and FIN bit from pong */
    plen = 2;
    rv = apr_socket_recv(sock, prelude, &plen);
    if (rv == APR_SUCCESS) {
        unsigned char opcode = prelude[0];
        unsigned char len = prelude[1];
        unsigned char mask = len >> 7;
        if (mask) len -= 128;
        plen = len;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, 
                        "Websocket: Got PONG opcode: %x", opcode);
        if (opcode == 0x8A) {
            lua_pushboolean(L, 1);
        }
        else {
            lua_pushboolean(L, 0);
        }
        if (plen > 0) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                        "Websocket: Reading %lu bytes of PONG", plen);
            return 1;
        }
        if (mask) {
            plen = 2;
            apr_socket_recv(sock, prelude, &plen);
            plen = 2;
            apr_socket_recv(sock, prelude, &plen);
        }
    }
    else {
        lua_pushboolean(L, 0);
    }
    return 1;
}


#define APLUA_REQ_TRACE(lev) static int req_trace##lev(lua_State *L)  \
{                                                               \
    return req_log_at(L, APLOG_TRACE##lev);                     \
}

APLUA_REQ_TRACE(1)
