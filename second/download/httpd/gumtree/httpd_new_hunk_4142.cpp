                        apr_allocator_max_free_set(allocator,
                                                   ap_max_mem_free);
                        apr_pool_create_ex(&ptrans, pconf, NULL, allocator);
                        apr_allocator_owner_set(allocator, ptrans);
                        if (ptrans == NULL) {
                            ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                                         ap_server_conf, APLOGNO(03097)
                                         "Failed to create transaction pool");
                            signal_threads(ST_GRACEFUL);
                            return NULL;
                        }
                    }
                    apr_pool_tag(ptrans, "transaction");
