static void
clientdbScheduledGC(void *unused)
{
    cleanup_scheduled = 0;
    clientdbStartGC();
}