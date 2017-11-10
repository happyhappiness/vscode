static void *x_create_dir_config(apr_pool_t *p, char *dirspec)
{
    x_cfg *cfg;
    char *dname = dirspec;
    char *note;

    /*
     * Allocate the space for our record from the pool supplied.
     */
    cfg = (x_cfg *) apr_pcalloc(p, sizeof(x_cfg));
    /*
     * Now fill in the defaults.  If there are any `parent' configuration
     * records, they'll get merged as part of a separate callback.
     */
    cfg->local = 0;
    cfg->congenital = 0;
    cfg->cmode = CONFIG_MODE_DIRECTORY;
    /*
     * Finally, add our trace to the callback list.
     */
    dname = (dname != NULL) ? dname : "";
    cfg->loc = apr_pstrcat(p, "DIR(", dname, ")", NULL);
    note = apr_psprintf(p, "x_create_dir_config(p == %pp, dirspec == %s)",
                        (void*) p, dirspec);
    trace_startup(p, NULL, cfg, note);
    return (void *) cfg;
}