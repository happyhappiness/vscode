static void trace_add(server_rec *s, request_rec *r, x_cfg *mconfig,
                      const char *note)
{
    const char *sofar;
    char *addon;
    char *where;
    apr_pool_t *p;
    const char *trace_copy;

    /*
     * Make sure our pools and tables are set up - we need 'em.
     */
    setup_module_cells();
    /*
     * Now, if we're in request-context, we use the request pool.
     */
    if (r != NULL) {
        p = r->pool;
        if ((trace_copy = apr_table_get(r->notes, TRACE_NOTE)) == NULL) {
            trace_copy = "";
        }
    }
    else {
        /*
         * We're not in request context, so the trace gets attached to our
         * module-wide pool.  We do the create/destroy every time we're called
         * in non-request context; this avoids leaking memory in some of
         * the subsequent calls that allocate memory only once (such as the
         * key formation below).
         *
         * Make a new sub-pool and copy any existing trace to it.  Point the
         * trace cell at the copied value.
         */
        apr_pool_create(&p, x_pool);
        if (trace != NULL) {
            trace = apr_pstrdup(p, trace);
        }
        /*
         * Now, if we have a sub-pool from before, nuke it and replace with
         * the one we just allocated.
         */
        if (x_subpool != NULL) {
            apr_pool_destroy(x_subpool);
        }
        x_subpool = p;
        trace_copy = trace;
    }
    /*
     * If we weren't passed a configuration record, we can't figure out to
     * what location this call applies.  This only happens for co-routines
     * that don't operate in a particular directory or server context.  If we
     * got a valid record, extract the location (directory or server) to which
     * it applies.
     */
    where = (mconfig != NULL) ? mconfig->loc : "nowhere";
    where = (where != NULL) ? where : "";
    /*
     * Now, if we're not in request context, see if we've been called with
     * this particular combination before.  The apr_table_t is allocated in the
     * module's private pool, which doesn't get destroyed.
     */
    if (r == NULL) {
        char *key;

        key = apr_pstrcat(p, note, ":", where, NULL);
        if (apr_table_get(static_calls_made, key) != NULL) {
            /*
             * Been here, done this.
             */
            return;
        }
        else {
            /*
             * First time for this combination of routine and environment -
             * log it so we don't do it again.
             */
            apr_table_set(static_calls_made, key, "been here");
        }
    }
    addon = apr_pstrcat(p,
                        "   <li>\n"
                        "    <dl>\n"
                        "     <dt><samp>", note, "</samp></dt>\n"
                        "     <dd><samp>[", where, "]</samp></dd>\n"
                        "    </dl>\n"
                        "   </li>\n",
                        NULL);
    sofar = (trace_copy == NULL) ? "" : trace_copy;
    trace_copy = apr_pstrcat(p, sofar, addon, NULL);
    if (r != NULL) {
        apr_table_set(r->notes, TRACE_NOTE, trace_copy);
    }
    else {
        trace = trace_copy;
    }
    /*
     * You *could* change the following if you wanted to see the calling
     * sequence reported in the server's error_log, but beware - almost all of
     * these co-routines are called for every single request, and the impact
     * on the size (and readability) of the error_log is considerable.
     */
#define EXAMPLE_LOG_EACH 0
    if (EXAMPLE_LOG_EACH && (s != NULL)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "mod_example: %s", note);
    }
}