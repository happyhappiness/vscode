void
statHistIntDumper(StoreEntry * sentry, int idx, double val, double size, int count)
{
    if (count)
        storeAppendPrintf(sentry, "%9d\t%9d\n", (int) val, count);
}