uint32_t
Ping::Init()
{
    if (Ping::Config.enable) {
#if HAVE_SIGACTION
        struct sigaction sa, osa;
        if (sigaction(SIGINT, NULL, &osa) == 0 && osa.sa_handler == SIG_DFL) {
            sa.sa_handler = catchSignal;
            sa.sa_flags = 0;
            sigemptyset(&sa.sa_mask);
            (void) sigaction(SIGINT, &sa, NULL);
        }
#else
        void (*osig) (int);
        if ((osig = signal(SIGINT, catchSignal)) != SIG_DFL)
            (void) signal(SIGINT, osig);
#endif
        return Ping::Config.count;
    }

    return 1;
}