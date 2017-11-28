void
CpuAffinitySet::apply()
{
    Must(CPU_COUNT(&theCpuSet) > 0); // CPU affinity mask set
    Must(!applied());

    bool success = false;
    if (sched_getaffinity(0, sizeof(theOrigCpuSet), &theOrigCpuSet)) {
        debugs(54, DBG_IMPORTANT, "ERROR: failed to get CPU affinity for "
               "process PID " << getpid() << ", ignoring CPU affinity for "
               "this process: " << xstrerror());
    } else {
        cpu_set_t cpuSet;
        memcpy(&cpuSet, &theCpuSet, sizeof(cpuSet));
        (void) CPU_AND(&cpuSet, &cpuSet, &theOrigCpuSet);
        if (CPU_COUNT(&cpuSet) <= 0) {
            debugs(54, DBG_IMPORTANT, "ERROR: invalid CPU affinity for process "
                   "PID " << getpid() << ", may be caused by an invalid core in "
                   "'cpu_affinity_map' or by external affinity restrictions");
        } else if (sched_setaffinity(0, sizeof(cpuSet), &cpuSet)) {
            debugs(54, DBG_IMPORTANT, "ERROR: failed to set CPU affinity for "
                   "process PID " << getpid() << ": " << xstrerror());
        } else
            success = true;
    }
    if (!success)
        CPU_ZERO(&theOrigCpuSet);
}