void
StoreController::create()
{
    swapDir->create();

#ifndef _SQUID_MSWIN_

    pid_t pid;

    do {
        int status;
#ifdef _SQUID_NEXT_

        pid = wait3(&status, WNOHANG, NULL);
#else

        pid = waitpid(-1, &status, 0);
#endif

    } while (pid > 0 || (pid < 0 && errno == EINTR));

#endif
}