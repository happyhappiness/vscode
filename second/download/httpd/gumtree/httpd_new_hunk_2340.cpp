            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
        }
    }
    else {
        proxy_worker *worker = ap_proxy_get_worker(cmd->temp_pool, conf, r);
        int reuse = 0;
        if (!worker) {
            const char *err = ap_proxy_add_worker(&worker, cmd->pool, conf, r);
            if (err)
                return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
            PROXY_COPY_CONF_PARAMS(worker, conf);
        } else {
            reuse = 1;
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server,
                         "Sharing worker '%s' instead of creating new worker '%s'",
                         worker->name, new->real);
        }

        for (i = 0; i < arr->nelts; i++) {
            if (reuse) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                             "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                             elts[i].key, elts[i].val, worker->name);
            } else {
                const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                                   elts[i].val);
                if (err)
                    return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
            }
        }
    }
    return NULL;
}

static const char *
