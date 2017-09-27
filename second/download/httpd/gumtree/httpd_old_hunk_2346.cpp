                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "proxy: *: found forward proxy worker for %s",
                              *url);
                *balancer = NULL;
                *worker = conf->forward;
                access_status = OK;
            }
        }
        else if (r->proxyreq == PROXYREQ_REVERSE) {
            if (conf->reverse) {
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "proxy: *: found reverse proxy worker for %s",
                               *url);
                *balancer = NULL;
                *worker = conf->reverse;
                access_status = OK;
            }
        }
    }
    else if (access_status == DECLINED && *balancer != NULL) {
        /* All the workers are busy */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
