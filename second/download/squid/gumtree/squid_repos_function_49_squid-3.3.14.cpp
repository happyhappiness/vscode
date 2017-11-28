static void
set_our_signal(void)
{
#if HAVE_SIGACTION

    struct sigaction sa;
    sa.sa_handler = pipe_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGPIPE, &sa, NULL) < 0) {
        fprintf(stderr, "Cannot set PIPE signal.\n");
        exit(-1);
    }
#else
    signal(SIGPIPE, pipe_handler);

#endif

}