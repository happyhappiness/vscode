static int get_now(rotate_config_t *config)
{
    apr_time_t tNow = apr_time_now();
    int utc_offset = config->utc_offset;
    if (config->use_localtime) {
        /* Check for our UTC offset before using it, since it might
         * change if there's a switch between standard and daylight
         * savings time.
         */
        apr_time_exp_t lt;
        apr_time_exp_lt(&lt, tNow);
        utc_offset = lt.tm_gmtoff;
    }
    return (int)apr_time_sec(tNow) + utc_offset;
}