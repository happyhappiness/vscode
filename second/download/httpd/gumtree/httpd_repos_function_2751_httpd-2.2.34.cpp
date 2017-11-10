static apr_time_t stat_read_rtime(apr_pool_t *p, char *buf, apr_size_t  len)
{
    char *tok;
    char *secs;
    char *usecs;
    const char *sep = ":.";

    buf[len-2] = '\0';

    secs = apr_strtok(buf, sep, &tok);
    usecs = apr_strtok(NULL, sep, &tok);
    if (secs && usecs) {
        return apr_time_make(atoi(secs), atoi(usecs));
    }
    else {
        return apr_time_make(0, 0);
    }
}