unsigned int
url_checksum(const char *url)
{
    unsigned int ck;
    SquidMD5_CTX M;
    static unsigned char digest[16];
    SquidMD5Init(&M);
    SquidMD5Update(&M, (unsigned char *) url, strlen(url));
    SquidMD5Final(digest, &M);
    memcpy(&ck, digest, sizeof(ck));
    return ck;
}