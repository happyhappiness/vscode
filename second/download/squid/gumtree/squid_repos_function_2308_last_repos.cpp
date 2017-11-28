static void
httpHeaderFldsPerHdrDumper(StoreEntry * sentry, int idx, double val, double, int count)
{
    if (count)
        storeAppendPrintf(sentry, "%2d\t %5d\t %5d\t %6.2f\n",
                          idx, (int) val, count,
                          xpercent(count, dump_stat->destroyedCount));
}