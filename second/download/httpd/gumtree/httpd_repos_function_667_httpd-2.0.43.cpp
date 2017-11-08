static int bio_bucket_in_read(BIO *bio, char *in, int inl)
{
    BIO_bucket_in_t *inbio = BIO_bucket_in_ptr(bio);
    SSLConnRec *sslconn = myConnConfig(inbio->f->c);
    int len = 0;

    /* XXX: flush here only required for SSLv2;
     * OpenSSL calls BIO_flush() at the appropriate times for
     * the other protocols.
     */
    if ((SSL_version(inbio->ssl) == SSL2_VERSION) || sslconn->is_proxy) {
        BIO_bucket_flush(inbio->wbio);
    }

    inbio->rc = APR_SUCCESS;
    
    /* first use data already read from socket if any */
    if ((len = char_buffer_read(&inbio->cbuf, in, inl))) {
        if ((len <= inl) || inbio->mode == AP_MODE_GETLINE) {
            return len;
        }
        inl -= len;
    }

    while (1) {
        const char *buf;
        apr_size_t buf_len = 0;

        if (inbio->bucket) {
            /* all of the data in this bucket has been read,
             * so we can delete it now.
             */
            apr_bucket_delete(inbio->bucket);
            inbio->bucket = NULL;
        }

        if (APR_BRIGADE_EMPTY(inbio->bb)) {
            /* We will always call with READBYTES even if the user wants
             * GETLINE.
             */
            inbio->rc = ap_get_brigade(inbio->f->next, inbio->bb,
                                       AP_MODE_READBYTES, inbio->block, 
                                       inl);

            if ((inbio->rc != APR_SUCCESS) || APR_BRIGADE_EMPTY(inbio->bb))
            {
                break;
            }
        }

        inbio->bucket = APR_BRIGADE_FIRST(inbio->bb);

        inbio->rc = apr_bucket_read(inbio->bucket,
                                    &buf, &buf_len, inbio->block);

        if (inbio->rc != APR_SUCCESS) {
            apr_bucket_delete(inbio->bucket);
            inbio->bucket = NULL;
            return len;
        }

        if (buf_len) {
            /* Protected against len > MAX_INT 
             */
            if ((len + (int)buf_len) >= inl || (int)buf_len < 0) {
                /* we have enough to fill the buffer.
                 * append if we have already written to the buffer.
                 */
                int nibble = inl - len;
                char *value = (char *)buf+nibble;

                int length = buf_len - nibble;
                memcpy(in + len, buf, nibble);

                char_buffer_write(&inbio->cbuf, value, length);
                len += nibble;

                break;
            }
            else {
                /* not enough data,
                 * save what we have and try to read more.
                 */
                memcpy(in + len, buf, buf_len);
                len += buf_len;
            }
        }

        if (inbio->mode == AP_MODE_GETLINE) {
            /* only read from the socket once in getline mode.
             * since callers buffer size is likely much larger than
             * the request headers.  caller can always come back for more
             * if first read didn't get all the headers.
             */
            break;
        }
    }

    return len;
}