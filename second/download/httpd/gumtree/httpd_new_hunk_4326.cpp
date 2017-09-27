        lastmod = date;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0,
                r, APLOGNO(00771) "cache: Last modified is in the future, "
                "replacing with now");
    }


    /* CC has priority over Expires.  */
    if (control.s_maxage || control.max_age) {
        apr_int64_t x;

        x = control.s_maxage ? control.s_maxage_value : control.max_age_value;
        x = x * MSEC_ONE_SEC;

        if (x < dconf->minex) {
            x = dconf->minex;
        }
        if (x > dconf->maxex) {
            x = dconf->maxex;
        }
        exp = date + x;
    }

    /* if no expiry date then
     *   if Cache-Control: s-maxage
     *      expiry date = date + smaxage
     *   if Cache-Control: max-age
     *      expiry date = date + max-age
     *   else if lastmod
     *      expiry date = date + min((date - lastmod) * factor, maxexpire)
     *   else
     *      expire date = date + defaultexpire
     */

    if (exp == APR_DATE_BAD) {
        if ((lastmod != APR_DATE_BAD) && (lastmod < date)) {
            /* if lastmod == date then you get 0*conf->factor which results in
             * an expiration time of now. This causes some problems with
             * freshness calculations, so we choose the else path...
             */
            apr_time_t x = (apr_time_t) ((date - lastmod) * dconf->factor);

