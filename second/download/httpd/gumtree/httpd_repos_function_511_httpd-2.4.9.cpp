static int fixup_env_module(request_rec *r)
{
    env_dir_config_rec *sconf = ap_get_module_config(r->per_dir_config,
                                                     &env_module);

    if (apr_is_empty_table(sconf->vars)) {
        return DECLINED;
    }

    r->subprocess_env = apr_table_overlay(r->pool, r->subprocess_env,
            sconf->vars);

    return OK;
}