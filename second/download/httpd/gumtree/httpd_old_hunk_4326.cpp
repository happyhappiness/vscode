        lastmod = date;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0,
                r, APLOGNO(00771) "cache: Last modified is in the future, "
                "replacing with now");
    }

    /* if no expiry date then
     *   if Cache-Control: max-age
     *      expiry date = date + max-age
     *   else if lastmod
     *      expiry date = date + min((date - lastmod) * factor, maxexpire)
     *   else
     *      expire date = date + defaultexpire
     */
    if (exp == APR_DATE_BAD) {

        if (control.max_age) {
            apr_int64_t x;

            errno = 0;
            x = control.max_age_value;
            if (errno) {
                x = dconf->defex;
            }
            else {
                x = x * MSEC_ONE_SEC;
            }
            if (x < dconf->minex) {
                x = dconf->minex;
            }
            if (x > dconf->maxex) {
                x = dconf->maxex;
            }
            exp = date + x;
        }
        else if ((lastmod != APR_DATE_BAD) && (lastmod < date)) {
            /* if lastmod == date then you get 0*conf->factor which results in
             * an expiration time of now. This causes some problems with
             * freshness calculations, so we choose the else path...
             */
            apr_time_t x = (apr_time_t) ((date - lastmod) * dconf->factor);

