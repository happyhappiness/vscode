    return TRUE;
}

int ssl_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->nMutexMode == SSL_MUTEXMODE_NONE)
        return TRUE;

    if (apr_global_mutex_child_init(&mc->pMutex,
                                    mc->szMutexFile, p) != APR_SUCCESS)
        return FALSE;
    return TRUE;
}

int ssl_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
