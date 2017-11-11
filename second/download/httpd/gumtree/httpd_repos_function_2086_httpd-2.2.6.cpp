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

    conf->protocol = NULL;
    conf->accf_map = apr_table_make(a, 5);

#ifdef APR_TCP_DEFER_ACCEPT
    apr_table_set(conf->accf_map, "http", "data");
    apr_table_set(conf->accf_map, "https", "data");
#endif

#if APR_HAS_SO_ACCEPTFILTER
#ifndef ACCEPT_FILTER_NAME
#define ACCEPT_FILTER_NAME "httpready"
#ifdef __FreeBSD_version
#if __FreeBSD_version < 411000 /* httpready broken before 4.1.1 */
#undef ACCEPT_FILTER_NAME
#define ACCEPT_FILTER_NAME "dataready"
#endif
#endif
#endif
    apr_table_set(conf->accf_map, "http", ACCEPT_FILTER_NAME);
    apr_table_set(conf->accf_map, "https", "dataready");
#endif

    conf->trace_enable = AP_TRACE_UNSET;

    return (void *)conf;
}