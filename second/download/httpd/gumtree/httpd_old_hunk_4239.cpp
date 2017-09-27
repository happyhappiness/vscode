                                   h2_task **ptask)
{   
    h2_ngn_entry *entry;
    
    AP_DEBUG_ASSERT(ngn);
    *ptask = NULL;
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, shed->c,
                  "h2_ngn_shed(%ld): pull task for engine %s, shutdown=%d", 
                  shed->c->id, ngn->id, want_shutdown);
    if (shed->aborted) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, shed->c,
                      "h2_ngn_shed(%ld): abort while pulling requests %s", 
                      shed->c->id, ngn->id);
        ngn->shutdown = 1;
        return APR_ECONNABORTED;
    }
    
