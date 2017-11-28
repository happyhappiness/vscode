void
statHistIntDumper(StoreEntry * sentry, int, double val, double, int count)
{
    if (count)
        storeAppendPrintf(sentry, "%9d\t%9d\n", (int) val, count);
}