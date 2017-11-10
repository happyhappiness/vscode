static void *merge_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    dir_config_rec *new = apr_pcalloc(p, sizeof(dir_config_rec));
    dir_config_rec *base = (dir_config_rec *)basev;
    dir_config_rec *add = (dir_config_rec *)addv;

    new->index_names = add->index_names ? add->index_names : base->index_names;
    new->do_slash =
        (add->do_slash == SLASH_UNSET) ? base->do_slash : add->do_slash;
    new->redirect_index=
        (add->redirect_index == REDIRECT_UNSET) ? base->redirect_index : add->redirect_index;
    new->dflt = add->dflt ? add->dflt : base->dflt;
    return new;
}