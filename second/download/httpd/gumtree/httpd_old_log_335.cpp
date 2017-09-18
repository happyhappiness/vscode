ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                     "proxy: FTP: declining URL %s - proxyhost %s specified:", url, proxyhost);