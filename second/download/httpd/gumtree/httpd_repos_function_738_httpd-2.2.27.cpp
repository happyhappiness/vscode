void ssl_asn1_table_unset(apr_hash_t *table,
                          const char *key)
{
    apr_ssize_t klen = strlen(key);
    ssl_asn1_t *asn1 = apr_hash_get(table, key, klen);

    if (!asn1) {
        return;
    }

    if (asn1->cpData) {
        free(asn1->cpData);
    }
    free(asn1);

    apr_hash_set(table, key, klen, NULL);
}