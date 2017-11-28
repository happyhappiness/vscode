static void
timeout_during_auth(int signum)
{
    dc_disconnect();
}