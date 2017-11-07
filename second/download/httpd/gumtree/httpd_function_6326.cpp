static apr_status_t send_environment(proxy_conn_rec *conn, request_rec *r,
                                     apr_pool_t *temp_pool,
                                     apr_uint16_t request_id)
{
    const apr_array_header_t *envarr;
    const apr_table_entry_t *elts;
    struct iovec vec[2];
    ap_fcgi_header header;
    unsigned char farray[AP_FCGI_HEADER_LEN];
    char *body;
    apr_status_t rv;
    apr_size_t avail_len, len, required_len;
    int next_elem, starting_elem;
    int fpm = 0;
    fcgi_req_config_t *rconf = ap_get_module_config(r->request_config, &proxy_fcgi_module);
    fcgi_dirconf_t *dconf = ap_get_module_config(r->per_dir_config, &proxy_fcgi_module);

    if (rconf) {
       if (rconf->need_dirwalk) {
          ap_directory_walk(r);
       }
    }

    /* Strip proxy: prefixes */
    if (r->filename) {
        char *newfname = NULL;

        if (!strncmp(r->filename, "proxy:balancer://", 17)) {
            newfname = apr_pstrdup(r->pool, r->filename+17);
        }

        if (!FCGI_MAY_BE_FPM(dconf))  {
            if (!strncmp(r->filename, "proxy:fcgi://", 13)) {
                /* If we strip this under FPM, and any internal redirect occurs
                 * on PATH_INFO, FPM may use PATH_TRANSLATED instead of
                 * SCRIPT_FILENAME (a la mod_fastcgi + Action).
                 */
                newfname = apr_pstrdup(r->pool, r->filename+13);
            }
            /* Query string in environment only */
            if (newfname && r->args && *r->args) {
                char *qs = strrchr(newfname, '?');
                if (qs && !strcmp(qs+1, r->args)) {
                    *qs = '\0';
                }
            }
        } else {
            fpm = 1;
        }

        if (newfname) {
            newfname = ap_strchr(newfname, '/');
            r->filename = newfname;
        }
    }

#if 0
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(09999)
                  "r->filename: %s", (r->filename ? r->filename : "nil"));
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(09999)
                  "r->uri: %s", (r->uri ? r->uri : "nil"));
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(09999)
                  "r->path_info: %s", (r->path_info ? r->path_info : "nil"));
#endif

    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    if (fpm || apr_table_get(r->notes, "virtual_script")) {
        /*
         * Adjust SCRIPT_NAME, PATH_INFO and PATH_TRANSLATED for PHP-FPM
         * TODO: Right now, PATH_INFO and PATH_TRANSLATED look OK...
         */
        const char *pend;
        const char *script_name = apr_table_get(r->subprocess_env, "SCRIPT_NAME");
        pend = script_name + strlen(script_name);
        if (r->path_info && *r->path_info) {
            pend = script_name + ap_find_path_info(script_name, r->path_info) - 1;
        }
        while (pend != script_name && *pend != '/') {
            pend--;
        }
        apr_table_setn(r->subprocess_env, "SCRIPT_NAME", pend);
        ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                      "fpm:virtual_script: Modified SCRIPT_NAME to: %s",
                      pend);
    }

    /* XXX are there any FastCGI specific env vars we need to send? */

    /* Give admins final option to fine-tune env vars */
    fix_cgivars(r, dconf);

    /* XXX mod_cgi/mod_cgid use ap_create_environment here, which fills in
     *     the TZ value specially.  We could use that, but it would mean
     *     parsing the key/value pairs back OUT of the allocated env array,
     *     not to mention allocating a totally useless array in the first
     *     place, which would suck. */

    envarr = apr_table_elts(r->subprocess_env);
    elts = (const apr_table_entry_t *) envarr->elts;

    if (APLOGrtrace8(r)) {
        int i;

        for (i = 0; i < envarr->nelts; ++i) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r, APLOGNO(01062)
                          "sending env var '%s' value '%s'",
                          elts[i].key, elts[i].val);
        }
    }

    /* Send envvars over in as many FastCGI records as it takes, */
    next_elem = 0; /* starting with the first one */

    avail_len = 16 * 1024; /* our limit per record, which could have been up
                            * to AP_FCGI_MAX_CONTENT_LEN
                            */

    while (next_elem < envarr->nelts) {
        starting_elem = next_elem;
        required_len = ap_fcgi_encoded_env_len(r->subprocess_env,
                                               avail_len,
                                               &next_elem);

        if (!required_len) {
            if (next_elem < envarr->nelts) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              APLOGNO(02536) "couldn't encode envvar '%s' in %"
                              APR_SIZE_T_FMT " bytes",
                              elts[next_elem].key, avail_len);
                /* skip this envvar and continue */
                ++next_elem;
                continue;
            }
            /* only an unused element at the end of the array */
            break;
        }

        body = apr_palloc(temp_pool, required_len);
        rv = ap_fcgi_encode_env(r, r->subprocess_env, body, required_len,
                                &starting_elem);
        /* we pre-compute, so we can't run out of space */
        ap_assert(rv == APR_SUCCESS);
        /* compute and encode must be in sync */
        ap_assert(starting_elem == next_elem);

        ap_fcgi_fill_in_header(&header, AP_FCGI_PARAMS, request_id,
                               (apr_uint16_t)required_len, 0);
        ap_fcgi_header_to_array(&header, farray);

        vec[0].iov_base = (void *)farray;
        vec[0].iov_len = sizeof(farray);
        vec[1].iov_base = body;
        vec[1].iov_len = required_len;

        rv = send_data(conn, vec, 2, &len);
        apr_pool_clear(temp_pool);

        if (rv) {
            return rv;
        }
    }

    /* Envvars sent, so say we're done */
    ap_fcgi_fill_in_header(&header, AP_FCGI_PARAMS, request_id, 0, 0);
    ap_fcgi_header_to_array(&header, farray);

    vec[0].iov_base = (void *)farray;
    vec[0].iov_len = sizeof(farray);

    return send_data(conn, vec, 1, &len);
}