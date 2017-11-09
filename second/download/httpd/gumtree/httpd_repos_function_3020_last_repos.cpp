static void *create_substitute_dcfg(apr_pool_t *p, char *d)
{
    subst_dir_conf *dcfg =
        (subst_dir_conf *) apr_palloc(p, sizeof(subst_dir_conf));

    dcfg->patterns = apr_array_make(p, 10, sizeof(subst_pattern_t));
    dcfg->max_line_length = AP_SUBST_MAX_LINE_LENGTH;
    dcfg->max_line_length_set = 0;
    dcfg->inherit_before = -1;
    return dcfg;
}