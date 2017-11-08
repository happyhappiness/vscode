static apr_status_t send_environment(apr_socket_t *s,
                                     const fcgi_provider_conf *conf,
                                     request_rec *r, apr_uint16_t request_id,
                                     apr_pool_t *temp_pool)
{
    const char *fn = "send_environment";
    const apr_array_header_t *envarr;
    const apr_table_entry_t *elts;
    struct iovec vec[2];
    ap_fcgi_header header;
    unsigned char farray[AP_FCGI_HEADER_LEN];
    char *body;
    apr_status_t rv;
    apr_size_t avail_len, len, required_len;
    int i, next_elem, starting_elem;

    envarr = apr_table_elts(r->subprocess_env);
    elts = (const apr_table_entry_t *) envarr->elts;

    if (APLOG_R_IS_LEVEL(r, APLOG_TRACE2)) {

        for (i = 0; i < envarr->nelts; ++i) {
            if (!elts[i].key) {
                continue;
            }
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "%s: '%s': '%s'",
                          fn, elts[i].key, 
                          !strcmp(elts[i].key, "REMOTE_PASSWD") ?
                              "XXXXXXXX" : elts[i].val);
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
                              APLOGNO(02499) "couldn't encode envvar '%s' in %"
                              APR_SIZE_T_FMT " bytes",
                              elts[next_elem].key, avail_len);
                /* skip this envvar and continue */
                ++next_elem;
                continue;
            }
            /* only an unused element at the end of the array */
            break;
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      APLOGNO(02500) "required len for encoding envvars: %"
                      APR_SIZE_T_FMT ", %d/%d elems processed so far",
                      required_len, next_elem, envarr->nelts);

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

        rv = sendv_data(conf, r, s, vec, 2, &len);
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

    return sendv_data(conf, r, s, vec, 1, &len);
}