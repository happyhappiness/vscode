ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_conn(%ld), has connection filter %s",
                          session->id, filter->frec->name);