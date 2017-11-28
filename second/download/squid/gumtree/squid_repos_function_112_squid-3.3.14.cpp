void
print_stats()
{
#ifdef WITH_LIB
    memReport(stdout);
#endif
    getrusage(RUSAGE_SELF, &myusage);
    printf("m/c/f/r=%d/%d/%d/%d\n", mstat.mallocs, mstat.callocs,
           mstat.frees, mstat.reallocs);
#if 0
    printf("types                 : %d\n", size2id_len);
#endif
    printf("user time used        : %d.%d\n", (int) myusage.ru_utime.tv_sec,
           (int) myusage.ru_utime.tv_usec);
    printf("system time used      : %d.%d\n", (int) myusage.ru_stime.tv_sec,
           (int) myusage.ru_stime.tv_usec);
    printf("max resident set size : %d\n", (int) myusage.ru_maxrss);
    printf("page faults           : %d\n", (int) myusage.ru_majflt);
}