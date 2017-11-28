static inline void
xprof_chk_overhead(int samples)
{
    while (samples--) {
        PROF_start(PROF_OVERHEAD);
        PROF_stop(PROF_OVERHEAD);
    }
}