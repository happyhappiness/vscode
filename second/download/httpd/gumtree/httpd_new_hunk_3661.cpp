                             * socket to a worker
                             */
                            apr_socket_close(csd);
                            ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                         ap_server_conf,
                                         "ap_queue_push failed");
                            ap_push_pool(worker_queue_info, ptrans);
                        }
                        else {
                            have_idle_worker = 0;
                        }
                    }
                    else {
                        ap_push_pool(worker_queue_info, ptrans);
                    }
                }
            }               /* if:else on pt->type */
            out_pfd++;
            num--;
