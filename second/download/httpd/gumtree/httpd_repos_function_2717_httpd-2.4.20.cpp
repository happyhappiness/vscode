static int cipher_is_blacklisted(const char *cipher, const char **psource)
{   
    *psource = apr_hash_get(BLCNames, cipher, APR_HASH_KEY_STRING);
    return !!*psource;
}