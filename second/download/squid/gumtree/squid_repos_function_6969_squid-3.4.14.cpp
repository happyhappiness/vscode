inline int
CpuCount(const cpu_set_t *set)
{
    int count = 0;
    for (int i = 0; i < CPU_SETSIZE; ++i) {
        if (CPU_ISSET(i, set))
            ++count;
    }
    return count;
}