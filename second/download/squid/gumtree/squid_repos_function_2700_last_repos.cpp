void
CpuAffinityReconfigure()
{
    if (TheCpuAffinitySet) {
        TheCpuAffinitySet->undo();
        delete TheCpuAffinitySet;
        TheCpuAffinitySet = NULL;
    }
    CpuAffinityInit();
}