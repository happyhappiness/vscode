static char *format_integer(apr_pool_t *p, int i)
{
    return apr_itoa(p, i);
}