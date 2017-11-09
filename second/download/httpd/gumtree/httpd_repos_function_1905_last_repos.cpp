static char *zap_sp_and_dup(apr_pool_t *p, const char *start,
                            const char *end, apr_size_t *len)
{
    while ((start < end) && apr_isspace(*start)) {
        start++;
    }
    while ((end > start) && apr_isspace(*(end - 1))) {
        end--;
    }
    if (len) {
        *len = end - start;
    }
    return apr_pstrmemdup(p, start, end - start);
}