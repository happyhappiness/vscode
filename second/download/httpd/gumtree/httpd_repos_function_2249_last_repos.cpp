const char *h2_util_base64url_encode(const char *data, 
                                     apr_size_t len, apr_pool_t *pool)
{
    apr_size_t mlen = ((len+2)/3)*3;
    apr_size_t slen = (mlen/3)*4;
    apr_size_t i;
    const unsigned char *udata = (const unsigned char*)data;
    char *enc, *p = apr_pcalloc(pool, slen+1); /* 0 terminated */
    
    enc = p;
    for (i = 0; i < mlen; i+= 3) {
        *p++ = BASE64URL_CHARS[ (udata[i] >> 2) & 0x3fu ];
        *p++ = BASE64URL_CHARS[ ((udata[i] << 4) + 
                                 ((i+1 < len)? (udata[i+1] >> 4) : 0)) & 0x3fu ];
        *p++ = BASE64URL_CHARS[ ((udata[i+1] << 2) + 
                                 ((i+2 < len)? (udata[i+2] >> 6) : 0)) & 0x3fu ];
        if (i+2 < len) {
            *p++ = BASE64URL_CHARS[ udata[i+2] & 0x3fu ];
        }
    }
    
    return enc;
}