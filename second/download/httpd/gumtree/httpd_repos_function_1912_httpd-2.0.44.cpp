static int getsfunc_BRIGADE(char *buf, int len, void *arg)
{
    apr_bucket_brigade *bb = (apr_bucket_brigade *)arg;
    const char *dst_end = buf + len - 1; /* leave room for terminating null */
    char *dst = buf;
    apr_bucket *e = APR_BRIGADE_FIRST(bb);
    apr_status_t rv;
    int done = 0;

    while ((dst < dst_end) && !done && !APR_BUCKET_IS_EOS(e)) {
        const char *bucket_data;
        apr_size_t bucket_data_len;
        const char *src;
        const char *src_end;
        apr_bucket * next;

        rv = apr_bucket_read(e, &bucket_data, &bucket_data_len,
                             APR_BLOCK_READ);
        if (!APR_STATUS_IS_SUCCESS(rv) || (bucket_data_len == 0)) {
            return 0;
        }
        src = bucket_data;
        src_end = bucket_data + bucket_data_len;
        while ((src < src_end) && (dst < dst_end) && !done) {
            if (*src == '\n') {
                done = 1;
            }
            else if (*src != '\r') {
                *dst++ = *src;
            }
            src++;
        }

        if (src < src_end) {
            apr_bucket_split(e, src - bucket_data);
        }
        next = APR_BUCKET_NEXT(e);
        APR_BUCKET_REMOVE(e);
        apr_bucket_destroy(e);
        e = next;
    }
    *dst = 0;
    return 1;
}