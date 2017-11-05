static int cache_conditional_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
                 "cache: running CACHE_CONDITIONAL filter");

    if (f->r->status == HTTP_NOT_MODIFIED) {
        /* replace ourselves with CACHE_OUT filter */
        ap_add_output_filter_handle(cache_out_filter_handle, NULL,
                                    f->r, f->r->connection);
    }
    else {
        /* replace ourselves with CACHE_SAVE filter */
        ap_add_output_filter_handle(cache_save_filter_handle, NULL,
                                    f->r, f->r->connection);
    }
    ap_remove_output_filter(f);

    return ap_pass_brigade(f->next, in);
}