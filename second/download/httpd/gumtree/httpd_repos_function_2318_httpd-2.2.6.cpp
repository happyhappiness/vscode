static void set_signals(void)
{
    apr_signal(SIGTERM, sig_term);
    apr_signal(SIGABRT, sig_term);
}