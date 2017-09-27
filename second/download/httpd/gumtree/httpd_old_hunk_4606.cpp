    ap_fcgi_header header;
    unsigned char farray[AP_FCGI_HEADER_LEN];
    char *body;
    apr_status_t rv;
    apr_size_t avail_len, len, required_len;
    int next_elem, starting_elem;
    fcgi_req_config_t *rconf = ap_get_module_config(r->request_config, &proxy_fcgi_module);

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
        else if (!strncmp(r->filename, "proxy:fcgi://", 13)) {
            newfname = apr_pstrdup(r->pool, r->filename+13);
        }
        /* Query string in environment only */
        if (newfname && r->args && *r->args) { 
            char *qs = strrchr(newfname, '?');
            if (qs && !strcmp(qs+1, r->args)) { 
                *qs = '\0';
            }
        }

        if (newfname) {
            newfname = ap_strchr(newfname, '/');
            r->filename = newfname;
        }
    }

    ap_add_common_vars(r);
    ap_add_cgi_vars(r);
 
    /* XXX are there any FastCGI specific env vars we need to send? */

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
