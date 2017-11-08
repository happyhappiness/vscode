static void *merge_alias_dir_config(apr_pool_t *p, void *basev, void *overridesv)
{
    alias_dir_conf *a =
    (alias_dir_conf *) apr_pcalloc(p, sizeof(alias_dir_conf));
    alias_dir_conf *base = (alias_dir_conf *) basev;
    alias_dir_conf *overrides = (alias_dir_conf *) overridesv;

    a->redirects = apr_array_append(p, overrides->redirects, base->redirects);

    a->alias = (overrides->alias_set == 0) ? base->alias : overrides->alias;
    a->handler = (overrides->alias_set == 0) ? base->handler : overrides->handler;
    a->alias_set = overrides->alias_set || base->alias_set;

    a->redirect = (overrides->redirect_set == 0) ? base->redirect : overrides->redirect;
    a->redirect_status = (overrides->redirect_set == 0) ? base->redirect_status : overrides->redirect_status;
    a->redirect_set = overrides->redirect_set || base->redirect_set;

    return a;
}