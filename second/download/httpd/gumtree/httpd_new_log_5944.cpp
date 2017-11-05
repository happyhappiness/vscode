ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
                  "h2_task: creating conn, master=%ld, sid=%ld, logid=%s", 
                  master->id, c->id, c->log_id);