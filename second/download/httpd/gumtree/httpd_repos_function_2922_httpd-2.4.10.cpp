static void *authz_dbd_merge_cfg(apr_pool_t *pool, void *BASE, void *ADD)
{
    authz_dbd_cfg *base = BASE;
    authz_dbd_cfg *add = ADD;
    authz_dbd_cfg *ret = apr_palloc(pool, sizeof(authz_dbd_cfg));

    ret->query = (add->query == NULL) ? base->query : add->query;
    ret->redir_query = (add->redir_query == NULL)
                            ? base->redir_query : add->redir_query;
    ret->redirect = (add->redirect == -1) ? base->redirect : add->redirect;
    return ret;
}