pid_t
WaitForOnePid(pid_t pid, PidStatus &status, int flags)
{
#if _SQUID_NEXT_
    if (pid < 0)
        return wait3(&status, flags, NULL);
    return wait4(pid, &status, flags, NULL);
#elif _SQUID_WINDOWS_
    return 0; // function not used on Windows
#else
    return waitpid(pid, &status, flags);
#endif
}