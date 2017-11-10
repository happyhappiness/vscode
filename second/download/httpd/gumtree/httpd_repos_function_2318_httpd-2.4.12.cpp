static void *filter_merge(apr_pool_t *pool, void *BASE, void *ADD)
{
    mod_filter_cfg *base = BASE;
    mod_filter_cfg *add = ADD;
    mod_filter_chain *savelink = 0;
    mod_filter_chain *newlink;
    mod_filter_chain *p;
    mod_filter_cfg *conf = apr_palloc(pool, sizeof(mod_filter_cfg));

    conf->live_filters = apr_hash_overlay(pool, add->live_filters,
                                          base->live_filters);
    if (base->chain && add->chain) {
        for (p = base->chain; p; p = p->next) {
            newlink = apr_pmemdup(pool, p, sizeof(mod_filter_chain));
            if (newlink->fname == NULL) {
                conf->chain = savelink = newlink;
            }
            else if (savelink) {
                savelink->next = newlink;
                savelink = newlink;
            }
            else {
                conf->chain = savelink = newlink;
            }
        }

        for (p = add->chain; p; p = p->next) {
            newlink = apr_pmemdup(pool, p, sizeof(mod_filter_chain));
            /** Filter out merged chain resets */
            if (newlink->fname == NULL) {
                conf->chain = savelink = newlink;
            }
            else if (savelink) {
                savelink->next = newlink;
                savelink = newlink;
            }
            else {
                conf->chain = savelink = newlink;
            }
        }
    }
    else if (add->chain) {
        conf->chain = add->chain;
    }
    else {
        conf->chain = base->chain;
    }

    return conf;
}