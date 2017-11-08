unsigned char *ssl_asn1_table_set(apr_hash_t *table,
                                  const char *key,
                                  long int length)
{
    apr_ssize_t klen = strlen(key);
    ssl_asn1_t *asn1 = apr_hash_get(table, key, klen);

    /*
     * if a value for this key already exists,
     * reuse as much of the already malloc-ed data
     * as possible.
     */
    if (asn1) {
        if (asn1->nData != length) {
            free(asn1->cpData); /* XXX: realloc? */
            asn1->cpData = NULL;
        }
    }
    else {
        asn1 = malloc(sizeof(*asn1));
        asn1->source_mtime = 0; /* used as a note for encrypted private keys */
        asn1->cpData = NULL;
    }

    asn1->nData = length;
    if (!asn1->cpData) {
        asn1->cpData = malloc(length);
    }

    apr_hash_set(table, key, klen, asn1);

    return asn1->cpData; /* caller will assign a value to this */
}