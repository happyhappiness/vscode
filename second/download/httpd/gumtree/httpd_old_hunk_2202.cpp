                status = apr_pollset_poll(pollset, -1, &numdesc, &pdesc);
                if (status != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(status)) {
                        if (one_process && shutdown_pending) {
                            return;
                        }
                        continue;
                    }
                    /* Single Unix documents select as returning errnos
                     * EBADF, EINTR, and EINVAL... and in none of those
                     * cases does it make sense to continue.  In fact
                     * on Linux 2.0.x we seem to end up with EFAULT
                     * occasionally, and we'd loop forever due to it.
                     */
                    ap_log_error(APLOG_MARK, APLOG_ERR, status,
                                 ap_server_conf, "apr_pollset_poll: (listen)");
                    clean_child_exit(1);
                }

                /* We can always use pdesc[0], but sockets at position N
                 * could end up completely starved of attention in a very
                 * busy server. Therefore, we round-robin across the
