static void *merge_substitute_dcfg(apr_pool_t *p, void *basev, void *overv)
{
    subst_dir_conf *a =
        (subst_dir_conf *) apr_palloc(p, sizeof(subst_dir_conf));
    subst_dir_conf *base = (subst_dir_conf *) basev;
    subst_dir_conf *over = (subst_dir_conf *) overv;

    a->inherit_before = (over->inherit_before != -1)
                            ? over->inherit_before
                            : base->inherit_before;
    /* SubstituteInheritBefore wasn't the default behavior until 2.5.x,
     * and may be re-disabled as desired; the original default behavior
     * was to apply inherited subst patterns after locally scoped patterns.
     * In later 2.2 and 2.4 versions, SubstituteInheritBefore may be toggled
     * 'on' to follow the corrected/expected behavior, without violating POLS.
     */
    if (a->inherit_before == 1) {
        a->patterns = apr_array_append(p, base->patterns,
                                          over->patterns);
    }
    else {
        a->patterns = apr_array_append(p, over->patterns,
                                          base->patterns);
    }
    a->max_line_length = over->max_line_length_set ?
                             over->max_line_length : base->max_line_length;
    a->max_line_length_set = over->max_line_length_set
                           | base->max_line_length_set;
    return a;
}