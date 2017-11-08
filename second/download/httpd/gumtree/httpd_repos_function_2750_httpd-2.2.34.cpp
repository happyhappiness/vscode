static apr_time_t stat_read_time(apr_pool_t *p, char *buf, apr_size_t  len)
{
    buf[len-2] = '\0';
    return apr_time_from_sec(atoi(buf));
}