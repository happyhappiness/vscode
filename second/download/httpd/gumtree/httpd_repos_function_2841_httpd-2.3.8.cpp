static void *create_core_dir_config(apr_pool_t *a, char *dir)
{
    core_dir_config *conf;

    conf = (core_dir_config *)apr_pcalloc(a, sizeof(core_dir_config));

    /* conf->r and conf->d[_*] are initialized by dirsection() or left NULL */

    conf->opts = dir ? OPT_UNSET : OPT_UNSET|OPT_ALL;
    conf->opts_add = conf->opts_remove = OPT_NONE;
    conf->override = dir ? OR_UNSET : OR_UNSET|OR_ALL;
    conf->override_opts = OPT_UNSET | OPT_ALL | OPT_SYM_OWNER | OPT_MULTI;

    conf->content_md5 = 2;
    conf->accept_path_info = 3;

    conf->use_canonical_name = USE_CANONICAL_NAME_UNSET;
    conf->use_canonical_phys_port = USE_CANONICAL_PHYS_PORT_UNSET;

    conf->hostname_lookups = HOSTNAME_LOOKUP_UNSET;

#ifdef RLIMIT_CPU
    conf->limit_cpu = NULL;
#endif
#if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS)
    conf->limit_mem = NULL;
#endif
#ifdef RLIMIT_NPROC
    conf->limit_nproc = NULL;
#endif

    conf->limit_req_body = AP_LIMIT_REQ_BODY_UNSET;
    conf->limit_xml_body = AP_LIMIT_UNSET;
    conf->sec_file = apr_array_make(a, 2, sizeof(ap_conf_vector_t *));

    conf->server_signature = srv_sig_unset;

    conf->add_default_charset = ADD_DEFAULT_CHARSET_UNSET;
    conf->add_default_charset_name = DEFAULT_ADD_DEFAULT_CHARSET_NAME;

    /* Overriding all negotiation
     */
    conf->mime_type = NULL;
    conf->handler = NULL;
    conf->output_filters = NULL;
    conf->input_filters = NULL;

    /*
     * Flag for use of inodes in ETags.
     */
    conf->etag_bits = ETAG_UNSET;
    conf->etag_add = ETAG_UNSET;
    conf->etag_remove = ETAG_UNSET;

    conf->enable_mmap = ENABLE_MMAP_UNSET;
    conf->enable_sendfile = ENABLE_SENDFILE_UNSET;
    conf->allow_encoded_slashes = 0;

    return (void *)conf;
}