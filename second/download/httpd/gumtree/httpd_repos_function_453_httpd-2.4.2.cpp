static apr_status_t ap_buffered_log_writer(request_rec *r,
                                           void *handle,
                                           const char **strs,
                                           int *strl,
                                           int nelts,
                                           apr_size_t len)

{
    char *str;
    char *s;
    int i;
    apr_status_t rv;
    buffered_log *buf = (buffered_log*)handle;

    if ((rv = APR_ANYLOCK_LOCK(&buf->mutex)) != APR_SUCCESS) {
        return rv;
    }

    if (len + buf->outcnt > LOG_BUFSIZE) {
        flush_log(buf);
    }
    if (len >= LOG_BUFSIZE) {
        apr_size_t w;

        str = apr_palloc(r->pool, len + 1);
        for (i = 0, s = str; i < nelts; ++i) {
            memcpy(s, strs[i], strl[i]);
            s += strl[i];
        }
        w = len;
        rv = apr_file_write(buf->handle, str, &w);

    }
    else {
        for (i = 0, s = &buf->outbuf[buf->outcnt]; i < nelts; ++i) {
            memcpy(s, strs[i], strl[i]);
            s += strl[i];
        }
        buf->outcnt += len;
        rv = APR_SUCCESS;
    }

    APR_ANYLOCK_UNLOCK(&buf->mutex);
    return rv;
}