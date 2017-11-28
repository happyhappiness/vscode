const cache_key *
storeKeyPublicByRequestMethod(HttpRequest * request, const HttpRequestMethod& method, const KeyScope keyScope)
{
    static cache_key digest[SQUID_MD5_DIGEST_LENGTH];
    unsigned char m = (unsigned char) method.id();
    const char *url = request->storeId(); /* storeId returns the right storeID\canonical URL for the md5 calc */
    SquidMD5_CTX M;
    SquidMD5Init(&M);
    SquidMD5Update(&M, &m, sizeof(m));
    SquidMD5Update(&M, (unsigned char *) url, strlen(url));

    if (keyScope)
        SquidMD5Update(&M, &keyScope, sizeof(keyScope));

    if (!request->vary_headers.isEmpty()) {
        SquidMD5Update(&M, request->vary_headers.rawContent(), request->vary_headers.length());
        debugs(20, 3, "updating public key by vary headers: " << request->vary_headers << " for: " << url);
    }

    SquidMD5Final(digest, &M);

    return digest;
}