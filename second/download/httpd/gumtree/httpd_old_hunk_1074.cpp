    apr_terminate();
#ifdef NETWARE
    pressanykey();
#endif
}

static void htdbm_terminate(htdbm_t *htdbm) 
{
    if (htdbm->dbm)
        apr_dbm_close(htdbm->dbm);
    htdbm->dbm = NULL;
}

static htdbm_t *h;
  
static void htdbm_interrupted(void) 
{
    htdbm_terminate(h);
    fprintf(stderr, "htdbm Interrupted !\n");
    exit(ERR_INTERRUPTED);
}

static apr_status_t htdbm_init(apr_pool_t **pool, htdbm_t **hdbm) 
{

#if APR_CHARSET_EBCDIC
    apr_status_t rv;
#endif

