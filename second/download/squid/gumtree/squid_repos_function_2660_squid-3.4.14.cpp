void
setMaxFD(void)
{
#if HAVE_SETRLIMIT && defined(RLIMIT_NOFILE)

    /* On Linux with 64-bit file support the sys/resource.h header
     * uses #define to change the function definition to require rlimit64
     */
#if defined(getrlimit)
    struct rlimit64 rl; // Assume its a 64-bit redefine anyways.
#else
    struct rlimit rl;
#endif

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        debugs(50, DBG_CRITICAL, "setrlimit: RLIMIT_NOFILE: " << xstrerror());
    } else if (Config.max_filedescriptors > 0) {
#if USE_SELECT || USE_SELECT_WIN32
        /* select() breaks if this gets set too big */
        if (Config.max_filedescriptors > FD_SETSIZE) {
            rl.rlim_cur = FD_SETSIZE;
            debugs(50, DBG_CRITICAL, "WARNING: 'max_filedescriptors " << Config.max_filedescriptors << "' does not work with select()");
        } else
#endif
            rl.rlim_cur = Config.max_filedescriptors;
        if (rl.rlim_cur > rl.rlim_max)
            rl.rlim_max = rl.rlim_cur;
        if (setrlimit(RLIMIT_NOFILE, &rl)) {
            debugs(50, DBG_CRITICAL, "ERROR: setrlimit: RLIMIT_NOFILE: " << xstrerror());
            getrlimit(RLIMIT_NOFILE, &rl);
            rl.rlim_cur = rl.rlim_max;
            if (setrlimit(RLIMIT_NOFILE, &rl)) {
                debugs(50, DBG_CRITICAL, "ERROR: setrlimit: RLIMIT_NOFILE: " << xstrerror());
            }
        }
    }
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        debugs(50, DBG_CRITICAL, "ERROR: getrlimit: RLIMIT_NOFILE: " << xstrerror());
    } else {
        Squid_MaxFD = rl.rlim_cur;
    }

#endif /* HAVE_SETRLIMIT */
}