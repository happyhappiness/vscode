static apr_status_t ssl_io_input_getline(bio_filter_in_ctx_t *inctx,
                                         char *buf,
                                         apr_size_t *len)
{
    const char *pos = NULL;
    apr_status_t status;
    apr_size_t tmplen = *len, buflen = *len, offset = 0;

    *len = 0;

    /*
     * in most cases we get all the headers on the first SSL_read.
     * however, in certain cases SSL_read will only get a partial
     * chunk of the headers, so we try to read until LF is seen.
     */

    while (tmplen > 0) {
        status = ssl_io_input_read(inctx, buf + offset, &tmplen);

        if (status != APR_SUCCESS) {
            return status;
        }

        *len += tmplen;

        if ((pos = memchr(buf, APR_ASCII_LF, *len))) {
            break;
        }

        offset += tmplen;
        tmplen = buflen - offset;
    }

    if (pos) {
        char *value;
        int length;
        apr_size_t bytes = pos - buf;

        bytes += 1;
        value = buf + bytes;
        length = *len - bytes;

        char_buffer_write(&inctx->cbuf, value, length);

        *len = bytes;
    }

    return APR_SUCCESS;
}