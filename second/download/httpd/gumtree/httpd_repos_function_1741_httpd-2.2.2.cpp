static void *x_merge_server_config(apr_pool_t *p, void *server1_conf,
                                         void *server2_conf)
{

    x_cfg *merged_config = (x_cfg *) apr_pcalloc(p, sizeof(x_cfg));
    x_cfg *s1conf = (x_cfg *) server1_conf;
    x_cfg *s2conf = (x_cfg *) server2_conf;
    char *note;

    /*
     * Our inheritance rules are our own, and part of our module's semantics.
     * Basically, just note whence we came.
     */
    merged_config->cmode =
        (s1conf->cmode == s2conf->cmode) ? s1conf->cmode : CONFIG_MODE_COMBO;
    merged_config->local = s2conf->local;
    merged_config->congenital = (s1conf->congenital | s1conf->local);
    merged_config->loc = apr_pstrdup(p, s2conf->loc);
    /*
     * Trace our call, including what we were asked to merge.
     */
    note = apr_pstrcat(p, "x_merge_server_config(\"", s1conf->loc, "\",\"",
                   s2conf->loc, "\")", NULL);
    trace_add(NULL, NULL, merged_config, note);
    return (void *) merged_config;
}