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
