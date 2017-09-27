        }
        if ((val = apr_table_get(params, "b_wyes")) &&
            (*val == '1' && *(val+1) == '\0') &&
            (val = apr_table_get(params, "b_nwrkr"))) {
            char *ret;
            proxy_worker *nworker;
            nworker = ap_proxy_get_worker(conf->pool, bsel, conf, val);
            if (!nworker && storage->num_free_slots(bsel->wslot)) {
                if ((rv = PROXY_GLOBAL_LOCK(bsel)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01194)
                                  "%s: Lock failed for adding worker",
                                  bsel->s->name);
                }
