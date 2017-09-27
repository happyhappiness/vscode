            /* ??? */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03091)
                         "post_config: mpm type unknown");
            break;
    }
    
    status = h2_h2_init(p, s);
    if (status == APR_SUCCESS) {
        status = h2_switch_init(p, s);
    }
    if (status == APR_SUCCESS) {
        status = h2_task_init(p, s);
