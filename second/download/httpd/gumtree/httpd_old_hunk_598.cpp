    }
    r->hostname = host;
    return;

bad:
    r->status = HTTP_BAD_REQUEST;
    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                  "Client sent malformed Host header");
    return;
}


/* return 1 if host matches ServerName or ServerAliases */
