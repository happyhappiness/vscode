apr_status_t h2_ngn_shed_push_request(h2_ngn_shed *shed, const char *ngn_type, 
                                      request_rec *r, 
                                      http2_req_engine_init *einit) 
{
    h2_req_engine *ngn;
    h2_task *task = h2_ctx_rget_task(r);

    ap_assert(task);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c,
                  "h2_ngn_shed(%ld): PUSHing request (task=%s)", shed->c->id, 
                  task->id);
    if (task->request->serialize) {
        /* Max compatibility, deny processing of this */
        return APR_EOF;
    }
    
    if (task->assigned) {
        --task->assigned->no_assigned;
        --task->assigned->no_live;
        task->assigned = NULL;
    }
    
    if (task->engine) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c, 
                      "h2_ngn_shed(%ld): push task(%s) hosting engine %s " 
                      "already with %d tasks", 
                      shed->c->id, task->id, task->engine->id,
                      task->engine->no_assigned);
        task->assigned = task->engine;
        ngn_add_task(task->engine, task, r);
        return APR_SUCCESS;
    }
    
    ngn = apr_hash_get(shed->ngns, ngn_type, APR_HASH_KEY_STRING);
    if (ngn && !ngn->shutdown) {
        /* this task will be processed in another thread,
         * freeze any I/O for the time being. */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                      "h2_ngn_shed(%ld): pushing request %s to %s", 
                      shed->c->id, task->id, ngn->id);
        if (!h2_task_has_thawed(task)) {
            h2_task_freeze(task);
        }
        ngn_add_task(ngn, task, r);
        return APR_SUCCESS;
    }
    
    /* no existing engine or being shut down, start a new one */
    if (einit) {
        apr_status_t status;
        apr_pool_t *pool = task->pool;
        h2_req_engine *newngn;
        
        newngn = apr_pcalloc(pool, sizeof(*ngn));
        newngn->pool = pool;
        newngn->id   = apr_psprintf(pool, "ngn-%s", task->id);
        newngn->type = apr_pstrdup(pool, ngn_type);
        newngn->c    = task->c;
        newngn->shed = shed;
        newngn->capacity = shed->default_capacity;
        newngn->no_assigned = 1;
        newngn->no_live = 1;
        APR_RING_INIT(&newngn->entries, h2_ngn_entry, link);
        
        status = einit(newngn, newngn->id, newngn->type, newngn->pool,
                       shed->req_buffer_size, r,
                       &newngn->out_consumed, &newngn->out_consumed_ctx);
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, task->c, APLOGNO(03395)
                      "h2_ngn_shed(%ld): create engine %s (%s)", 
                      shed->c->id, newngn->id, newngn->type);
        if (status == APR_SUCCESS) {
            newngn->task = task;
            task->engine = newngn;
            task->assigned = newngn;
            apr_hash_set(shed->ngns, newngn->type, APR_HASH_KEY_STRING, newngn);
        }
        return status;
    }
    return APR_EOF;
}