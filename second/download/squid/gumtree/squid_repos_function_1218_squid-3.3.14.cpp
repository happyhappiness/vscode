void
CpuAffinitySet::set(const cpu_set_t &aCpuSet)
{
    memcpy(&theCpuSet, &aCpuSet, sizeof(theCpuSet));
}