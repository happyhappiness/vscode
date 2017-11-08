static void *merge_includes_dir_config(apr_pool_t *p, void *basev, void *overridesv)
{
    include_dir_config *base = (include_dir_config *)basev,
                       *over = (include_dir_config *)overridesv,
                       *new  = apr_palloc(p, sizeof(include_dir_config));
    MERGE(base, over, new, default_error_msg, NULL);
    MERGE(base, over, new, default_time_fmt,  NULL);
    MERGE(base, over, new, undefined_echo,    NULL);
    MERGE(base, over, new, xbithack,          XBITHACK_UNSET);
    MERGE(base, over, new, lastmodified,      UNSET);
    MERGE(base, over, new, etag,              UNSET);
    MERGE(base, over, new, legacy_expr,       UNSET);
    return new;
}