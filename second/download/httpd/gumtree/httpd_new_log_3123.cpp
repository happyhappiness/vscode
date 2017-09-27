ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                      "Response sent with status %d%s",
		      r->status,
		      APLOGrtrace4(r) ? ", headers:" : "");