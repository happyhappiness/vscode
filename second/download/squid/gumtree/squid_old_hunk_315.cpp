#else

    return gettimeofday(tp, NULL);
#endif
}				/* ARGSUSED */

static void
catchSignal(int sig)
{
    interrupted = 1;
    fprintf(stderr, "Interrupted.\n");
}

static void
pipe_handler(int sig)
{
    fprintf(stderr, "SIGPIPE received.\n");
}

static void
