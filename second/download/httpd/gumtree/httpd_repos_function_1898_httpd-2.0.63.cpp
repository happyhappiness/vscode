static void *create_core_server_config(apr_pool_t *a, server_rec *s)
{
    core_server_config *conf;
    int is_virtual = s->is_virtual;

    conf = (core_server_config *)apr_pcalloc(a, sizeof(core_server_config));

#ifdef GPROF
    conf->gprof_dir = NULL;
#endif

    conf->access_name = is_virtual ? NULL : DEFAULT_ACCESS_FNAME;
    conf->ap_document_root = is_virtual ? NULL : DOCUMENT_LOCATION;
    conf->sec_dir = apr_array_make(a, 40, sizeof(ap_conf_vector_t *));
    conf->sec_url = apr_array_make(a, 40, sizeof(ap_conf_vector_t *));

    /* recursion stopper */
    conf->redirect_limit = 0; /* 0 == unset */
    conf->subreq_limit = 0;

    conf->trace_enable = AP_TRACE_UNSET;

    return (void *)conf;
}