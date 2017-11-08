static void sig_term(int sig)
{
    shutdown_pending = 1;
    signal(SIGTERM, SIG_DFL);
}