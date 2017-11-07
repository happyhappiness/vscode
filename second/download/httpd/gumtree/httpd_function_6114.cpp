static apr_status_t strict_hostname_check(request_rec *r, char *host)
{
    char *ch;
    int is_dotted_decimal = 1, leading_zeroes = 0, dots = 0;

    for (ch = host; *ch; ch++) {
        if (!apr_isascii(*ch)) {
            goto bad;
        }
        else if (apr_isalpha(*ch) || *ch == '-') {
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
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02415)
                  "[strict] Invalid host name '%s'%s%.6s",
                  host, *ch ? ", problem near: " : "", ch);
    return APR_EINVAL;
}