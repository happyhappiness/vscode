ap_log_cerror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, task->c,
                              APLOGNO(02955) "h2_task(%s): invalid header[%d] '%s'",
                              task->id, i, (char*)hline);