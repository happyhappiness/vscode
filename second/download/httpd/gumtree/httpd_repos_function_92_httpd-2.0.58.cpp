static void terminate(void)
{
    apr_terminate();
#ifdef NETWARE
    pressanykey();
#endif
}