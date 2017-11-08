static void *merge_charset_dir_conf(apr_pool_t *p, void *basev, void *overridesv)
{
    charset_dir_t *a = (charset_dir_t *)apr_pcalloc (p, sizeof(charset_dir_t));
    charset_dir_t *base = (charset_dir_t *)basev,
        *over = (charset_dir_t *)overridesv;

    /* If it is defined in the current container, use it.  Otherwise, use the one
     * from the enclosing container.
     */

    a->debug =
        over->debug != -1 ? over->debug : base->debug;
    a->charset_default =
        over->charset_default ? over->charset_default : base->charset_default;
    a->charset_source =
        over->charset_source ? over->charset_source : base->charset_source;
    a->implicit_add =
        over->implicit_add != IA_INIT ? over->implicit_add : base->implicit_add;
    a->force_xlate=
        over->force_xlate != FX_INIT ? over->force_xlate : base->force_xlate;
    return a;
}