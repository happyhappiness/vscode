         svr = create_dbd_config(config_pool, s);
         ap_set_module_config(s->module_config, &dbd_module, svr);
    }

    if (apr_hash_get(svr->cfg->queries, label, APR_HASH_KEY_STRING)
        && strcmp(query, "")) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "conflicting SQL statements with label %s", label);
    }

    apr_hash_set(svr->cfg->queries, label, APR_HASH_KEY_STRING, query);
}

