void
Store::Controller::create()
{
    swapDir->create();

#if !_SQUID_WINDOWS_
    pid_t pid;
    do {
        PidStatus status;
        pid = WaitForAnyPid(status, WNOHANG);
    } while (pid > 0 || (pid < 0 && errno == EINTR));
#endif
}