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
    if (signal(sig, sigusr2_handle) == SIG_ERR)	/* reinstall */
        debugs(50, DBG_CRITICAL, "signal: sig=" << sig << " func=sigusr2_handle: " << xstrerror());
