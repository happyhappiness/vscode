static void
free_CpuAffinityMap(CpuAffinityMap **const cpuAffinityMap)
{
    delete *cpuAffinityMap;
    *cpuAffinityMap = NULL;
}