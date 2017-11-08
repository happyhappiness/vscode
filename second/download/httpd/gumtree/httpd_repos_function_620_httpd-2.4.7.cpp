static apr_status_t ap_headers_output_filter(ap_filter_t *f,
                                             apr_bucket_brigade *in)
{
    headers_conf *dirconf = ap_get_module_config(f->r->per_dir_config,
                                                 &headers_module);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server, APLOGNO(01502)
                 "headers: ap_headers_output_filter()");

    /* do the fixup */
    do_headers_fixup(f->r, f->r->err_headers_out, dirconf->fixup_err, 0);
    do_headers_fixup(f->r, f->r->headers_out, dirconf->fixup_out, 0);

    /* remove ourselves from the filter chain */
    ap_remove_output_filter(f);

    /* send the data up the stack */
    return ap_pass_brigade(f->next,in);
}