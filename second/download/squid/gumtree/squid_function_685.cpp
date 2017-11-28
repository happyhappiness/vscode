void
keepCapabilities(void)
{
#if HAVE_PRCTL && defined(PR_SET_KEEPCAPS) && USE_LIBCAP

    if (prctl(PR_SET_KEEPCAPS, 1, 0, 0, 0)) {
        IpInterceptor.StopTransparency("capability setting has failed.");
    }
#endif
}