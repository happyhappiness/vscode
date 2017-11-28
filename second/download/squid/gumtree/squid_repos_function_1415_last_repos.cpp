bool
CpuAffinityMap::add(const std::vector<int> &aProcesses, const std::vector<int> &aCores)
{
    if (aProcesses.size() != aCores.size())
        return false;

    for (size_t i = 0; i < aProcesses.size(); ++i) {
        const int process = aProcesses[i];
        const int core = aCores[i];
        if (process <= 0 || core <= 0)
            return false;
        theProcesses.push_back(process);
        theCores.push_back(core);
    }

    return true;
}