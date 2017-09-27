            checked_standby = checking_standby++;
        }
        cur_lbset++;
    } while (cur_lbset <= max_lbset && !mycandidate);

    if (mycandidate) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: bytraffic selected worker \"%s\" : busy %" APR_SIZE_T_FMT,
                     mycandidate->name, mycandidate->s->busy);

    }

    return mycandidate;
}

static apr_status_t reset(proxy_balancer *balancer, server_rec *s) {
        return APR_SUCCESS;
}

static apr_status_t age(proxy_balancer *balancer, server_rec *s) {
        return APR_SUCCESS;
}

