ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                   "ajp_marshal_into_msgb: Header[%d] [%s] = [%s]",
                   i, elts[i].key, elts[i].val);