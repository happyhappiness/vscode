void h2_filter_cin_timeout_set(h2_filter_cin *cin, apr_interval_time_t timeout)
{
    cin->timeout = timeout;
}