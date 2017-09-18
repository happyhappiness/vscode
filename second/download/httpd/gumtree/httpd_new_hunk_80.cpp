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
    }
