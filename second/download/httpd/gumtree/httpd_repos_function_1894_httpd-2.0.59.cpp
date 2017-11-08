static void *merge_core_dir_configs(apr_pool_t *a, void *basev, void *newv)
{
    core_dir_config *base = (core_dir_config *)basev;
    core_dir_config *new = (core_dir_config *)newv;
    core_dir_config *conf;
    int i;

    /* Create this conf by duplicating the base, replacing elements
     * (or creating copies for merging) where new-> values exist.
     */
    conf = (core_dir_config *)apr_palloc(a, sizeof(core_dir_config));
    memcpy(conf, base, sizeof(core_dir_config));

    conf->d = new->d;
    conf->d_is_fnmatch = new->d_is_fnmatch;
    conf->d_components = new->d_components;
    conf->r = new->r;

    if (new->opts & OPT_UNSET) {
        /* there was no explicit setting of new->opts, so we merge
         * preserve the invariant (opts_add & opts_remove) == 0
         */
        conf->opts_add = (conf->opts_add & ~new->opts_remove) | new->opts_add;
        conf->opts_remove = (conf->opts_remove & ~new->opts_add)
                            | new->opts_remove;
        conf->opts = (conf->opts & ~conf->opts_remove) | conf->opts_add;
        if ((base->opts & OPT_INCNOEXEC) && (new->opts & OPT_INCLUDES)) {
            conf->opts = (conf->opts & ~OPT_INCNOEXEC) | OPT_INCLUDES;
        }
    }
    else {
        /* otherwise we just copy, because an explicit opts setting
         * overrides all earlier +/- modifiers
         */
        conf->opts = new->opts;
        conf->opts_add = new->opts_add;
        conf->opts_remove = new->opts_remove;
    }

    if (!(new->override & OR_UNSET)) {
        conf->override = new->override;
    }

    if (new->ap_default_type) {
        conf->ap_default_type = new->ap_default_type;
    }

    if (new->ap_auth_type) {
        conf->ap_auth_type = new->ap_auth_type;
    }

    if (new->ap_auth_name) {
        conf->ap_auth_name = new->ap_auth_name;
    }

    if (new->ap_requires) {
        conf->ap_requires = new->ap_requires;
    }

    if (conf->response_code_strings == NULL) {
        conf->response_code_strings = new->response_code_strings;
    }
    else if (new->response_code_strings != NULL) {
        /* If we merge, the merge-result must have it's own array
         */
        conf->response_code_strings = apr_palloc(a,
            sizeof(*conf->response_code_strings) * RESPONSE_CODES);
        memcpy(conf->response_code_strings, base->response_code_strings,
               sizeof(*conf->response_code_strings) * RESPONSE_CODES);

        for (i = 0; i < RESPONSE_CODES; ++i) {
            if (new->response_code_strings[i] != NULL) {
                conf->response_code_strings[i] = new->response_code_strings[i];
            }
        }
    }
    /* Otherwise we simply use the base->response_code_strings array
     */

    if (new->hostname_lookups != HOSTNAME_LOOKUP_UNSET) {
        conf->hostname_lookups = new->hostname_lookups;
    }

    if ((new->do_rfc1413 & 2) == 0) {
        conf->do_rfc1413 = new->do_rfc1413;
    }

    if ((new->content_md5 & 2) == 0) {
        conf->content_md5 = new->content_md5;
    }

    if (new->accept_path_info != 3) {
        conf->accept_path_info = new->accept_path_info;
    }

    if (new->use_canonical_name != USE_CANONICAL_NAME_UNSET) {
        conf->use_canonical_name = new->use_canonical_name;
    }

#ifdef RLIMIT_CPU
    if (new->limit_cpu) {
        conf->limit_cpu = new->limit_cpu;
    }
#endif

#if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS)
    if (new->limit_mem) {
        conf->limit_mem = new->limit_mem;
    }
#endif

#ifdef RLIMIT_NPROC
    if (new->limit_nproc) {
        conf->limit_nproc = new->limit_nproc;
    }
#endif

    if (new->limit_req_body != AP_LIMIT_REQ_BODY_UNSET) {
        conf->limit_req_body = new->limit_req_body;
    }

    if (new->limit_xml_body != AP_LIMIT_UNSET)
        conf->limit_xml_body = new->limit_xml_body;
    else
        conf->limit_xml_body = base->limit_xml_body;

    if (!conf->sec_file) {
        conf->sec_file = new->sec_file;
    }
    else if (new->sec_file) {
        /* If we merge, the merge-result must have it's own array
         */
        conf->sec_file = a