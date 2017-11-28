static void
statHistSBufDumper(StoreEntry * sentry, int idx, double val, double size, int count)
{
    if (count == 0)
        return;
    storeAppendPrintf(sentry, "\t%d-%d\t%d\n", static_cast<int>(val), static_cast<int>(val+size), count);
}