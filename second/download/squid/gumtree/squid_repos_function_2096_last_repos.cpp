void
sigusr2_handle(int sig)
{
    static int state = 0;
    /* no debugs() here; bad things happen if the signal is delivered during _db_print() */

    DebugSignal = sig;

    if (state == 0) {
        Debug::parseOptions("ALL,7");
        state = 1;
    } else {
        Debug::parseOptions(Debug::debugOptions);
        state = 0;
    }

#if !HAVE_SIGACTION
    /* reinstall */
    if (signal(sig, sigusr2_handle) == SIG_ERR) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, "signal: sig=" << sig << " func=sigusr2_handle: " << xstrerr(xerrno));
    }
#endif
}