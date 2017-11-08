static void trace_request(const request_rec *r, const char *note)
{
    const char *trace_copy, *sofar;
    char *addon, *where;
    x_cfg *cfg;

#if EXAMPLE_LOG_EACH
    example_log_each(r->pool, r->server, note);
#endif

    if ((sofar = apr_table_get(r->notes, TRACE_NOTE)) == NULL) {
        sofar = "";
    }

    cfg = our_dconfig(r);

    where = (cfg != NULL) ? cfg->loc : "nowhere";
    where = (where != NULL) ? where : "";

    addon = apr_pstrcat(r->pool,
                        "   <li>\n"
                        "    <dl>\n"
                        "     <dt><samp>", note, "</samp></dt>\n"
                        "     <dd><samp>[", where, "]</samp></dd>\n"
                        "    </dl>\n"
                        "   </li>\n",
                        NULL);

    trace_copy = apr_pstrcat(r->pool, sofar, addon, NULL);
    apr_table_set(r->notes, TRACE_NOTE, trace_copy);
}