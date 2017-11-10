static void get_current_time(apr_uint64_t *timestamp)
{
    /* ### this needs to be made thread-safe! */

    apr_uint64_t time_now;
    static apr_uint64_t time_last = 0;
    static apr_uint64_t fudge = 0;

    get_system_time(&time_now);
        
    /* if clock reading changed since last UUID generated... */
    if (time_last != time_now) {
        /* The clock reading has changed since the last UUID was generated.
           Reset the fudge factor. if we are generating them too fast, then
           the fudge may need to be reset to something greater than zero. */
        if (time_last + fudge > time_now)
            fudge = time_last + fudge - time_now + 1;
        else
            fudge = 0;
        time_last = time_now;
    }
    else {
        /* We generated two really fast. Bump the fudge factor. */
        ++fudge;
    }

    *timestamp = time_now + fudge;
}