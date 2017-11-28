double

rusage_cputime(struct rusage *r)
{
    return (double) r->ru_stime.tv_sec +
           (double) r->ru_utime.tv_sec +
           (double) r->ru_stime.tv_usec / 1000000.0 +
           (double) r->ru_utime.tv_usec / 1000000.0;
}