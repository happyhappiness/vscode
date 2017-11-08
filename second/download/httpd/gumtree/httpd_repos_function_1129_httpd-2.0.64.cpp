static int log_script(request_rec *r, cgi_server_conf * conf, int ret,
                      char *dbuf, const char *sbuf, apr_bucket_brigade *bb, 
                      apr_file_t *script_err)
{
    const apr_array_header_t *hdrs_arr = apr_table_elts(r->headers_in);
    const apr_table_entry_t *hdrs = (const apr_table_entry_t *) hdrs_arr->elts;
    char argsbuffer[HUGE_STRING_LEN];
    apr_file_t *f = NULL;
    apr_bucket *e;
    const char *buf;
    apr_size_t len;
    apr_status_t rv;
    int first;
    int i;
    apr_finfo_t finfo;
    char time_str[APR_CTIME_LEN];

    /* XXX Very expensive mainline case! Open, then getfileinfo! */
    if (!conf->logname ||
        ((apr_stat(&finfo, conf->logname,
                   APR_FINFO_SIZE, r->pool) == APR_SUCCESS) &&
         (finfo.size > conf->logbytes)) ||
        (apr_file_open(&f, conf->logname,
                       APR_APPEND|APR_WRITE|APR_CREATE, APR_OS_DEFAULT,
                       r->pool) != APR_SUCCESS)) {
        /* Soak up script output */
        discard_script_output(bb);
        log_script_err(r, script_err);
        return ret;
    }

    /* "%% [Wed Jun 19 10:53:21 1996] GET /cgi-bin/printenv HTTP/1.0" */
    apr_ctime(time_str, apr_time_now());
    apr_file_printf(f, "%%%% [%s] %s %s%s%s %s\n", time_str, r->method, r->uri,
                    r->args ? "?" : "", r->args ? r->args : "", r->protocol);
    /* "%% 500 /usr/local/apache/cgi-bin" */
    apr_file_printf(f, "%%%% %d %s\n", ret, r->filename);

    apr_file_puts("%request\n", f);
    for (i = 0; i < hdrs_arr->nelts; ++i) {
        if (!hdrs[i].key)
            continue;
        apr_file_printf(f, "%s: %s\n", hdrs[i].key, hdrs[i].val);
    }
    if ((r->method_number == M_POST || r->method_number == M_PUT) &&
        *dbuf) {
        apr_file_printf(f, "\n%s\n", dbuf);
    }

    apr_file_puts("%response\n", f);
    hdrs_arr = apr_table_elts(r->err_headers_out);
    hdrs = (const apr_table_entry_t *) hdrs_arr->elts;

    for (i = 0; i < hdrs_arr->nelts; ++i) {
        if (!hdrs[i].key)
            continue;
        apr_file_printf(f, "%s: %s\n", hdrs[i].key, hdrs[i].val);
    }

    if (sbuf && *sbuf)
        apr_file_printf(f, "%s\n", sbuf);

    first = 1;
    APR_BRIGADE_FOREACH(e, bb) {
        if (APR_BUCKET_IS_EOS(e)) {
            break;
        }
        rv = apr_bucket_read(e, &buf, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS || (len == 0)) {
            break;
        }
        if (first) {
            apr_file_puts("%stdout\n", f);
            first = 0;
        }
        apr_file_write(f, buf, &len);
        apr_file_puts("\n", f);
    }

    if (apr_file_gets(argsbuffer, HUGE_STRING_LEN, script_err) == APR_SUCCESS) {
        apr_file_puts("%stderr\n", f);
        apr_file_puts(argsbuffer, f);
        while (apr_file_gets(argsbuffer, HUGE_STRING_LEN,
                             script_err) == APR_SUCCESS) {
            apr_file_puts(argsbuffer, f);
        }
        apr_file_puts("\n", f);
    }

    apr_brigade_destroy(bb);
    apr_file_close(script_err);

    apr_file_close(f);
    return ret;
}