CpuAffinitySet *
CpuAffinityMap::calculateSet(const int targetProcess) const
{
    Must(theProcesses.size() == theCores.size());
    int core = 0;
    for (size_t i = 0; i < theProcesses.size(); ++i) {
        const int process = theProcesses[i];
        if (process == targetProcess) {
            if (core > 0) {
                debugs(54, DBG_CRITICAL, "WARNING: conflicting "
                       "'cpu_affinity_map' for process number " << process <<
                       ", using the last core seen: " << theCores[i]);
            }
            core = theCores[i];
        }
    }
    CpuAffinitySet *cpuAffinitySet = NULL;
    if (core > 0) {
        cpuAffinitySet = new CpuAffinitySet;
        cpu_set_t cpuSet;
        CPU_ZERO(&cpuSet);
        CPU_SET(core - 1, &cpuSet);
        cpuAffinitySet->set(cpuSet);
    }
    return cpuAffinitySet;
}