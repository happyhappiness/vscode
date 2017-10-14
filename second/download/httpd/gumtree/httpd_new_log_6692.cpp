ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "RewriteRule '%s' and URI '%s' "
                              "exceeded maximum length (%d)", 
                              p->pattern, r->uri, 2*r->server->limit_req_line );