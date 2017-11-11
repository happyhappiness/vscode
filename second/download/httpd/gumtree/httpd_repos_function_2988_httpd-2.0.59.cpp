static char *conv_os_thread_t(apr_os_thread_t *tid, char *buf_end, int *len)
{
    union {
        apr_os_thread_t tid;
        apr_uint64_t alignme;
    } u;
    int is_negative;

    u.tid = *tid;
    switch(sizeof(u.tid)) {
    case sizeof(apr_int32_t):
        return conv_10(*(apr_uint32_t *)&u.tid, TRUE, &is_negative, buf_end, len);
    case sizeof(apr_int64_t):
        return conv_10_quad(*(apr_uint64_t *)&u.tid, TRUE, &is_negative, buf_end, len);
    default:
        /* not implemented; stick 0 in the buffer */
        return conv_10(0, TRUE, &is_negative, buf_end, len);
    }
}