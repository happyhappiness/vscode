void
CpuAffinityCheck()
{
    if (Config.cpuAffinityMap) {
        Must(!Config.cpuAffinityMap->processes().empty());
        const int maxProcess =
            *std::max_element(Config.cpuAffinityMap->processes().begin(),
                              Config.cpuAffinityMap->processes().end());

        // in no-deamon mode, there is one process regardless of squid.conf
        const int numberOfProcesses = InDaemonMode() ? NumberOfKids() : 1;

        if (maxProcess > numberOfProcesses) {
            debugs(54, DBG_IMPORTANT, "WARNING: 'cpu_affinity_map' has "
                   "non-existing process number(s)");
        }
    }
}