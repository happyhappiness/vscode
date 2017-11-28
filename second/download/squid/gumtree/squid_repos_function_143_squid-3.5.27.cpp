void
Ping::TimerStart()
{
    if (!Ping::Config.enable)
        return;

#if GETTIMEOFDAY_NO_TZP
    (void)gettimeofday(&tv1);
#else
    (void)gettimeofday(&tv1, NULL);
#endif
}