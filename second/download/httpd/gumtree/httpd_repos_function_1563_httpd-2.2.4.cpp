static const char *filter_chain(cmd_parms *cmd, void *CFG, const char *arg)
{
    mod_filter_chain *p;
    mod_filter_chain *q;
    mod_filter_cfg *cfg = CFG;

    switch (arg[0]) {
    case '+':        /* add to end of chain */
        p = apr_pcalloc(cmd->pool, sizeof(mod_filter_chain));
        p->fname = arg+1;
        if (cfg->chain) {
            for (q = cfg->chain; q->next; q = q->next);
            q->next = p;
        }
        else {
            cfg->chain = p;
        }
        break;

    case '@':        /* add to start of chain */
        p = apr_palloc(cmd->pool, sizeof(mod_filter_chain));
        p->fname = arg+1;
        p->next = cfg->chain;
        cfg->chain = p;
        break;

    case '-':        /* remove from chain */
        if (cfg->chain) {
            if (strcasecmp(cfg->chain->fname, arg+1)) {
                for (p = cfg->chain; p->next; p = p->next) {
                    if (!strcasecmp(p->next->fname, arg+1)) {
                        p->next = p->next->next;
                    }
                }
            }
            else {
                cfg->chain = cfg->chain->next;
            }
        }
        break;

    case '!':        /* Empty the chain */
        cfg->chain = NULL;
        break;

    case '=':        /* initialise chain with this arg */
        p = apr_pcalloc(cmd->pool, sizeof(mod_filter_chain));
        p->fname = arg+1;
        cfg->chain = p;
        break;

    default:        /* add to end */
        p = apr_pcalloc(cmd->pool, sizeof(mod_filter_chain));
        p->fname = arg;
        if (cfg->chain) {
            for (q = cfg->chain; q->next; q = q->next);
            q->next = p;
        }
        else {
            cfg->chain = p;
        }
        break;
    }

    return NULL;
}