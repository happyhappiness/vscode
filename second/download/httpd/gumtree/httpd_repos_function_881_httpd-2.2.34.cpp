static char *ssl_var_lookup_ssl_cert_remain(apr_pool_t *p, ASN1_UTCTIME *tm)
{
    apr_time_t then, now = apr_time_now();
    apr_time_exp_t exp = {0};
    long diff;

    /* Fail if the time isn't a valid ASN.1 UTCTIME; RFC3280 mandates
     * that the seconds digits are present even though ASN.1
     * doesn't. */
    if (tm->length < 11 || !ASN1_UTCTIME_check(tm)) {
        return apr_pstrdup(p, "0");
    }

    exp.tm_year = DIGIT2NUM(tm->data);
    exp.tm_mon = DIGIT2NUM(tm->data + 2) - 1;
    exp.tm_mday = DIGIT2NUM(tm->data + 4) + 1;
    exp.tm_hour = DIGIT2NUM(tm->data + 6);
    exp.tm_min = DIGIT2NUM(tm->data + 8);
    exp.tm_sec = DIGIT2NUM(tm->data + 10);

    if (exp.tm_year <= 50) exp.tm_year += 100;

    if (apr_time_exp_gmt_get(&then, &exp) != APR_SUCCESS) {
        return apr_pstrdup(p, "0");
    }

    diff = (long)((apr_time_sec(then) - apr_time_sec(now)) / (60*60*24));

    return diff > 0 ? apr_ltoa(p, diff) : apr_pstrdup(p, "0");
}