static void trace_startup(apr_pool_t *p, server_rec *s, x_cfg *mconfig,
                          const char *note)
{
    const char *sofar;
    char *where, *addon;

#if EXAMPLE_LOG_EACH
    example_log_each(p, s, note);
#endif

    /*
     * If we weren't passed a configuration record, we can't figure out to
     * what location this call applies.  This only happens for co-routines
     * that don't operate in a particular directory or server context.  If we
     * got a valid record, extract the location (directory or server) to which
     * it applies.
     */
    where = (mconfig != NULL) ? mconfig->loc : "nowhere";
    where = (where != NULL) ? where : "";

    addon = apr_pstrcat(p,
                        "   <li>\n"
                        "    <dl>\n"
                        "     <dt><samp>", note, "</samp></dt>\n"
                        "     <dd><samp>[", where, "]</samp></dd>\n"
                        "    </dl>\n"
                        "   </li>\n",
                        NULL);

    /*
     * Make sure that we start with a valid string, even if we have never been
     * called.
     */
    sofar = (trace == NULL) ? "" : trace;

    trace = apr_pstrcat(p, sofar, addon, NULL);
}