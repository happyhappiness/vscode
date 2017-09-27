                    for (n = 0; n < balancer->workers->nelts; n++) {
                        worker = *workers;
                        if (!PROXY_WORKER_IS(worker, PROXY_WORKER_STOPPED) &&
                           (worker->s->method != NONE) &&
                           (now > worker->s->updated + worker->s->interval)) {
                            baton_t *baton;
                            /* This pool must last the lifetime of the (possible) thread */
                            apr_pool_t *ptemp;
                            apr_pool_create(&ptemp, ctx->p);
                            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                                         "Checking %s worker: %s  [%d] (%pp)", balancer->s->name,
                                         worker->s->name, worker->s->method, worker);

                            if ((rv = hc_init_worker(ctx, worker)) != APR_SUCCESS) {
                                return rv;
                            }
                            baton = apr_palloc(ptemp, sizeof(baton_t));
                            baton->ctx = ctx;
                            baton->now = now;
                            baton->worker = worker;
                            baton->ptemp = ptemp;

                            if (!ctx->hctp) {
                                hc_check(NULL, baton);
                            }
#if HC_USE_THREADS
                            else {
                                rv = apr_thread_pool_push(ctx->hctp, hc_check, (void *)baton,
                                                          APR_THREAD_TASK_PRIORITY_NORMAL, NULL);
                            }
#endif
                        }
                        workers++;
                    }
                }
                /* s = s->next; */
            }
            break;

        case AP_WATCHDOG_STATE_STOPPING:
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03261)
                         "stopping %s watchdog.",
                         HCHECK_WATHCHDOG_NAME);
#if HC_USE_THREADS
            rv =  apr_thread_pool_destroy(ctx->hctp);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_INFO, rv, s, APLOGNO(03315)
                             "apr_thread_pool_destroy() failed");
            }
#endif
            ctx->hctp = NULL;
            break;
    }
    return rv;
}

static int hc_post_config(apr_pool_t *p, apr_pool_t *plog,
                       apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    sctx_t *ctx;

    APR_OPTIONAL_FN_TYPE(ap_watchdog_get_instance) *hc_watchdog_get_instance;
    APR_OPTIONAL_FN_TYPE(ap_watchdog_register_callback) *hc_watchdog_register_callback;

    hc_watchdog_get_instance = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_get_instance);
    hc_watchdog_register_callback = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_register_callback);
    if (!hc_watchdog_get_instance || !hc_watchdog_register_callback) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(03262)
                     "mod_watchdog is required");
        return !OK;
    }
    ctx = (sctx_t *) ap_get_module_config(s->module_config,
                                          &proxy_hcheck_module);

    rv = hc_watchdog_get_instance(&ctx->watchdog,
                                  HCHECK_WATHCHDOG_NAME,
                                  0, 1, p);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(03263)
                     "Failed to create watchdog instance (%s)",
                     HCHECK_WATHCHDOG_NAME);
        return !OK;
    }
    rv = hc_watchdog_register_callback(ctx->watchdog,
            apr_time_from_sec(HCHECK_WATHCHDOG_INTERVAL),
            ctx,
            hc_watchdog_callback);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(03264)
                     "Failed to register watchdog callback (%s)",
                     HCHECK_WATHCHDOG_NAME);
        return !OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03265)
                 "watchdog callback registered (%s)", HCHECK_WATHCHDOG_NAME);
    return OK;
}

static void hc_show_exprs(request_rec *r)
{
    const apr_table_entry_t *elts;
