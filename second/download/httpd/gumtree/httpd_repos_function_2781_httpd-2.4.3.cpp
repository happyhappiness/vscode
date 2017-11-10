static void *authn_dbd_merge_conf(apr_pool_t *pool, void *BASE, void *ADD)
{
    authn_dbd_conf *add = ADD;
    authn_dbd_conf *base = BASE;
    authn_dbd_conf *ret = apr_palloc(pool, sizeof(authn_dbd_conf));
    ret->user = (add->user == NULL) ? base->user : add->user;
    ret->realm = (add->realm == NULL) ? base->realm : add->realm;
    return ret;
}