static char *asn1_table_vhost_key(SSLModConfigRec *mc, apr_pool_t *p,
                                  char *id, char *an)
{
    /* 'p' pool used here is cleared on restarts (or sooner) */
    char *key = apr_psprintf(p, "%s:%s", id, an);
    void *keyptr = apr_hash_get(mc->tVHostKeys, key,
                                APR_HASH_KEY_STRING);

    if (!keyptr) {
        /* make a copy out of s->process->pool */
        keyptr = apr_pstrdup(mc->pPool, key);
        apr_hash_set(mc->tVHostKeys, keyptr,
                     APR_HASH_KEY_STRING, keyptr);
    }

    return (char *)keyptr;
}