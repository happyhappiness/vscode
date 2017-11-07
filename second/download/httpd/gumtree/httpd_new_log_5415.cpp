ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, slave,
                  "h2_slave_conn(%ld): destroy (task=%s)", slave->id,
                  apr_table_get(slave->notes, H2_TASK_ID_NOTE));