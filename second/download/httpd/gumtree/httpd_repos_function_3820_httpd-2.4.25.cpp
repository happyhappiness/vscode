static apr_status_t fix_hostname_non_v6(request_rec *r, char *host)
{
    char *dst;

    for (dst = host; *dst; dst++) {
        if (apr_islower(*dst)) {
            /* leave char unchanged */
        }
        else if (*dst == '.') {
            if (*(dst + 1) == '.') {
                return APR_EINVAL;
            }
        }
        else if (apr_isupper(*dst)) {
            *dst = apr_tolower(*dst);
        }
        else if (*dst == '/' || *dst == '\\') {
            return APR_EINVAL;
        }
    }
    /* strip trailing gubbins */
    if (dst > host && dst[-1] == '.') {
        dst[-1] = '\0';
    }
    return APR_SUCCESS;
}