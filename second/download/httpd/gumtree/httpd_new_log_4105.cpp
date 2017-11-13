ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                   "ajp_marshal_into_msgb: Header[%d] [%s] = [%s]",
                   i, elts[i].key, elts[i].val);