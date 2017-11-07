static void terminate(void)
{
#ifdef NETWARE
    pressanykey();
#endif
    apr_terminate();
}