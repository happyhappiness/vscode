        return DECLINED;
    }

    if (!(id = apr_table_get(r->subprocess_env, "UNIQUE_ID"))) {
        /* we make the assumption that we can't go through all the PIDs in
           under 1 second */
        id = apr_psprintf(r->pool, "%x:%lx:%x", getpid(), time(NULL),
                          apr_atomic_inc32(&next_id));
    }
    ap_set_module_config(r->request_config, &log_forensic_module, (char *)id);

    h.p = r->pool;
    h.count = 0;

