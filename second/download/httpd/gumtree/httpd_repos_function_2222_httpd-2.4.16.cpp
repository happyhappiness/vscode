static void *merge_substitute_dcfg(apr_pool_t *p, void *basev, void *overv)
{
    subst_dir_conf *a =
    (subst_dir_conf *) apr_pcalloc(p, sizeof(subst_dir_conf));
    subst_dir_conf *base = (subst_dir_conf *) basev;
    subst_dir_conf *over = (subst_dir_conf *) overv;

    a->patterns = apr_array_append(p, over->patterns,
                                                  base->patterns);
    a->max_line_length = over->max_line_length_set ?
                         over->max_line_length : base->max_line_length;
    a->max_line_length_set = over->max_line_length_set ?
                             over->max_line_length_set : base->max_line_length_set;
    return a;
}