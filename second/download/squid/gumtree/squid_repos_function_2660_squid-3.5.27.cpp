void
keepCapabilities(void)
{
#if USE_LIBCAP && HAVE_PRCTL && defined(PR_SET_KEEPCAPS)

    if (prctl(PR_SET_KEEPCAPS, 1, 0, 0, 0)) {
        Ip::Interceptor.StopTransparency("capability setting has failed.");
    }
#endif
}