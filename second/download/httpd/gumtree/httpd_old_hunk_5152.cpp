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
