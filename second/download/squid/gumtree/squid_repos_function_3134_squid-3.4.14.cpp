const cache_key *
storeKeyPublicByRequestMethod(HttpRequest * request, const HttpRequestMethod& method)
{
    static cache_key digest[SQUID_MD5_DIGEST_LENGTH];
    unsigned char m = (unsigned char) method.id();
    const char *url = request->storeId(); /* storeId returns the right storeID\canonical URL for the md5 calc */
    SquidMD5_CTX M;
    SquidMD5Init(&M);
    SquidMD5Update(&M, &m, sizeof(m));
    SquidMD5Update(&M, (unsigned char *) url, strlen(url));

    if (request->vary_headers) {
        SquidMD5Update(&M, (unsigned char *) request->vary_headers, strlen(request->vary_headers));
        debugs(20, 3, "updating public key by vary headers: " << request->vary_headers << " for: " << url);
    }

    SquidMD5Final(digest, &M);

    return digest;
}