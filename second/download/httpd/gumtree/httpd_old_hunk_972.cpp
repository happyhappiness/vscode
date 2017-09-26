        if (!ap_listeners->next) {
            /* Only one listener, so skip the poll */
            lr = ap_listeners;
        }
        else {
            while (!listener_may_exit) {
                apr_status_t ret;
                apr_int16_t event;

                ret = apr_poll(pollset, num_listensocks, &n, -1);
                if (ret != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(ret)) {
                        continue;
                    }

                    /* apr_pollset_poll() will only return errors in catastrophic
                     * circumstances. Let's try exiting gracefully, for now. */
                    ap_log_error(APLOG_MARK, APLOG_ERR, ret, (const server_rec *)
                                 ap_server_conf, "apr_poll: (listen)");
                    signal_threads(ST_GRACEFUL);
                }

                if (listener_may_exit) break;

                /* find a listener */
                lr = last_lr;
                do {
                    lr = lr->next;
                    if (lr == NULL) {
                        lr = ap_listeners;
                    }
                    /* XXX: Should we check for POLLERR? */
                    apr_poll_revents_get(&event, lr->sd, pollset);
                    if (event & APR_POLLIN) {
                        last_lr = lr;
                        goto got_fd;
                    }
                } while (lr != last_lr);
            }
        }
    got_fd:
        if (!listener_may_exit) {
            if (ptrans == NULL) {
                /* we can't use a recycled transaction pool this time.
                 * create a new transaction pool */
                apr_allocator_t *allocator;

                apr_allocator_create(&allocator);
                apr_allocator_max_free_set(allocator, ap_max_mem_free);
                apr_pool_create_ex(&ptrans, NULL, NULL, allocator);
                apr_allocator_owner_set(allocator, ptrans);
            }
            apr_pool_tag(ptrans, "transaction");
            rv = lr->accept_func(&csd, lr, ptrans);
            /* later we trash rv and rely on csd to indicate success/failure */
            AP_DEBUG_ASSERT(rv == APR_SUCCESS || !csd);
