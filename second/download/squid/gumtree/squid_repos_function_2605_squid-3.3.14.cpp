void
PrintRusage(void)
{

    struct rusage rusage;
    squid_getrusage(&rusage);
    fprintf(debug_log, "CPU Usage: %.3f seconds = %.3f user + %.3f sys\n",
            rusage_cputime(&rusage),
            rusage.ru_utime.tv_sec + ((double) rusage.ru_utime.tv_usec / 1000000.0),
            rusage.ru_stime.tv_sec + ((double) rusage.ru_stime.tv_usec / 1000000.0));
    fprintf(debug_log, "Maximum Resident Size: %d KB\n",
            rusage_maxrss(&rusage));
    fprintf(debug_log, "Page faults with physical i/o: %d\n",
            rusage_pagefaults(&rusage));
}