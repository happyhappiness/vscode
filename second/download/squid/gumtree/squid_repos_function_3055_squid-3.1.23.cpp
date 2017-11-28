const cache_key *
storeKeyPrivate(const char *url, const HttpRequestMethod& method, int id)
{
    static cache_key digest[SQUID_MD5_DIGEST_LENGTH];
    SquidMD5_CTX M;
    assert(id > 0);
    debugs(20, 3, "storeKeyPrivate: " << RequestMethodStr(method) << " " << url);
    SquidMD5Init(&M);
    SquidMD5Update(&M, (unsigned char *) &id, sizeof(id));
    SquidMD5Update(&M, (unsigned char *) &method, sizeof(method));
    SquidMD5Update(&M, (unsigned char *) url, strlen(url));
    SquidMD5Final(digest, &M);
    return digest;
}