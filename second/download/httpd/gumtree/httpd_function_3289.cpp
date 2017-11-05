static apr_status_t reqtimeout_filter(ap_filter_t *f,
                                      apr_bucket_brigade *bb,
                                      ap_input_mode_t mode,
                                      apr_read_type_e block,
                                      apr_off_t readbytes)
{
    apr_time_t time_left;
    apr_time_t now;
    apr_status_t rv;
    apr_interval_time_t saved_sock_timeout = -1;
    reqtimeout_con_cfg *ccfg = f->ctx;

    if (ccfg->in_keep_alive) {
        /* For this read, the normal keep-alive timeout must be used */
        ccfg->in_keep_alive = 0;
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    now = apr_time_now();
    if (ccfg->new_timeout > 0) {
        /* set new timeout */
        ccfg->timeout_at = now + apr_time_from_sec(ccfg->new_timeout);
        ccfg->new_timeout = 0;
        if (ccfg->new_max_timeout > 0) {
            ccfg->max_timeout_at = now + apr_time_from_sec(ccfg->new_max_timeout);
            ccfg->new_max_timeout = 0;
        }
    }
    else if (ccfg->timeout_at == 0) {
        /* no timeout set */
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    if (!ccfg->socket) {
        ccfg->socket = ap_get_module_config(f->c->conn_config, &core_module);
    }

    rv = check_time_left(ccfg, &time_left);
    if (rv != APR_SUCCESS)
        goto out;

    if (block == APR_NONBLOCK_READ || mode == AP_MODE_INIT
        || mode == AP_MODE_EATCRLF) {
        rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
        if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
            extend_timeout(ccfg, bb);
        }
        return rv;
    }

    rv = apr_socket_timeout_get(ccfg->socket, &saved_sock_timeout);
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    rv = apr_socket_timeout_set(ccfg->socket, MIN(time_left, saved_sock_timeout));
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    if (mode == AP_MODE_GETLINE) {
        /*
         * For a blocking AP_MODE_GETLINE read, apr_brigade_split_line()
         * would loop until a whole line has been read. As this would make it
         * impossible to enforce a total timeout, we only do non-blocking
         * reads.
         */
        apr_off_t remaining = HUGE_STRING_LEN;
        do {
            apr_off_t bblen;
#if APR_MAJOR_VERSION < 2
            apr_int32_t nsds;
            apr_interval_time_t poll_timeout;
            apr_pollfd_t pollset;
#endif

            rv = ap_get_brigade(f->next, bb, AP_MODE_GETLINE, APR_NONBLOCK_READ, remaining);
            if (rv != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(rv)) {
                break;
            }

            if (!APR_BRIGADE_EMPTY(bb)) {
                if (ccfg->min_rate > 0) {
                    extend_timeout(ccfg, bb);
                }

                rv = have_lf_or_eos(bb);
                if (rv != APR_INCOMPLETE) {
                    break;
                }

                rv = apr_brigade_length(bb, 1, &bblen);
                if (rv != APR_SUCCESS) {
                    break;
                }
                remaining -= bblen;
                if (remaining <= 0) {
                    break;
                }

                /* Haven't got a whole line yet, save what we have ... */
                if (!ccfg->tmpbb) {
                    ccfg->tmpbb = apr_brigade_create(f->c->pool, f->c->bucket_alloc);
                }
                APR_BRIGADE_CONCAT(ccfg->tmpbb, bb);
            }

            /* ... and wait for more */
#if APR_MAJOR_VERSION < 2
            pollset.p = f->c->pool;
            pollset.desc_type = APR_POLL_SOCKET;
            pollset.reqevents = APR_POLLIN|APR_POLLHUP;
            pollset.desc.s = ccfg->socket;
            apr_socket_timeout_get(ccfg->socket, &poll_timeout);
            rv = apr_poll(&pollset, 1, &nsds, poll_timeout);
#else
            rv = apr_socket_wait(ccfg->socket, APR_WAIT_READ);
#endif
            if (rv != APR_SUCCESS)
                break;

            rv = check_time_left(ccfg, &time_left);
            if (rv != APR_SUCCESS)
                break;

            rv = apr_socket_timeout_set(ccfg->socket,
                                   MIN(time_left, saved_sock_timeout));
            AP_DEBUG_ASSERT(rv == APR_SUCCESS);

        } while (1);

        if (ccfg->tmpbb)
            APR_BRIGADE_PREPEND(bb, ccfg->tmpbb);

    }
    else {
        /* mode != AP_MODE_GETLINE */
        rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
        if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
            extend_timeout(ccfg, bb);
        }
    }

    apr_socket_timeout_set(ccfg->socket, saved_sock_timeout);

out:
    if (APR_STATUS_IS_TIMEUP(rv)) {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                      "Request %s read timeout", ccfg->type);
        /*
         * If we allow a normal lingering close, the client may keep this
         * process/thread busy for another 30s (MAX_SECS_TO_LINGER).
         * Therefore we tell ap_lingering_close() to shorten this period to
         * 2s (SECONDS_TO_LINGER).
         */
        apr_table_setn(f->c->notes, "short-lingering-close", "1");
    }
    return rv;
}