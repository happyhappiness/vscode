        }
    }
}

static void ap_headers_insert_output_filter(request_rec *r)
{
    headers_conf *dirconf = ap_get_module_config(r->per_dir_config,
                                                 &headers_module);

    if (dirconf->fixup_out->nelts || dirconf->fixup_err->nelts) {
        ap_add_output_filter("FIXUP_HEADERS_OUT", NULL, r, r->connection);
    }
}

static void ap_headers_insert_error_filter(request_rec *r)
{
    headers_conf *dirconf = ap_get_module_config(r->per_dir_config,
                                                 &headers_module);

    if (dirconf->fixup_err->nelts) {
        ap_add_output_filter("FIXUP_HEADERS_ERR", NULL, r, r->connection);
    }
}

static apr_status_t ap_headers_output_filter(ap_filter_t *f,
                                             apr_bucket_brigade *in)
{
    headers_conf *dirconf = ap_get_module_config(f->r->per_dir_config,
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
