char *md5sum(const char *s)
{
    static unsigned char digest[16];
    SquidMD5_CTX ctx;
    int idx;
    static char sum[33];

    memset(digest,0,16);

    SquidMD5Init(&ctx);
    SquidMD5Update(&ctx,(const unsigned char *)s,strlen(s));
    SquidMD5Final(digest,&ctx);

    for (idx=0; idx<16; idx++)
        sprintf(&sum[idx*2],"%02x",digest[idx]);

    sum[32]='\0';

    /* Don't leave anything around in vm they could use. */
    memset(digest, 0, sizeof digest);

    return sum;
}