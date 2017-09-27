                                                 &headers_module);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
                 "headers: ap_headers_output_filter()");

    /* do the fixup */
    do_headers_fixup(f->r, f->r->err_headers_out, dirconf->fixup_err);
    do_headers_fixup(f->r, f->r->headers_out, dirconf->fixup_out);

    /* remove ourselves from the filter chain */
    ap_remove_output_filter(f);

    /* send the data up the stack */
    return ap_pass_brigade(f->next,in);
}

static apr_status_t ap_headers_error_filter(ap_filter_t *f,
                                            apr_bucket_brigade *in)
{
    headers_conf *dirconf = ap_get_module_config(f->r->per_dir_config,
                                                 &headers_module);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
                 "headers: ap_headers_error_filter()");

    /* do the fixup */
    do_headers_fixup(f->r, f->r->err_headers_out, dirconf->fixup_err);

    /* remove ourselves from the filter chain */
    ap_remove_output_filter(f);

    /* send the data up the stack */
    return ap_pass_brigade(f->next,in);
}

static apr_status_t ap_headers_fixup(request_rec *r)
{
    headers_conf *dirconf = ap_get_module_config(r->per_dir_config,
                                                 &headers_module);

    /* do the fixup */
    if (dirconf->fixup_in->nelts) {
        do_headers_fixup(r, r->headers_in, dirconf->fixup_in);
    }

    return DECLINED;
}
                                        
static const command_rec headers_cmds[] =
{
    AP_INIT_RAW_ARGS("Header", header_cmd, &hdr_out, OR_FILEINFO,
                   "an optional condition, an action, header and value "
                   "followed by optional env clause"),
    AP_INIT_RAW_ARGS("RequestHeader", header_cmd, &hdr_in, OR_FILEINFO,
                   "an action, header and value"),
    {NULL}
};

static void register_format_tag_handler(apr_pool_t *p, char *tag, void *tag_handler, int def)
{
    const void *h = apr_palloc(p, sizeof(h));
    h = tag_handler;
    apr_hash_set(format_tag_hash, tag, 1, h);
}
static int header_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    format_tag_hash = apr_hash_make(p);
    register_format_tag_handler(p, "D", (void*) header_request_duration, 0);
    register_format_tag_handler(p, "t", (void*) header_request_time, 0);
    register_format_tag_handler(p, "e", (void*) header_request_env_var, 0);

    return OK;
}

static void register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(header_pre_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_insert_filter(ap_headers_insert_output_filter, NULL, NULL, APR_HOOK_LAST);
    ap_hook_insert_error_filter(ap_headers_insert_error_filter, NULL, NULL, APR_HOOK_LAST);
    ap_hook_fixups(ap_headers_fixup, NULL, NULL, APR_HOOK_LAST);
    ap_register_output_filter("FIXUP_HEADERS_OUT", ap_headers_output_filter,
                              NULL, AP_FTYPE_CONTENT_SET);
    ap_register_output_filter("FIXUP_HEADERS_ERR", ap_headers_error_filter,
                              NULL, AP_FTYPE_CONTENT_SET);
}

module AP_MODULE_DECLARE_DATA headers_module =
{
    STANDARD20_MODULE_STUFF,
    create_headers_config,      /* dir config creater */
    merge_headers_config,       /* dir merger --- default is to override */
    NULL,                       /* server config */
    NULL,                       /* merge server configs */
    headers_cmds,               /* command apr_table_t */
    register_hooks              /* register hooks */
};
