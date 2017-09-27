    int cur_lbset = 0;
    int max_lbset = 0;
    int checking_standby;
    int checked_standby;

    int total_factor = 0;
    
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: Entering bybusyness for BALANCER (%s)",
                 balancer->name);

    /* First try to see if we have available candidate */
    do {

        checking_standby = checked_standby = 0;
        while (!mycandidate && !checked_standby) {
