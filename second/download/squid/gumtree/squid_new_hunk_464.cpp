
        state = 0;
    }

#if !HAVE_SIGACTION
    if (signal(sig, sigusr2_handle) == SIG_ERR)	/* reinstall */
        debugs(50, DBG_CRITICAL, "signal: sig=" << sig << " func=sigusr2_handle: " << xstrerror());

#endif
}

void
debug_trap(const char *message)
{
    if (!opt_catch_signals)
        fatal_dump(message);

    _db_print("WARNING: %s\n", message);
}

void
sig_child(int sig)
{
#if !_SQUID_WINDOWS_
#if _SQUID_NEXT_
    union wait status;
#else

    int status;
#endif
