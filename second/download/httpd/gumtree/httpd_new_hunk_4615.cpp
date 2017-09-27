                    for (n = 0; n < balancer->workers->nelts; n++) {
                        worker = *workers;
                        if (!PROXY_WORKER_IS(worker, PROXY_WORKER_STOPPED) &&
                           (worker->s->method != NONE) &&
                           (now > worker->s->updated + worker->s->interval)) {
                            baton_t *baton;
                            apr_pool_t *ptemp;
                            ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                                         "Checking %s worker: %s  [%d] (%pp)", balancer->s->name,
                                         worker->s->name, worker->s->method, worker);

                            if ((rv = hc_init_worker(ctx, worker)) != APR_SUCCESS) {
                                return rv;
                            }
                            /* This pool must last the lifetime of the (possible) thread */
                            apr_pool_create(&ptemp, ctx->p);
                            apr_pool_tag(ptemp, "hc_request");
                            baton = apr_palloc(ptemp, sizeof(baton_t));
                            baton->ctx = ctx;
                            baton->now = now;
                            baton->worker = worker;
                            baton->ptemp = ptemp;
                            baton->hc = hc_get_hcworker(ctx, worker, ptemp);

                            if (!hctp) {
                                hc_check(NULL, baton);
                            }
#if HC_USE_THREADS
                            else {
                                rv = apr_thread_pool_push(hctp, hc_check, (void *)baton,
                                                          APR_THREAD_TASK_PRIORITY_NORMAL, NULL);
                            }
#endif
                        }
                        workers++;
                    }
                }
            }
            break;

        case AP_WATCHDOG_STATE_STOPPING:
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03261)
                         "stopping %s watchdog.",
                         HCHECK_WATHCHDOG_NAME);
#if HC_USE_THREADS
            if (hctp) {
                rv =  apr_thread_pool_destroy(hctp);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_INFO, rv, s, APLOGNO(03315)
                                 "apr_thread_pool_destroy() failed");
                }
            }
#endif
            hctp = NULL;
            break;
    }
    return rv;
}
static int hc_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                         apr_pool_t *ptemp)
{
    tpsize = HC_THREADPOOL_SIZE;
    return OK;
}
static int hc_post_config(apr_pool_t *p, apr_pool_t *plog,
                       apr_pool_t *ptemp, server_rec *main_s)
{
    apr_status_t rv;
    server_rec *s = main_s;

    APR_OPTIONAL_FN_TYPE(ap_watchdog_get_instance) *hc_watchdog_get_instance;
    APR_OPTIONAL_FN_TYPE(ap_watchdog_register_callback) *hc_watchdog_register_callback;

    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }
    hc_watchdog_get_instance = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_get_instance);
    hc_watchdog_register_callback = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_register_callback);
    if (!hc_watchdog_get_instance || !hc_watchdog_register_callback) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(03262)
                     "mod_watchdog is required");
        return !OK;
    }
    rv = hc_watchdog_get_instance(&watchdog,
                                  HCHECK_WATHCHDOG_NAME,
                                  0, 1, p);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(03263)
                     "Failed to create watchdog instance (%s)",
                     HCHECK_WATHCHDOG_NAME);
        return !OK;
    }
    while (s) {
        sctx_t *ctx = ap_get_module_config(s->module_config,
                                           &proxy_hcheck_module);

        if (s != ctx->s) {
            ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, s, APLOGNO(10019)
                         "Missing unique per-server context: %s (%pp:%pp) (no hchecks)",
                         s->server_hostname, s, ctx->s);
            s = s->next;
            continue;
        }
        rv = hc_watchdog_register_callback(watchdog,
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
                     "watchdog callback registered (%s for %s)", HCHECK_WATHCHDOG_NAME, s->server_hostname);
        s = s->next;
    }
    return OK;
}

static void hc_show_exprs(request_rec *r)
{
    const apr_table_entry_t *elts;
