void
squid_getrusage(struct rusage *r)
{
    memset(r, '\0', sizeof(struct rusage));
#if HAVE_GETRUSAGE && defined(RUSAGE_SELF) && !_SQUID_WINDOWS_
#if _SQUID_SOLARIS_
    /* Solaris 2.5 has getrusage() permission bug -- Arjan de Vet */
    enter_suid();
#endif

    getrusage(RUSAGE_SELF, r);

#if _SQUID_SOLARIS_
    leave_suid();
#endif

#elif _SQUID_WINDOWS_ && HAVE_WIN32_PSAPI
    // Windows has an alternative method if there is no POSIX getrusage defined.
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
                r->ru_utime.tv_sec =(long)(tUser64 / 1000000);
                r->ru_stime.tv_sec =(long)(tKernel64 / 1000000);
                r->ru_utime.tv_usec =(long)(tUser64 % 1000000);
                r->ru_stime.tv_usec =(long)(tKernel64 % 1000000);
            } else {
                CloseHandle( hProcess );
                return;
            }
        }
        if (GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc))) {
            r->ru_maxrss=(DWORD)(pmc.WorkingSetSize / getpagesize());
            r->ru_majflt=pmc.PageFaultCount;
        } else {
            CloseHandle( hProcess );
            return;
        }

        CloseHandle( hProcess );
    }
#endif
}