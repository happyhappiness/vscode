static void check_infinite_requests(void)
{
    if (ap_max_requests_per_child) {
        signal_threads(ST_GRACEFUL);
    }
    else {
        requests_this_child = INT_MAX;      /* keep going */
    }
}