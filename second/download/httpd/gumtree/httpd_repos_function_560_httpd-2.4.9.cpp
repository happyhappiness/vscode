static void *make_cookie_dir(apr_pool_t *p, char *d)
{
    cookie_dir_rec *dcfg;

    dcfg = (cookie_dir_rec *) apr_pcalloc(p, sizeof(cookie_dir_rec));
    dcfg->cookie_name = COOKIE_NAME;
    dcfg->cookie_domain = NULL;
    dcfg->style = CT_UNSET;
    dcfg->enabled = 0;

    /* In case the user does not use the CookieName directive,
     * we need to compile the regexp for the default cookie name. */
    set_and_comp_regexp(dcfg, p, COOKIE_NAME);

    return dcfg;
}