static apr_uint32_t stat_read_uint32(apr_pool_t *p, char *buf, apr_size_t  len)
{
    buf[len-2] = '\0';
    return atoi(buf);
}