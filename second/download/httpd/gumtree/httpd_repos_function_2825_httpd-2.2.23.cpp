static const char *odbc_escape(apr_pool_t *pool, const char *s,
                               apr_dbd_t *handle)
{   
    char *newstr, *src, *dst, *sq;
    int qcount;

    /* return the original if there are no single-quotes */
    if (!(sq = strchr(s, '\''))) 
        return (char *)s;
    /* count the single-quotes and allocate a new buffer */
    for (qcount = 1; (sq = strchr(sq + 1, '\'')); )
        qcount++;
    newstr = apr_palloc(pool, strlen(s) + qcount + 1);

    /* move chars, doubling all single-quotes */
    src = (char *)s;
    for (dst = newstr; *src; src++) {
        if ((*dst++ = *src) == '\'')  
            *dst++ = '\'';
    }
    *dst = 0;
    return newstr;
}