                     * on Linux 2.0.x we seem to end up with EFAULT
                     * occasionally, and we'd loop forever due to it.
                     */
                    ap_log_error(APLOG_MARK, APLOG_ERR, status,
                                 ap_server_conf, "apr_pollset_poll: (listen)");
                    SAFE_ACCEPT(accept_mutex_off());
                    clean_child_exit(APEXIT_CHILDSICK);
                }

                /* We can always use pdesc[0], but sockets at position N
                 * could end up completely starved of attention in a very
                 * busy server. Therefore, we round-robin across the
                 * returned set of descriptors. While it is possible that
