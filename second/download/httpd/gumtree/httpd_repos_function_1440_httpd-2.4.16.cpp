static int dbd_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                           apr_pool_t *ptemp, server_rec *s)
{
    server_rec *sp;
    apr_array_header_t *add_queries = apr_array_make(ptemp, 10,
                                                     sizeof(dbd_query_t));

    for (sp = s; sp; sp = sp->next) {
        svr_cfg *svr = ap_get_module_config(sp->module_config, &dbd_module);
        dbd_cfg_t *cfg = svr->cfg;
        apr_hash_index_t *hi_first = apr_hash_first(ptemp, cfg->queries);
        dbd_group_t *group;

        /* dbd_setup in 2.2.3 and under was causing spurious error messages
         * when dbd isn't configured.  We can stop that with a quick check here
         * together with a similar check in ap_dbd_open (where being
         * unconfigured is a genuine error that must be reported).
         */
        if (cfg->name == no_dbdriver || !cfg->persist) {
            continue;
        }

        for (group = group_list; group; group = group->next) {
            dbd_cfg_t *group_cfg = group->cfg;
            apr_hash_index_t *hi;
            int group_ok = 1;

            if (strcmp(cfg->name, group_cfg->name)
                || strcmp(cfg->params, group_cfg->params)) {
                continue;
            }

#if APR_HAS_THREADS
            if (cfg->nmin != group_cfg->nmin
                || cfg->nkeep != group_cfg->nkeep
                || cfg->nmax != group_cfg->nmax
                || cfg->exptime != group_cfg->exptime) {
                continue;
            }
#endif

            add_queries->nelts = 0;

            for (hi = hi_first; hi; hi = apr_hash_next(hi)) {
                const char *label, *query;
                const char *group_query;

                apr_hash_this(hi, (void*) &label, NULL, (void*) &query);

                group_query = apr_hash_get(group_cfg->queries, label,
                                           APR_HASH_KEY_STRING);

                if (!group_query) {
                    dbd_query_t *add_query = apr_array_push(add_queries);

                    add_query->label = label;
                    add_query->query = query;
                }
                else if (strcmp(query, group_query)) {
                    group_ok = 0;
                    break;
                }
            }

            if (group_ok) {
                int i;

                for (i = 0; i < add_queries->nelts; ++i) {
                    dbd_query_t *add_query = ((dbd_query_t*) add_queries->elts)
                                             + i;

                    apr_hash_set(group_cfg->queries, add_query->label,
                                 APR_HASH_KEY_STRING, add_query->query);
                }

                svr->group = group;
                break;
            }
        }

        if (!svr->group) {
            svr->group = group = apr_pcalloc(pconf, sizeof(dbd_group_t));

            group->cfg = cfg;

            group->next = group_list;
            group_list = group;
        }
    }

    return OK;
}