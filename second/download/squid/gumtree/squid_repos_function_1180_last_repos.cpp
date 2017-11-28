void
SignalEngine::handleStoppedChild()
{
    // no AvoidSignalAction() call: This code can run at any time because it
    // does not depend on Squid state. It does not need debugging because it
    // handles an "internal" signal, not an external/admin command.
    do_handle_stopped_child = 0;
#if !_SQUID_WINDOWS_
    PidStatus status;
    pid_t pid;

    do {
        pid = WaitForAnyPid(status, WNOHANG);

#if HAVE_SIGACTION

    } while (pid > 0);

#else

    }