static const char *stat_read_string(apr_pool_t *p, char *buf, apr_size_t len)
{
    /* remove trailing \r\n and null char */
    return apr_pstrmemdup(p, buf, len-2);
}