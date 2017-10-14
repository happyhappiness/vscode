static int log_before(request_rec *r)
{
    fcfg *cfg = ap_get_module_config(r->server->module_config,
                                     &log_forensic_module);
    const char *id;
    hlog h;
    apr_size_t n;
    apr_status_t rv;

    if (!cfg->fd || r->prev) {
        return DECLINED;
    }

    if (!(id = apr_table_get(r->subprocess_env, "UNIQUE_ID"))) {
        /* we make the assumption that we can't go through all the PIDs in
           under 1 second */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                    "mod_log_forensic: mod_unique_id must also be active");
	return DECLINED;
    }
    ap_set_module_config(r->request_config, &log_forensic_module, (char *)id);

    h.p = r->pool;
    h.count = 0;

    apr_table_do(count_headers, &h, r->headers_in, NULL);

    h.count += 1+strlen(id)+1+count_string(r->the_request)+1+1;
    h.log = apr_palloc(r->pool, h.count);
    h.pos = h.log;
    h.end = h.log+h.count;

    *h.pos++ = '+';
    strcpy(h.pos, id);
    h.pos += strlen(h.pos);
    *h.pos++ = '|';
    h.pos = log_escape(h.pos, h.end, r->the_request);

    apr_table_do(log_headers, &h, r->headers_in, NULL);

    ap_assert(h.pos < h.end);
    *h.pos++ = '\n';

    n = h.count-1;
    rv = apr_file_write(cfg->fd, h.log, &n);
    ap_assert(rv == APR_SUCCESS && n == h.count-1);

    apr_table_setn(r->notes, "forensic-id", id);

    return OK;
}