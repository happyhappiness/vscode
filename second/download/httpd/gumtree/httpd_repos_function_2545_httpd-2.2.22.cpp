static void check_infinite_requests(void)
{
    if (ap_max_requests_per_child) {
        signal_threads(ST_GRACEFUL);
    }
    else {
        /* wow! if you're executing this code, you may have set a record.
         * either this child process has served over 2 billion requests, or
         * you're running a threaded 2.0 on a 16 bit machine.
         *
         * I'll buy pizza and beers at Apachecon for the first person to do
         * the former without cheating (dorking with INT_MAX, or running with
         * uncommitted performance patches, for example).
         *
         * for the latter case, you probably deserve a beer too.   Greg Ames
         */

        requests_this_child = INT_MAX;  /* keep going */
    }
}