     *     not to mention allocating a totally useless array in the first
     *     place, which would suck. */

    envarr = apr_table_elts(r->subprocess_env);
    elts = (const apr_table_entry_t *) envarr->elts;

#ifdef FCGI_DUMP_ENV_VARS
    {
        int i;
        
        for (i = 0; i < envarr->nelts; ++i) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01062)
                          "sending env var '%s' value '%s'",
                          elts[i].key, elts[i].val);
        }
    }
#endif

    /* Send envvars over in as many FastCGI records as it takes, */
    next_elem = 0; /* starting with the first one */

    avail_len = 16 * 1024; /* our limit per record, which could have been up
                            * to AP_FCGI_MAX_CONTENT_LEN
