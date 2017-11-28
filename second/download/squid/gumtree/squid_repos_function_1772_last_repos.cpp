inline pid_t WaitForAnyPid(PidStatus &status, int flags)
{
    return WaitForOnePid(-1, status, flags);
}