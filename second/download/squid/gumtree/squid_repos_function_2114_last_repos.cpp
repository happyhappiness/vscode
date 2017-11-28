void
squid_signal(int sig, SIGHDLR * func, int flags)
{
#if HAVE_SIGACTION

    struct sigaction sa;
    sa.sa_handler = func;
    sa.sa_flags = flags;
    sigemptyset(&sa.sa_mask);

    if (sigaction(sig, &sa, NULL) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, "sigaction: sig=" << sig << " func=" << func << ": " << xstrerr(xerrno));
    }
#else
#if _SQUID_WINDOWS_
    /*
    On Windows, only SIGINT, SIGILL, SIGFPE, SIGTERM, SIGBREAK, SIGABRT and SIGSEGV signals
    are supported, so we must care of don't call signal() for other value.
    The SIGILL, SIGSEGV, and SIGTERM signals are not generated under Windows. They are defined
    for ANSI compatibility, so both SIGSEGV and SIGBUS are emulated with an Exception Handler.
    */
    switch (sig) {

    case SIGINT:

    case SIGILL:

    case SIGFPE:

    case SIGTERM:

    case SIGBREAK:

    case SIGABRT:
        break;

    case SIGSEGV:
        WIN32_ExceptionHandlerInit();
        break;

    case SIGBUS:
        WIN32_ExceptionHandlerInit();
        return;
        break;  /* Nor reached */

    default:
        return;
        break;  /* Nor reached */
    }

#endif

    signal(sig, func);

#endif
}