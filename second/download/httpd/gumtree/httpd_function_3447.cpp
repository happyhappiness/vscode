static int cache_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    /* we are just a marker, so let's just remove ourselves */
    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, f->r->server,
                 "cache: CACHE filter was added twice, or was added in quick "
    		     "handler mode and will be ignored.");
    ap_remove_output_filter(f);
    return ap_pass_brigade(f->next, in);
}