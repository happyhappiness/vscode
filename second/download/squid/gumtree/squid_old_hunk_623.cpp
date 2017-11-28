static int
Now(struct timeval *tp)
{
#if GETTIMEOFDAY_NO_TZP
    return gettimeofday(tp);
#else

    return gettimeofday(tp, NULL);
#endif
}				/* ARGSUSED */

void
catchSignal(int sig)
{
    interrupted = 1;
    fprintf(stderr, "Interrupted.\n");
