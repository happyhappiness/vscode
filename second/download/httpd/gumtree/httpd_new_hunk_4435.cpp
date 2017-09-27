        
        if (cs) {
            cs->state = CONN_STATE_HANDLER;
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_task(%s): start process_request", task->id);
    
        ap_process_request(r);
        if (task->frozen) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          "h2_task(%s): process_request frozen", task->id);
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          "h2_task(%s): process_request done", task->id);
        }
        
        /* After the call to ap_process_request, the
         * request pool will have been deleted.  We set
         * r=NULL here to ensure that any dereference
         * of r that might be added later in this function
         * will result in a segfault immediately instead
