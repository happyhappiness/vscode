static void *merge_imap_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    imap_conf_rec *new = (imap_conf_rec *) apr_pcalloc(p, sizeof(imap_conf_rec));
    imap_conf_rec *base = (imap_conf_rec *) basev;
    imap_conf_rec *add = (imap_conf_rec *) addv;

    new->imap_menu = add->imap_menu ? add->imap_menu : base->imap_menu;
    new->imap_default = add->imap_default ? add->imap_default
                                          : base->imap_default;
    new->imap_base = add->imap_base ? add->imap_base : base->imap_base;

    return new;
}