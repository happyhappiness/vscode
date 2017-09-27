        else {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          "h2_task(%s): process_request done", task->id);
        }
        
        /* After the call to ap_process_request, the
         * request pool will have been deleted.  We set
         * r=NULL here to ensure that any dereference
         * of r that might be added later in this function
         * will result in a segfault immediately instead
         * of nondeterministic failures later.
         */
        if (cs) 
