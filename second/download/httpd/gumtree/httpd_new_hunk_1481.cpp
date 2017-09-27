

/*****************************************************************************
 * run-time vhost matching functions
 */

static apr_status_t fix_hostname_v6_literal(request_rec *r, char *host)
{
    char *dst;
    int double_colon = 0;

    for (dst = host; *dst; dst++) {
        if (apr_isxdigit(*dst)) {
            if (apr_isupper(*dst)) {
                *dst = apr_tolower(*dst);
            }
        }
        else if (*dst == ':') {
            if (*(dst + 1) == ':') {
                if (double_colon)
                    return APR_EINVAL;
                double_colon = 1;
            }
            else if (*(dst + 1) == '.') {
                return APR_EINVAL;
            }
        }
        else if (*dst == '.') {
            /* For IPv4-mapped IPv6 addresses like ::FFFF:129.144.52.38 */
            if (*(dst + 1) == ':' || *(dst + 1) == '.')
                return APR_EINVAL;
        }
        else {
            return APR_EINVAL;
        }
    }
    return APR_SUCCESS;
}

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

/*
 * If strict mode ever becomes the default, this should be folded into
 * fix_hostname_non_v6()
 */
static apr_status_t strict_hostname_check(request_rec *r, char *host)
{
    char *ch;
    int is_dotted_decimal = 1, leading_zeroes = 0, dots = 0;

    for (ch = host; *ch; ch++) {
        if (apr_isalpha(*ch) || *ch == '-') {
            is_dotted_decimal = 0;
        }
        else if (ch[0] == '.') {
            dots++;
            if (ch[1] == '0' && apr_isdigit(ch[2]))
                leading_zeroes = 1;
        }
        else if (!apr_isdigit(*ch)) {
           /* also takes care of multiple Host headers by denying commas */
            goto bad;
        }
    }
    if (is_dotted_decimal) {
        if (host[0] == '.' || (host[0] == '0' && apr_isdigit(host[1])))
            leading_zeroes = 1;
        if (leading_zeroes || dots != 3) {
            /* RFC 3986 7.4 */
            goto bad;
        }
    }
    else {
        /* The top-level domain must start with a letter (RFC 1123 2.1) */
        while (ch > host && *ch != '.')
            ch--;
        if (ch[0] == '.' && ch[1] != '\0' && !apr_isalpha(ch[1]))
            goto bad;
    }
    return APR_SUCCESS;

bad:
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[strict] Invalid host name '%s'%s%.6s",
                  host, *ch ? ", problem near: " : "", ch);
    return APR_EINVAL;
}

/* Lowercase and remove any trailing dot and/or :port from the hostname,
 * and check that it is sane.
 *
 * In most configurations the exact syntax of the hostname isn't
 * important so strict sanity checking isn't necessary. However, in
 * mass hosting setups (using mod_vhost_alias or mod_rewrite) where
