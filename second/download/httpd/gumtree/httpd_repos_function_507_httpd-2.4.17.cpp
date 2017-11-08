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