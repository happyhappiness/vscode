static apr_status_t htdbm_init(apr_pool_t **pool, htdbm_t **hdbm) 
{

#if APR_CHARSET_EBCDIC
    apr_status_t rv;
#endif

    apr_pool_create( pool, NULL);
    apr_signal(SIGINT, (void (*)(int)) htdbm_interrupted);

    (*hdbm) = (htdbm_t *)apr_pcalloc(*pool, sizeof(htdbm_t));
    (*hdbm)->pool = *pool;

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&((*hdbm)->to_ascii), "ISO8859-1", APR_DEFAULT_CHARSET, (*hdbm)->pool);
    if (rv) {
        fprintf(stderr, "apr_xlate_open(to ASCII)->%d\n", rv);
        return APR_EGENERAL;
    }
    rv = apr_SHA1InitEBCDIC((*hdbm)->to_ascii);
    if (rv) {
        fprintf(stderr, "apr_SHA1InitEBCDIC()->%d\n", rv);
        return APR_EGENERAL;
    }
    rv = apr_MD5InitEBCDIC((*hdbm)->to_ascii);
    if (rv) {
        fprintf(stderr, "apr_MD5InitEBCDIC()->%d\n", rv);
        return APR_EGENERAL;
    }
#endif /*APR_CHARSET_EBCDIC*/

    /* Set MD5 as default */
    (*hdbm)->alg = ALG_APMD5;
    (*hdbm)->type = "default";
    return APR_SUCCESS;
}