static int clean_warning_headers(void *data, const char *key, const char *val)
{
    apr_table_t *headers = ((header_dptr*)data)->table;
    apr_pool_t *pool = ((header_dptr*)data)->pool;
    char *warning;
    char *date;
    apr_time_t warn_time;
    const int nmatch = 3;
    ap_regmatch_t pmatch[3];

    if (headers == NULL) {
        ((header_dptr*)data)->table = headers = apr_table_make(pool, 2);
    }
/*
 * Parse this, suckers!
 *
 *    Warning    = "Warning" ":" 1#warning-value
 *
 *    warning-value = warn-code SP warn-agent SP warn-text
 *                                             [SP warn-date]
 *
 *    warn-code  = 3DIGIT
 *    warn-agent = ( host [ ":" port ] ) | pseudonym
 *                    ; the name or pseudonym of the server adding
 *                    ; the Warning header, for use in debugging
 *    warn-text  = quoted-string
 *    warn-date  = <"> HTTP-date <">
 *
 * Buggrit, use a bloomin' regexp!
 * (\d{3}\s+\S+\s+\".*?\"(\s+\"(.*?)\")?)  --> whole in $1, date in $3
 */
    while (!ap_regexec(warn_rx, val, nmatch, pmatch, 0)) {
        warning = apr_pstrndup(pool, val+pmatch[0].rm_so,
                               pmatch[0].rm_eo - pmatch[0].rm_so);
        warn_time = 0;
        if (pmatch[2].rm_eo > pmatch[2].rm_so) {
            /* OK, we have a date here */
            date = apr_pstrndup(pool, val+pmatch[2].rm_so,
                                pmatch[2].rm_eo - pmatch[2].rm_so);
            warn_time = apr_date_parse_http(date);
        }
        if (!warn_time || (warn_time == ((header_dptr*)data)->time)) {
            apr_table_addn(headers, key, warning);
        }
        val += pmatch[0].rm_eo;
    }
    return 1;
}