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

void
debug_trap(const char *message)
{
    if (!opt_catch_signals)
        fatal_dump(message);

    _db_print("WARNING: %s\n", message);
}

const char *
getMyHostname(void)
{
    LOCAL_ARRAY(char, host, SQUIDHOSTNAMELEN + 1);
    static int present = 0;
    struct addrinfo *AI = NULL;
