inline void
CpuAnd(cpu_set_t *destset, const cpu_set_t *srcset1, const cpu_set_t *srcset2)
{
    for (int i = 0; i < CPU_SETSIZE; ++i) {
        if (CPU_ISSET(i, srcset1) && CPU_ISSET(i, srcset2))
            CPU_SET(i, destset);
        else
            CPU_CLR(i, destset);
    }
}