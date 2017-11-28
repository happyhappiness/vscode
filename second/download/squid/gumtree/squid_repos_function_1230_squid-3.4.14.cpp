bool
CpuAffinitySet::applied()
{
    // NOTE: cannot be const.
    // According to CPU_SET(3) and, apparently, on some systems (e.g.,
    // OpenSuSE 10.3) CPU_COUNT macro expects a non-const argument.
    return (CPU_COUNT(&theOrigCpuSet) > 0);
}