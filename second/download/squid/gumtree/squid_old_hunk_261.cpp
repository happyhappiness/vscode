{
    statObjectsStart(sentry, statObjectsOpenfdFilter);
}

#endif

#ifdef XMALLOC_STATISTICS
static void
info_get_mallstat(int size, int number, int oldnum, void *data)
{
    StoreEntry *sentry = (StoreEntry *)data;

// format: "%12s %15s %6s %12s\n","Alloc Size","Count","Delta","Alloc/sec"
    if (number > 0)
        storeAppendPrintf(sentry, "%12d %15d %6d %.1f\n", size, number, number - oldnum, xdiv((number - oldnum), xm_deltat));
}

#endif

static void
info_get(StoreEntry * sentry)
{

    struct rusage rusage;
    double cputime;
    double runtime;

    runtime = tvSubDsec(squid_start, current_time);

    if (runtime == 0.0)
        runtime = 1.0;

    storeAppendPrintf(sentry, "Squid Object Cache: Version %s\n",
                      version_string);

#ifdef _SQUID_WIN32_

    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        storeAppendPrintf(sentry,"\nRunning as %s Windows System Service on %s\n",
                          WIN32_Service_name, WIN32_OS_string);
        storeAppendPrintf(sentry,"Service command line is: %s\n", WIN32_Service_Command_Line);
    } else
        storeAppendPrintf(sentry,"Running on %s\n",WIN32_OS_string);
