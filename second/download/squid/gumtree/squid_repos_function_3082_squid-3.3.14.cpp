const char *
storeKeyText(const cache_key *key)
{
    static char buf[SQUID_MD5_DIGEST_LENGTH * 2+1];
    int i;

    for (i = 0; i < SQUID_MD5_DIGEST_LENGTH; ++i)
        snprintf(&buf[i*2],sizeof(buf) - i*2, "%02X", *(key + i));

    return buf;
}