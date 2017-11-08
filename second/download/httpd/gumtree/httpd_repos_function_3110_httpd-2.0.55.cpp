apr_status_t apr_gethostname(char *buf, apr_int32_t len, apr_pool_t *cont)
{
    if (gethostname(buf, len) == -1) {
        buf[0] = '\0';
        return errno;
    }
    else if (!memchr(buf, '\0', len)) { /* buffer too small */
        /* note... most platforms just truncate in this condition
         *         linux+glibc return an error
         */
        buf[0] = '\0';
        return APR_ENAMETOOLONG;
    }
    return APR_SUCCESS;
}