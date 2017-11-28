void
CpuAffinitySet::undo()
{
    if (applied()) {
        if (sched_setaffinity(0, sizeof(theOrigCpuSet), &theOrigCpuSet)) {
            int xerrno = errno;
            debugs(54, DBG_IMPORTANT, "ERROR: failed to restore original CPU "
                   "affinity for process PID " << getpid() << ": " <<
                   xstrerr(xerrno));
        }
        CPU_ZERO(&theOrigCpuSet);
    }
}