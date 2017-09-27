        if (!ap_listeners->next) {
            /* Only one listener, so skip the poll */
            lr = ap_listeners;
        }
        else {
            while (!listener_may_exit) {
                apr_int32_t numdesc;
                const apr_pollfd_t *pdesc;

                rv = apr_pollset_poll(pollset, -1, &numdesc, &pdesc);
                if (rv != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(rv)) {
                        continue;
                    }

                    /* apr_pollset_poll() will only return errors in catastrophic
                     * circumstances. Let's try exiting gracefully, for now. */
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv,
                                 (const server_rec *) ap_server_conf,
                                 "apr_pollset_poll: (listen)");
                    signal_threads(ST_GRACEFUL);
                }

                if (listener_may_exit) break;

                /* We can always use pdesc[0], but sockets at position N
                 * could end up completely starved of attention in a very
                 * busy server. Therefore, we round-robin across the
                 * returned set of descriptors. While it is possible that
                 * the returned set of descriptors might flip around and
                 * continue to starve some sockets, we happen to know the
                 * internal pollset implementation retains ordering
                 * stability of the sockets. Thus, the round-robin should
                 * ensure that a socket will eventually be serviced.
                 */
                if (last_poll_idx >= numdesc)
                    last_poll_idx = 0;

                /* Grab a listener record from the client_data of the poll
                 * descriptor, and advance our saved index to round-robin
                 * the next fetch.
                 *
                 * ### hmm... this descriptor might have POLLERR rather
                 * ### than POLLIN
                 */
                lr = pdesc[last_poll_idx++].client_data;
                break;

            } /* while */

        } /* if/else */

        if (!listener_may_exit) {
            if (ptrans == NULL) {
                /* we can't use a recycled transaction pool this time.
                 * create a new transaction pool */
                apr_allocator_t *allocator;

                apr_allocator_create(&allocator);
                apr_allocator_max_free_set(allocator, ap_max_mem_free);
                apr_pool_create_ex(&ptrans, pconf, NULL, allocator);
                apr_allocator_owner_set(allocator, ptrans);
            }
            apr_pool_tag(ptrans, "transaction");
            rv = lr->accept_func(&csd, lr, ptrans);
            /* later we trash rv and rely on csd to indicate success/failure */
            AP_DEBUG_ASSERT(rv == APR_SUCCESS || !csd);
