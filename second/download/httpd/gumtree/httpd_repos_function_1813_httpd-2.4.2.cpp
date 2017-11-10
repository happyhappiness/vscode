static apr_status_t ftp_string_read(conn_rec *c, apr_bucket_brigade *bb,
        char *buff, apr_size_t bufflen, int *eos)
{
    apr_bucket *e;
    apr_status_t rv;
    char *pos = buff;
    char *response;
    int found = 0;
    apr_size_t len;

    /* start with an empty string */
    buff[0] = 0;
    *eos = 0;

    /* loop through each brigade */
    while (!found) {
        /* get brigade from network one line at a time */
        if (APR_SUCCESS != (rv = ap_get_brigade(c->input_filters, bb,
                                                AP_MODE_GETLINE,
                                                APR_BLOCK_READ,
                                                0))) {
            return rv;
        }
        /* loop through each bucket */
        while (!found) {
            if (*eos || APR_BRIGADE_EMPTY(bb)) {
                /* The connection aborted or timed out */
                return APR_ECONNABORTED;
            }
            e = APR_BRIGADE_FIRST(bb);
            if (APR_BUCKET_IS_EOS(e)) {
                *eos = 1;
            }
            else {
                if (APR_SUCCESS != (rv = apr_bucket_read(e,
                                                         (const char **)&response,
                                                         &len,
                                                         APR_BLOCK_READ))) {
                    return rv;
                }
                /*
                 * is string LF terminated?
                 * XXX: This check can be made more efficient by simply checking
                 * if the last character in the 'response' buffer is an ASCII_LF.
                 * See ap_rgetline() for an example.
                 */
                if (memchr(response, APR_ASCII_LF, len)) {
                    found = 1;
                }
                /* concat strings until buff is full - then throw the data away */
                if (len > ((bufflen-1)-(pos-buff))) {
                    len = (bufflen-1)-(pos-buff);
                }
                if (len > 0) {
                    memcpy(pos, response, len);
                    pos += len;
                }
            }
            APR_BUCKET_REMOVE(e);
            apr_bucket_destroy(e);
        }
        *pos = '\0';
    }

    return APR_SUCCESS;
}