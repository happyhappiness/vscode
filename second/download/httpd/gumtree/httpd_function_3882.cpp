static apr_status_t send_environment(proxy_conn_rec *conn, request_rec *r, 
                                     int request_id)
{
    const apr_array_header_t *envarr;
    const apr_table_entry_t *elts;
    struct iovec vec[2];
    fcgi_header header;
    unsigned char farray[FCGI_HEADER_LEN];
    apr_size_t bodylen, envlen;
    char *body, *itr;
    apr_status_t rv;
    apr_size_t len;
    int i, numenv;

    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    /* XXX are there any FastCGI specific env vars we need to send? */

    bodylen = envlen = 0;

    /* XXX mod_cgi/mod_cgid use ap_create_environment here, which fills in
     *     the TZ value specially.  We could use that, but it would mean
     *     parsing the key/value pairs back OUT of the allocated env array,
     *     not to mention allocating a totally useless array in the first
     *     place, which would suck. */

    envarr = apr_table_elts(r->subprocess_env);

    elts = (const apr_table_entry_t *) envarr->elts;

    for (i = 0; i < envarr->nelts; ++i) {
        apr_size_t keylen, vallen;

        if (! elts[i].key) {
            continue;
        }

        keylen = strlen(elts[i].key);

        if (keylen >> 7 == 0) {
            envlen += 1;
        }
        else {
            envlen += 4;
        }

        envlen += keylen;

        vallen = strlen(elts[i].val);

#ifdef FCGI_DUMP_ENV_VARS
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "proxy: FCGI: sending env var '%s' value '%s'",
                      elts[i].key, elts[i].val);
#endif

        if (vallen >> 7 == 0) {
            envlen += 1;
        }
        else {
            envlen += 4;
        }

        envlen += vallen;

	/* The cast of bodylen is safe since FCGI_MAX_ENV_SIZE is for sure an int */
        if (envlen > FCGI_MAX_ENV_SIZE) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: FCGI: truncating environment to %d bytes and %d elements",
                          (int)bodylen, i);
            break;
        }

        bodylen = envlen;
    }

    numenv = i;

    body = apr_pcalloc(r->pool, bodylen);

    itr = body;

    for (i = 0; i < numenv; ++i) {
        apr_size_t keylen, vallen;
       
        if (! elts[i].key) {
            continue;
        }

        keylen = strlen(elts[i].key);

        if (keylen >> 7 == 0) {
            itr[0] = keylen & 0xff;
            itr += 1;
        }
        else {
            itr[0] = ((keylen >> 24) & 0xff) | 0x80;
            itr[1] = ((keylen >> 16) & 0xff);
            itr[2] = ((keylen >> 8) & 0xff);
            itr[3] = ((keylen) & 0xff);
            itr += 4;
        }

        vallen = strlen(elts[i].val);

        if (vallen >> 7 == 0) {
            itr[0] = vallen & 0xff;
            itr += 1;
        }
        else {
            itr[0] = ((vallen >> 24) & 0xff) | 0x80;
            itr[1] = ((vallen >> 16) & 0xff);
            itr[2] = ((vallen >> 8) & 0xff);
            itr[3] = ((vallen) & 0xff);
            itr += 4;
        }

        memcpy(itr, elts[i].key, keylen);
        itr += keylen;

        memcpy(itr, elts[i].val, vallen);
        itr += vallen;
    }

    fill_in_header(&header, FCGI_PARAMS, request_id, bodylen, 0);
    fcgi_header_to_array(&header, farray);

    vec[0].iov_base = farray;
    vec[0].iov_len = sizeof(farray);
    vec[1].iov_base = body;
    vec[1].iov_len = bodylen;

    rv = send_data(conn, vec, 2, &len, 1);
    if (rv) {
        return rv;
    }

    fill_in_header(&header, FCGI_PARAMS, request_id, 0, 0);
    fcgi_header_to_array(&header, farray);

    vec[0].iov_base = farray;
    vec[0].iov_len = sizeof(farray);

    return send_data(conn, vec, 1, &len, 1);
}