static void sig_hup(int sig)
{
    shutdown_pending = 1;
    is_graceful = 1;
}