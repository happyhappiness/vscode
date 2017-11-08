static void get_system_time(apr_uint64_t *uuid_time)
{
    /* ### fix this call to be more portable? */
    *uuid_time = apr_time_now();

    /* Offset between UUID formatted times and Unix formatted times.
       UUID UTC base time is October 15, 1582.
       Unix base time is January 1, 1970.      */
    *uuid_time = (*uuid_time * 10) + APR_TIME_C(0x01B21DD213814000);
}