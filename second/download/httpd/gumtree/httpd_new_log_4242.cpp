ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01178) "Doing balancers create: %d, %d (%d)",
                         (int)ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                         (int)conf->balancers->nelts, conf->max_balancers);