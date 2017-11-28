static void
info_get_mallstat(int size, int number, int oldnum, void *data)
{
    StoreEntry *sentry = (StoreEntry *)data;

// format: "%12s %15s %6s %12s\n","Alloc Size","Count","Delta","Alloc/sec"
    if (number > 0)
        storeAppendPrintf(sentry, "%12d %15d %6d %.1f\n", size, number, number - oldnum, xdiv((number - oldnum), xm_deltat));
}