static void *create_substitute_dcfg(apr_pool_t *p, char *d)
{
    subst_dir_conf *dcfg =
    (subst_dir_conf *) apr_pcalloc(p, sizeof(subst_dir_conf));

    dcfg->patterns = apr_array_make(p, 10, sizeof(subst_pattern_t));
    return dcfg;
}