const cache_key *
storeKeyPublic(const char *url, const HttpRequestMethod& method, const KeyScope keyScope)
{
    static cache_key digest[SQUID_MD5_DIGEST_LENGTH];
    unsigned char m = (unsigned char) method.id();
    SquidMD5_CTX M;
    SquidMD5Init(&M);
    SquidMD5Update(&M, &m, sizeof(m));
    SquidMD5Update(&M, (unsigned char *) url, strlen(url));
    if (keyScope)
        SquidMD5Update(&M, &keyScope, sizeof(keyScope));
    SquidMD5Final(digest, &M);
    return digest;
}