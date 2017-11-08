int SSL_X509_STORE_lookup(X509_STORE *pStore, int nType,
                          X509_NAME *pName, X509_OBJECT *pObj)
{
    X509_STORE_CTX pStoreCtx;
    int rc;

    X509_STORE_CTX_init(&pStoreCtx, pStore, NULL, NULL);
    rc = X509_STORE_get_by_subject(&pStoreCtx, nType, pName, pObj);
    X509_STORE_CTX_cleanup(&pStoreCtx);
    return rc;
}