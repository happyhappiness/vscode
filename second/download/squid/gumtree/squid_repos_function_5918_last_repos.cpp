void
helperfail(const char *reason)
{
#if FAIL_DEBUG
    fail_debug_enabled =1;
#endif
    SEND_BH(reason);
}