static void
clientdbScheduledGC(void *)
{
    cleanup_scheduled = 0;
    clientdbStartGC();
}