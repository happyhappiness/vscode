static void x_child_init(apr_pool_t *p, server_rec *s)
{
    char *note;
    char *sname = s->server_hostname;

    /*
     * Set up any module cells that ought to be initialised.
     */
    setup_module_cells();
    /*
     * The arbitrary text we add to our trace entry indicates for which server
     * we're being called.
     */
    sname = (sname != NULL) ? sname : "";
    note = apr_pstrcat(p, "x_child_init(", sname, ")", NULL);
    trace_add(s, NULL, NULL, note);

    apr_pool_cleanup_register(p, s, x_child_exit, x_child_exit);
}