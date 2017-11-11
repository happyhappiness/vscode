static void *merge_core_server_configs(apr_pool_t *p, void *basev, void *virtv)
{
    core_server_config *base = (core_server_config *)basev;
    core_server_config *virt = (core_server_config *)virtv;
    core_server_config *conf;

    conf = (core_server_config *)apr_palloc(p, sizeof(core_server_config));
    memcpy(conf, virt, sizeof(core_server_config));

    if (!conf->access_name) {
        conf->access_name = base->access_name;
    }

    if (!conf->ap_document_root) {
        conf->ap_document_root = base->ap_document_root;
    }

    conf->sec_dir = apr_array_append(p, base->sec_dir, virt->sec_dir);
    conf->sec_url = apr_array_append(p, base->sec_url, virt->sec_url);

    conf->redirect_limit = virt->redirect_limit
                           ? virt->redirect_limit
                           : base->redirect_limit;

    conf->subreq_limit = virt->subreq_limit
                         ? virt->subreq_limit
                         : base->subreq_limit;

    conf->trace_enable = (virt->trace_enable != AP_TRACE_UNSET)
                         ? virt->trace_enable
                         : base->trace_enable;

    return conf;
}