            
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
    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02666)
                  "Websocket: Upgrade from HTTP to Websocket failed");
    return 0;
}

static apr_status_t lua_websocket_readbytes(conn_rec* c, char* buffer, 
        apr_off_t len) 
{
