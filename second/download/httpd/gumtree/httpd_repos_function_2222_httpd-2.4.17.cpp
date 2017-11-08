apr_size_t h2_util_base64url_decode(const char **decoded, const char *encoded, 
                                    apr_pool_t *pool)
{
    const unsigned char *e = (const unsigned char *)encoded;
    const unsigned char *p = e;
    unsigned char *d;
    int n;
    apr_size_t len, mlen, remain, i;
    
    while (*p && BASE64URL_TABLE[ *p ] == -1) {
        ++p;
    }
    len = p - e;
    mlen = (len/4)*4;
    *decoded = apr_pcalloc(pool, len+1);
    
    i = 0;
    d = (unsigned char*)*decoded;
    for (; i < mlen; i += 4) {
        n = ((BASE64URL_TABLE[ e[i+0] ] << 18) +
             (BASE64URL_TABLE[ e[i+1] ] << 12) +
             (BASE64URL_TABLE[ e[i+2] ] << 6) +
             BASE64URL_TABLE[ e[i+3] ]);
        *d++ = n >> 16;
        *d++ = n >> 8 & 0xffu;
        *d++ = n & 0xffu;
    }
    remain = len - mlen;
    switch (remain) {
        case 2:
            n = ((BASE64URL_TABLE[ e[mlen+0] ] << 18) +
                 (BASE64URL_TABLE[ e[mlen+1] ] << 12));
            *d++ = n >> 16;
            break;
        case 3:
            n = ((BASE64URL_TABLE[ e[mlen+0] ] << 18) +
                 (BASE64URL_TABLE[ e[mlen+1] ] << 12) +
                 (BASE64URL_TABLE[ e[mlen+2] ] << 6));
            *d++ = n >> 16;
            *d++ = n >> 8 & 0xffu;
            break;
        default: /* do nothing */
            break;
    }
    return len;
}