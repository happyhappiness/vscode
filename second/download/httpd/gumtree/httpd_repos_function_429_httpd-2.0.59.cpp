static int fixup_env_module(request_rec *r)
{
    apr_table_t *e = r->subprocess_env;
    env_dir_config_rec *sconf = ap_get_module_config(r->per_dir_config,
                                                     &env_module);
    apr_table_t *vars = sconf->vars;

    if (!apr_table_elts(sconf->vars)->nelts)
        return DECLINED;

    r->subprocess_env = apr_table_overlay(r->pool, e, vars);

    return OK;
}