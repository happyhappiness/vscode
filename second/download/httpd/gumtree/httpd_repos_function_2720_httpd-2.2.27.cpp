static apr_uint64_t stat_read_uint64(apr_pool_t *p, char *buf, apr_size_t  len)
{
    buf[len-2] = '\0';
    return apr_atoi64(buf);
}