apr_status_t h2_conn_run(struct h2_ctx *ctx, conn_rec *c)
{
    apr_status_t status;
    int mpm_state = 0;
    h2_session *session = h2_ctx_session_get(ctx);
    
    ap_assert(session);
    do {
        if (c->cs) {
            c->cs->sense = CONN_SENSE_DEFAULT;
            c->cs->state = CONN_STATE_HANDLER;
        }
    
        status = h2_session_process(session, async_mpm);
        
        if (APR_STATUS_IS_EOF(status)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, 
                          H2_SSSN_LOG(APLOGNO(03045), session, 
                          "process, closing conn"));
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
    
    if (c->cs) {
        switch (session->state) {
            case H2_SESSION_ST_INIT:
            case H2_SESSION_ST_CLEANUP:
            case H2_SESSION_ST_DONE:
            case H2_SESSION_ST_IDLE:
                c->cs->state = CONN_STATE_WRITE_COMPLETION;
                break;
            case H2_SESSION_ST_BUSY:
            case H2_SESSION_ST_WAIT:
            default:
                c->cs->state = CONN_STATE_HANDLER;
                break;
                
        }
    }
    
    return DONE;
}