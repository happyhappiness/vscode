apr_status_t h2_conn_run(struct h2_ctx *ctx, conn_rec *c)
{
    apr_status_t status;
    int mpm_state = 0;
    
    do {
        if (c->cs) {
            c->cs->sense = CONN_SENSE_DEFAULT;
        }
        status = h2_session_process(h2_ctx_session_get(ctx), async_mpm);
        
        if (APR_STATUS_IS_EOF(status)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03045)
                          "h2_session(%ld): process, closing conn", c->id);
            c->keepalive = AP_CONN_CLOSE;
        }
        else {
            c->keepalive = AP_CONN_KEEPALIVE;
        }
        
        if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
            break;
        }
    } while (!async_mpm
             && c->keepalive == AP_CONN_KEEPALIVE 
             && mpm_state != AP_MPMQ_STOPPING);
    
    return DONE;
}