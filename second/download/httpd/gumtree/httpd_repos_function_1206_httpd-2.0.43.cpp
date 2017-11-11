void ap_process_request(request_rec *r)
{
    int access_status;

    /* Give quick handlers a shot at serving the request on the fast
     * path, bypassing all of the other Apache hooks.
     *
     * This hook was added to enable serving files out of a URI keyed 
     * content cache ( e.g., Mike Abbott's Quick Shortcut Cache, 
     * described here: http://oss.sgi.com/projects/apache/mod_qsc.html )
     *
     * It may have other uses as well, such as routing requests directly to
     * content handlers that have the ability to grok HTTP and do their
     * own access checking, etc (e.g. servlet engines). 
     * 
     * Use this hook with extreme care and only if you know what you are 
     * doing.
     */
    access_status = ap_run_quick_handler(r, 0);  /* Not a look-up request */
    if (access_status == DECLINED) {
        access_status = ap_process_request_internal(r);
        if (access_status == OK) {
            access_status = ap_invoke_handler(r);
        }
    }

    if (access_status == DONE) {
        /* e.g., something not in storage like TRACE */
        access_status = OK;
    }

    if (access_status == OK) {
        ap_finalize_request_protocol(r);
    }
    else {
        ap_die(access_status, r);
    }
    
    /*
     * We want to flush the last packet if this isn't a pipelining connection
     * *before* we start into logging.  Suppose that the logging causes a DNS
     * lookup to occur, which may have a high latency.  If we hold off on
     * this packet, then it'll appear like the link is stalled when really
     * it's the application that's stalled.
     */
    check_pipeline_flush(r);
    ap_run_log_transaction(r);
}