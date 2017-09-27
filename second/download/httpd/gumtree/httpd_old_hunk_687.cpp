        return DECLINED;
    }

    if (!(id = apr_table_get(r->subprocess_env, "UNIQUE_ID"))) {
        /* we make the assumption that we can't go through all the PIDs in
           under 1 second */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                    "mod_log_forensic: mod_unique_id must also be active");
	return DECLINED;
    }
    ap_set_module_config(r->request_config, &log_forensic_module, (char *)id);

    h.p = r->pool;
    h.count = 0;

