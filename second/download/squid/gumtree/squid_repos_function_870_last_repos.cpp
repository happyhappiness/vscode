static void
parse_CpuAffinityMap(CpuAffinityMap **const cpuAffinityMap)
{
#if !HAVE_CPU_AFFINITY
    debugs(3, DBG_CRITICAL, "FATAL: Squid built with no CPU affinity " <<
           "support, do not set 'cpu_affinity_map'");
    self_destruct();

#else /* HAVE_CPU_AFFINITY */
    if (!*cpuAffinityMap)
        *cpuAffinityMap = new CpuAffinityMap;

    const char *const pToken = ConfigParser::NextToken();
    const char *const cToken = ConfigParser::NextToken();
    std::vector<int> processes, cores;
    if (!parseNamedIntList(pToken, "process_numbers", processes)) {
        debugs(3, DBG_CRITICAL, "FATAL: bad 'process_numbers' parameter " <<
               "in 'cpu_affinity_map'");
        self_destruct();
    } else if (!parseNamedIntList(cToken, "cores", cores)) {
        debugs(3, DBG_CRITICAL, "FATAL: bad 'cores' parameter in " <<
               "'cpu_affinity_map'");
        self_destruct();
    } else if (!(*cpuAffinityMap)->add(processes, cores)) {
        debugs(3, DBG_CRITICAL, "FATAL: bad 'cpu_affinity_map'; " <<
               "process_numbers and cores lists differ in length or " <<
               "contain numbers <= 0");
        self_destruct();
    }
#endif
}