         * (and higher?) we can use the upper 32 bits without fear of collision.
         * 32 bits is just what we need, since a connection can only handle so
         * many streams. 
         */
        int slave_id, free_bits;
        
        if (sizeof(unsigned long) >= 8) {
            free_bits = 32;
            slave_id = task->stream_id;
        }
        else {
            /* Assume we have a more limited number of threads/processes
             * and h2 workers on a 32-bit system. Use the worker instead
             * of the stream id. */
            free_bits = 8;
            slave_id = worker_id; 
        }
        task->c->id = (task->c->master->id << free_bits)^slave_id;
    }
    
    task->input.bb = apr_brigade_create(task->pool, task->c->bucket_alloc);
    if (task->request->serialize) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): serialize request %s %s", 
                      task->id, task->request->method, task->request->path);
        apr_brigade_printf(task->input.bb, NULL, 
                           NULL, "%s %s HTTP/1.1\r\n", 
                           task->request->method, task->request->path);
        apr_table_do(input_ser_header, task, task->request->headers, NULL);
        apr_brigade_puts(task->input.bb, NULL, NULL, "\r\n");
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                  "h2_task(%s): process connection", task->id);
    task->c->current_thread = thread; 
    ap_run_process_connection(task->c);
    
    if (task->frozen) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): process_conn returned frozen task", 
                      task->id);
        /* cleanup delayed */
        return APR_EAGAIN;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_task(%s): processing done", task->id);
        return output_finish(task);
    }
}

static apr_status_t h2_task_process_request(h2_task *task, conn_rec *c)
