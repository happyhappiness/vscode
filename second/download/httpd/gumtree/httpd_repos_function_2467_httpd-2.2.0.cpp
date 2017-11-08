static void sig_term(int sig)
{
    shutdown_pending = 1;
    is_graceful = 0;
    signal(SIGTERM, SIG_DFL);
}