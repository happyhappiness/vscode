int WIN32_getrusage(int who, struct rusage *usage)
{
#if HAVE_WIN32_PSAPI

    if (WIN32_OS_version >= _WIN_OS_WINNT) {
        /* On Windows NT and later call PSAPI.DLL for process Memory */
        /* informations -- Guido Serassio                       */
        HANDLE hProcess;
        PROCESS_MEMORY_COUNTERS pmc;
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                               PROCESS_VM_READ,
                               FALSE, GetCurrentProcessId());
        {
            /* Microsoft CRT doesn't have getrusage function,  */
            /* so we get process CPU time information from PSAPI.DLL. */
            FILETIME ftCreate, ftExit, ftKernel, ftUser;

            if (GetProcessTimes(hProcess, &ftCreate, &ftExit, &ftKernel, &ftUser)) {
                int64_t *ptUser = (int64_t *)&ftUser;
                int64_t tUser64 = *ptUser / 10;
                int64_t *ptKernel = (int64_t *)&ftKernel;
                int64_t tKernel64 = *ptKernel / 10;
                usage->ru_utime.tv_sec =(long)(tUser64 / 1000000);
                usage->ru_stime.tv_sec =(long)(tKernel64 / 1000000);
                usage->ru_utime.tv_usec =(long)(tUser64 % 1000000);
                usage->ru_stime.tv_usec =(long)(tKernel64 % 1000000);
            } else {
                CloseHandle( hProcess );
                return -1;
            }
        }

        if (GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc))) {
            usage->ru_maxrss=(DWORD)(pmc.WorkingSetSize / getpagesize());
            usage->ru_majflt=pmc.PageFaultCount;
        } else {
            CloseHandle( hProcess );
            return -1;
        }

        CloseHandle( hProcess );
    }

#endif
    return 0;
}