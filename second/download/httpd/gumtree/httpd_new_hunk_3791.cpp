        log_pfn_register(p, "^FB", log_ttfb, 0);
    }

    return OK;
}

static apr_status_t logio_ttfb_filter(ap_filter_t *f, apr_bucket_brigade *b)
{
    request_rec *r = f->r;
    logio_dirconf_t *conf = ap_get_module_config(r->per_dir_config,
                                                 &logio_module);
    if (conf && conf->track_ttfb) { 
        logio_req_t *rconf = ap_get_module_config(r->request_config, 
                                                  &logio_module);
        if (rconf == NULL) { 
            rconf = apr_pcalloc(r->pool, sizeof(logio_req_t));
            rconf->ttfb = apr_time_now() - r->request_time;
            ap_set_module_config(r->request_config, &logio_module, rconf);
        }
    }
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, b);
}

static void logio_insert_filter(request_rec * r)
{
    logio_dirconf_t *conf = ap_get_module_config(r->per_dir_config,
                                                 &logio_module);
    if (conf->track_ttfb) { 
        ap_add_output_filter(logio_ttfb_filter_name, NULL, r, r->connection);
    }
    return;
}

static const char *logio_track_ttfb(cmd_parms *cmd, void *in_dir_config, int arg)
{
    logio_dirconf_t *dir_config = in_dir_config;
    dir_config->track_ttfb = arg;
    return NULL;
}
