static void *x_merge_dir_config(apr_pool_t *p, void *parent_conf,
                                      void *newloc_conf)
{

    x_cfg *merged_config = (x_cfg *) apr_pcalloc(p, sizeof(x_cfg));
    x_cfg *pconf = (x_cfg *) parent_conf;
    x_cfg *nconf = (x_cfg *) newloc_conf;
    char *note;

    /*
     * Some things get copied directly from the more-specific record, rather
     * than getting merged.
     */
    merged_config->local = nconf->local;
    merged_config->loc = apr_pstrdup(p, nconf->loc);
    /*
     * Others, like the setting of the `congenital' flag, get ORed in.  The
     * setting of that particular flag, for instance, is TRUE if it was ever
     * true anywhere in the upstream configuration.
     */
    merged_config->congenital = (pconf->congenital | pconf->local);
    /*
     * If we're merging records for two different types of environment (server
     * and directory), mark the new record appropriately.  Otherwise, inherit
     * the current value.
     */
    merged_config->cmode =
        (pconf->cmode == nconf->cmode) ? pconf->cmode : CONFIG_MODE_COMBO;
    /*
     * Now just record our being called in the trace list.  Include the
     * locations we were asked to merge.
     */
    note = apr_psprintf(p, "x_merge_dir_config(p == %pp, parent_conf == "
                        "%pp, newloc_conf == %pp)", (void*) p,
                        (void*) parent_conf, (void*) newloc_conf);
    trace_startup(p, NULL, merged_config, note);
    return (void *) merged_config;
}