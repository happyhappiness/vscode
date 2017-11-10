static void trace_connection(conn_rec *c, const char *note)
{
    const char *trace_copy, *sofar;
    char *addon, *where;
    void *data;
    x_cfg *cfg;

#if EXAMPLE_LOG_EACH
    example_log_each(c->pool, c->base_server, note);
#endif

    cfg = our_cconfig(c);

    where = (cfg != NULL) ? cfg->loc : "nowhere";
    where = (where != NULL) ? where : "";

    addon = apr_pstrcat(c->pool,
                        "   <li>\n"
                        "    <dl>\n"
                        "     <dt><samp>", note, "</samp></dt>\n"
                        "     <dd><samp>[", where, "]</samp></dd>\n"
                        "    </dl>\n"
                        "   </li>\n",
                        NULL);

    /* Find existing notes and copy */
    apr_pool_userdata_get(&data, CONN_NOTE, c->pool);
    sofar = (data == NULL) ? "" : (const char *) data;

    /* Tack addon onto copy */
    trace_copy = apr_pstrcat(c->pool, sofar, addon, NULL);

    /*
     * Stash copy back into pool notes.  This call has a cleanup
     * parameter, but we're not using it because the string has been
     * allocated from that same pool.  There is also an unused return
     * value: we have nowhere to communicate any error that might
     * occur, and will have to check for the existence of this data on
     * the other end.
     */
    apr_pool_userdata_set((const void *) trace_copy, CONN_NOTE,
                          NULL, c->pool);
}