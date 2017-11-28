int
storeKeyNull(const cache_key * key)
{
    if (memcmp(key, null_key, SQUID_MD5_DIGEST_LENGTH) == 0)
        return 1;
    else
        return 0;
}