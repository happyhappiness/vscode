static apr_status_t brigade_peek(apr_bucket_brigade *bbIn,
                                 char *buff, apr_size_t bufflen)
{
    apr_bucket *b;
    apr_size_t readbytes = 0;

    if (bufflen--)
        /* compensate for NULL */
        *buff = '\0';
    else
        return APR_EGENERAL;

    if (APR_BRIGADE_EMPTY(bbIn))
        return APR_EGENERAL;

    b = APR_BRIGADE_FIRST(bbIn);

    while ((b != APR_BRIGADE_SENTINEL(bbIn)) && (readbytes < bufflen)) {
        const char *pos;
        const char *str;
        apr_size_t len;
        apr_status_t rv;

        if ((rv = apr_bucket_read(b, &str, &len, APR_NONBLOCK_READ))
                != APR_SUCCESS)
            return rv;

        if ((pos = memchr(str, APR_ASCII_LF, len)) != NULL)
            len = pos - str;
        if (len > bufflen - readbytes)
            len = bufflen - readbytes;
        memcpy (buff + readbytes, str, len);
        readbytes += len;
        buff[readbytes] = '\0';

        b = APR_BUCKET_NEXT(b);
    }
    return APR_SUCCESS;
}