static bool
ProcessIsRunning(const pid_t pid)
{
    const auto result = kill(pid, 0);
    const auto savedErrno = errno;
    if (result != 0)
        debugs(50, 3, "kill(" << pid << ", 0) failed: " << xstrerr(savedErrno));
    // if we do not have permissions to signal the process, then it is running
    return (result == 0 || savedErrno == EPERM);
}