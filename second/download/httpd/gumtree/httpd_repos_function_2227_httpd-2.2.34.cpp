static void *merge_core_server_configs(apr_pool_t *p, void *basev, void *virtv)
{
    core_server_config *base = (core_server_config *)basev;
    core_server_config *virt = (core_server_config *)virtv;
    core_server_config *conf;

    conf = (core_server_config *)apr_pmemdup(p, virt, sizeof(core_server_config));

    if (!conf->access_name) {
        conf->access_name = base->access_name;
    }

    if (!conf->ap_document_root) {
        conf->ap_document_root = base->ap_document_root;
    }

    if (!conf->protocol) {
        conf->protocol = base->protocol;
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

    conf->merge_trailers = (virt->merge_trailers != AP_MERGE_TRAILERS_UNSET)
                           ? virt->merge_trailers
                           : base->merge_trailers;

    if (conf->http09_enable == AP_HTTP09_UNSET)
        conf->http09_enable = base->http09_enable;

    if (conf->http_conformance == AP_HTTP_CONFORMANCE_UNSET)
        conf->http_conformance = base->http_conformance;

    if (conf->http_methods == AP_HTTP_METHODS_UNSET)
        conf->http_methods = base->http_methods;

    /* N.B. If you backport things here from 2.4, note that the
     * merging logic needs to be inverted, since conf is initially a
     * copy of vertv not basev. */
    
    return conf;
}