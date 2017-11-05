static apr_status_t check_time_left(reqtimeout_con_cfg *ccfg,
                                    apr_time_t *time_left_p)
{
    *time_left_p = ccfg->timeout_at - apr_time_now();
    if (*time_left_p <= 0)
        return APR_TIMEUP;
    
    if (*time_left_p < apr_time_from_sec(1)) {
        *time_left_p = apr_time_from_sec(1);
    }
    return APR_SUCCESS;
}