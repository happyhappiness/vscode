static void cipher_init(apr_pool_t *pool)
{
    apr_hash_t *hash = apr_hash_make(pool);
    const char *source;
    unsigned int i;
    
    source = "rfc7540";
    for (i = 0; i < RFC7540_names_LEN; ++i) {
        apr_hash_set(hash, RFC7540_names[i], APR_HASH_KEY_STRING, source);
    }
    
    BLCNames = hash;
}