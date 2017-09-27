        newngn->no_live = 1;
        APR_RING_INIT(&newngn->entries, h2_ngn_entry, link);
        
        status = einit(newngn, newngn->id, newngn->type, newngn->pool,
                       shed->req_buffer_size, task->r, 
                       &newngn->out_consumed, &newngn->out_consumed_ctx);
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, task->c, APLOGNO(03395)
                      "h2_ngn_shed(%ld): create engine %s (%s)", 
                      shed->c->id, newngn->id, newngn->type);
        if (status == APR_SUCCESS) {
            AP_DEBUG_ASSERT(task->engine == NULL);
            newngn->task = task;
            task->engine = newngn;
