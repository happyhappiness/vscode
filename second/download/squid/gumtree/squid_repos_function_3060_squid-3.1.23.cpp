cache_key *
storeKeyCopy(cache_key * dst, const cache_key * src)
{
    xmemcpy(dst, src, SQUID_MD5_DIGEST_LENGTH);
    return dst;
}