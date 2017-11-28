void
DumpMallocStatistics(StoreEntry* sentry)
{
#if XMALLOC_STATISTICS
    xm_deltat = current_dtime - xm_time;
    xm_time = current_dtime;
    storeAppendPrintf(sentry, "\nMemory allocation statistics\n");
    storeAppendPrintf(sentry, "%12s %15s %6s %12s\n","Alloc Size","Count","Delta","Alloc/sec");
    malloc_statistics(info_get_mallstat, sentry);
#endif
}