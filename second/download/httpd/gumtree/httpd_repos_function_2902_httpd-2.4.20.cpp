static apr_status_t reqtimeout_eor(ap_filter_t *f, apr_bucket_brigade *bb)
{
    if (!APR_BRIGADE_EMPTY(bb) && AP_BUCKET_IS_EOR(APR_BRIGADE_LAST(bb))) {
        reqtimeout_con_cfg *ccfg = f->ctx;
        ccfg->timeout_at = 0;
    }
    return ap_pass_brigade(f->next, bb);
}