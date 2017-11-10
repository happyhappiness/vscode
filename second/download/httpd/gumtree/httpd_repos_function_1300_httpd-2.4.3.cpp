static void *create_imap_dir_config(apr_pool_t *p, char *dummy)
{
    imap_conf_rec *icr =
    (imap_conf_rec *) apr_palloc(p, sizeof(imap_conf_rec));

    icr->imap_menu = NULL;
    icr->imap_default = NULL;
    icr->imap_base = NULL;

    return icr;
}