     *
     * In addition, we make HTTP/1.1 age calculations and write them away
     * too.
     */

    /* Read the date. Generate one if one is not supplied */
    dates = ap_table_get(r->headers_out, "Date");
    if (dates != NULL)
        info->date = apr_date_parse_http(dates);
    else
        info->date = APR_DATE_BAD;

    now = apr_time_now();
    if (info->date == APR_DATE_BAD) {  /* No, or bad date */
        char *dates;
        /* no date header! */
        /* add one; N.B. use the time _now_ rather than when we were checking
         * the cache 
         */
        date = now;
        dates = apr_pcalloc(r->pool, MAX_STRING_LEN);
        apr_rfc822_date(dates, now);
        ap_table_set(r->headers_out, "Date", dates);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache: Added date header");
        info->date = date;
    }
    else {
        date = info->date;
