static int balancer_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                               apr_pool_t *ptemp)
{

    apr_status_t rv;

    rv = ap_mutex_register(pconf, balancer_mutex_type, NULL,
                               APR_LOCK_DEFAULT, 0);
    if (rv != APR_SUCCESS) {
        return rv;
    }
    set_worker_hc_param_f = APR_RETRIEVE_OPTIONAL_FN(set_worker_hc_param);
    hc_show_exprs_f = APR_RETRIEVE_OPTIONAL_FN(hc_show_exprs);
    hc_select_exprs_f = APR_RETRIEVE_OPTIONAL_FN(hc_select_exprs);
    hc_valid_expr_f = APR_RETRIEVE_OPTIONAL_FN(hc_valid_expr);
    return OK;
}