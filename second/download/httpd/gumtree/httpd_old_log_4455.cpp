ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_ENOTIMPL, r->server,
                     "proxy: client %s (%s) requested Transfer-Encoding "
                     "chunked body with Content-Length (C-L ignored)",
                     c->remote_ip, c->remote_host ? c->remote_host: "");