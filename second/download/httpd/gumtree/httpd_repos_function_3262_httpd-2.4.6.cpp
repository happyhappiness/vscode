static void *merge_core_server_configs(apr_pool_t *p, void *basev, void *virtv)
{
    core_server_config *base = (core_server_config *)basev;
    core_server_config *virt = (core_server_config *)virtv;
    core_server_config *conf = (core_server_config *)
                               apr_pmemdup(p, base, sizeof(core_server_config));

    if (virt->ap_document_root)
        conf->ap_document_root = virt->ap_document_root;

    if (virt->access_name)
        conf->access_name = virt->access_name;

    /* XXX optimize to keep base->sec_ pointers if virt->sec_ array is empty */
    conf->sec_dir = apr_array_append(p, base->sec_dir, virt->sec_dir);
    conf->sec_url = apr_array_append(p, base->sec_url, virt->sec_url);

    if (virt->redirect_limit)
        conf->redirect_limit = virt->redirect_limit;

    if (virt->subreq_limit)
        conf->subreq_limit = virt->subreq_limit;

    if (virt->trace_enable != AP_TRACE_UNSET)
        conf->trace_enable = virt->trace_enable;

    /* no action for virt->accf_map, not allowed per-vhost */

    if (virt->protocol)
        conf->protocol = virt->protocol;

    if (virt->gprof_dir)
        conf->gprof_dir = virt->gprof_dir;

    if (virt->error_log_format)
        conf->error_log_format = virt->error_log_format;

    if (virt->error_log_conn)
        conf->error_log_conn = virt->error_log_conn;

    if (virt->error_log_req)
        conf->error_log_req = virt->error_log_req;

    return conf;
}