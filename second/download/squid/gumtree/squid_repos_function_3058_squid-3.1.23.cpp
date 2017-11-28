const cache_key *
storeKeyPublicByRequestMethod(HttpRequest * request, const HttpRequestMethod& method)
{
    static cache_key digest[SQUID_MD5_DIGEST_LENGTH];
    unsigned char m = (unsigned char) method.id();
    const char *url = urlCanonical(request);
    SquidMD5_CTX M;
    SquidMD5Init(&M);
    SquidMD5Update(&M, &m, sizeof(m));
    SquidMD5Update(&M, (unsigned char *) url, strlen(url));

    if (request->vary_headers)
        SquidMD5Update(&M, (unsigned char *) request->vary_headers, strlen(request->vary_headers));

    SquidMD5Final(digest, &M);

    return digest;
}