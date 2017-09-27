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
