static void sig_restart(int sig)
{
    if (sig == SIGUSR1) {
        is_graceful = 1;
    }

    restart_pending = 1;
}