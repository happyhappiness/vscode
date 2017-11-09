static const char *set_worker_hc_param(apr_pool_t *p,
                                    server_rec *s,
                                    proxy_worker *worker,
                                    const char *key,
                                    const char *val,
                                    void *v)
{
    int ival;
    hc_template_t *temp;
    sctx_t *ctx = (sctx_t *) ap_get_module_config(s->module_config,
                                                  &proxy_hcheck_module);
    if (!worker && !v) {
        return "Bad call to set_worker_hc_param()";
    }
    temp = (hc_template_t *)v;
    if (!strcasecmp(key, "hctemplate")) {
        hc_template_t *template;
        template = (hc_template_t *)ctx->templates->elts;
        for (ival = 0; ival < ctx->templates->nelts; ival++, template++) {
            if (!strcasecmp(template->name, val)) {
                if (worker) {
                    worker->s->method = template->method;
                    worker->s->interval = template->interval;
                    worker->s->passes = template->passes;
                    worker->s->fails = template->fails;
                    PROXY_STRNCPY(worker->s->hcuri, template->hurl);
                    PROXY_STRNCPY(worker->s->hcexpr, template->hcexpr);
                } else {
                    temp->method = template->method;
                    temp->interval = template->interval;
                    temp->passes = template->passes;
                    temp->fails = template->fails;
                    temp->hurl = apr_pstrdup(p, template->hurl);
                    temp->hcexpr = apr_pstrdup(p, template->hcexpr);
                }
                return NULL;
            }
        }
        return apr_psprintf(p, "Unknown ProxyHCTemplate name: %s", val);
    }
    else if (!strcasecmp(key, "hcmethod")) {
        proxy_hcmethods_t *method = proxy_hcmethods;
        for (; method->name; method++) {
            if (!strcasecmp(val, method->name)) {
                if (!method->implemented) {
                    return apr_psprintf(p, "Health check method %s not (yet) implemented",
                                        val);
                }
                if (worker) {
                    worker->s->method = method->method;
                } else {
                    temp->method = method->method;
                }
                return NULL;
            }
        }
        return "Unknown method";
    }
    else if (!strcasecmp(key, "hcinterval")) {
        ival = atoi(val);
        if (ival < HCHECK_WATHCHDOG_INTERVAL)
            return apr_psprintf(p, "Interval must be a positive value greater than %d seconds",
                                HCHECK_WATHCHDOG_INTERVAL);
        if (worker) {
            worker->s->interval = apr_time_from_sec(ival);
        } else {
            temp->interval = apr_time_from_sec(ival);
        }
    }
    else if (!strcasecmp(key, "hcpasses")) {
        ival = atoi(val);
        if (ival < 0)
            return "Passes must be a positive value";
        if (worker) {
            worker->s->passes = ival;
        } else {
            temp->passes = ival;
        }
    }
    else if (!strcasecmp(key, "hcfails")) {
        ival = atoi(val);
        if (ival < 0)
            return "Fails must be a positive value";
        if (worker) {
            worker->s->fails = ival;
        } else {
            temp->fails = ival;
        }
    }
    else if (!strcasecmp(key, "hcuri")) {
        if (strlen(val) >= sizeof(worker->s->hcuri))
            return apr_psprintf(p, "Health check uri length must be < %d characters",
                    (int)sizeof(worker->s->hcuri));
        if (worker) {
            PROXY_STRNCPY(worker->s->hcuri, val);
        } else {
            temp->hurl = apr_pstrdup(p, val);
        }
    }
    else if (!strcasecmp(key, "hcexpr")) {
        hc_condition_t *cond;
        cond = (hc_condition_t *)apr_table_get(ctx->conditions, val);
        if (!cond) {
            return apr_psprintf(p, "Unknown health check condition expr: %s", val);
        }
        /* This check is wonky... a known expr can't be this big. Check anyway */
        if (strlen(val) >= sizeof(worker->s->hcexpr))
            return apr_psprintf(p, "Health check uri length must be < %d characters",
                    (int)sizeof(worker->s->hcexpr));
        if (worker) {
            PROXY_STRNCPY(worker->s->hcexpr, val);
        } else {
            temp->hcexpr = apr_pstrdup(p, val);
        }
    }
  else {
        return "unknown Worker hcheck parameter";
    }
    return NULL;
}