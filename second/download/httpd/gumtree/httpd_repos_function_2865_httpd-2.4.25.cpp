void h2_h2_register_hooks(void)
{
    /* Our main processing needs to run quite late. Definitely after mod_ssl,
     * as we need its connection filters, but also before reqtimeout as its
     * method of timeouts is specific to HTTP/1.1 (as of now).
     * The core HTTP/1 processing run as REALLY_LAST, so we will have
     * a chance to take over before it.
     */
    ap_hook_process_connection(h2_h2_process_conn, 
                               mod_ssl, mod_reqtimeout, APR_HOOK_LAST);
    
    /* One last chance to properly say goodbye if we have not done so
     * already. */
    ap_hook_pre_close_connection(h2_h2_pre_close_conn, NULL, mod_ssl, APR_HOOK_LAST);

    /* With "H2SerializeHeaders On", we install the filter in this hook
     * that parses the response. This needs to happen before any other post
     * read function terminates the request with an error. Otherwise we will
     * never see the response.
     */
    ap_hook_post_read_request(h2_h2_post_read_req, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_fixups(h2_h2_late_fixups, NULL, NULL, APR_HOOK_LAST);

    /* special bucket type transfer through a h2_bucket_beam */
    h2_register_bucket_beamer(h2_bucket_headers_beam);
    h2_register_bucket_beamer(h2_bucket_observer_beam);
}