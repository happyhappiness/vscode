ssl_asn1_t *ssl_asn1_table_get(apr_hash_t *table,
                               const char *key)
{
    return (ssl_asn1_t *)apr_hash_get(table, key, APR_HASH_KEY_STRING);
}