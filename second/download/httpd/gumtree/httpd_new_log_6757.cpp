ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, slave,
                  "h2_stream(%s): destroy slave", 
                  apr_table_get(slave->notes, H2_TASK_ID_NOTE));