static void htdbm_terminate(htdbm_t *htdbm) 
{
    
    if (htdbm->dbm)
        apr_dbm_close(htdbm->dbm);
    htdbm->dbm = NULL;
}