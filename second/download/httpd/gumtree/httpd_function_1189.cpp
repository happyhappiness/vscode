static apr_status_t htdbm_list(htdbm_t *htdbm) 
{
    apr_status_t rv;
    apr_datum_t key, val;
    char *rec, *cmnt;
    char kb[MAX_STRING_LEN];
    int i = 0;

    rv = apr_dbm_firstkey(htdbm->dbm, &key);
    if (rv != APR_SUCCESS) {
        fprintf(stderr, "Empty database -- %s\n", htdbm->filename); 
        return APR_ENOENT;
    }
    rec = apr_pcalloc(htdbm->pool, HUGE_STRING_LEN);

    fprintf(stderr, "Dumping records from database -- %s\n", htdbm->filename); 
    fprintf(stderr, "    %-32sComment\n", "Username");    
    while (key.dptr != NULL) {
        rv = apr_dbm_fetch(htdbm->dbm, key, &val);
        if (rv != APR_SUCCESS) {
            fprintf(stderr, "Failed getting data from %s\n", htdbm->filename);
            return APR_EGENERAL;
        }
        strncpy(kb, key.dptr, key.dsize);
        kb[key.dsize] = '\0';
        fprintf(stderr, "    %-32s", kb);
        strncpy(rec, val.dptr, val.dsize);
        rec[val.dsize] = '\0';
        cmnt = strchr(rec, ':');
        if (cmnt)
            fprintf(stderr, cmnt + 1);
        fprintf(stderr, "\n");
        rv = apr_dbm_nextkey(htdbm->dbm, &key);
        if (rv != APR_SUCCESS)
            fprintf(stderr, "Failed getting NextKey\n");
        ++i;
    }

    fprintf(stderr, "Total #records : %d\n", i);
    return APR_SUCCESS;
}