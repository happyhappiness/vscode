static void *am_merge_conf(apr_pool_t *pool, void *a, void *b)
{
    am_conf_t *base = (am_conf_t *)a;
    am_conf_t *add = (am_conf_t *)b;
    am_conf_t *conf = apr_palloc(pool, sizeof(am_conf_t));

    if (add->allowed_set) {
        conf->allowed = add->allowed;
        conf->allowed_set = add->allowed_set;
    }
    else {
        conf->allowed = base->allowed;
        conf->allowed_set = base->allowed_set;
    }

    return conf;
}