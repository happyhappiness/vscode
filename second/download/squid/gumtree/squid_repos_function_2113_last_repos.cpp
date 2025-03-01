void
setSystemLimits(void)
{
#if HAVE_SETRLIMIT && defined(RLIMIT_NOFILE) && !_SQUID_CYGWIN_
    /* limit system filedescriptors to our own limit */

    /* On Linux with 64-bit file support the sys/resource.h header
     * uses #define to change the function definition to require rlimit64
     */
#if defined(getrlimit)
    struct rlimit64 rl; // Assume its a 64-bit redefine anyways.
#else
    struct rlimit rl;
#endif

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, "getrlimit: RLIMIT_NOFILE: " << xstrerr(xerrno));
    } else {
        rl.rlim_cur = Squid_MaxFD;
        if (setrlimit(RLIMIT_NOFILE, &rl) < 0) {
            int xerrno = errno;
            snprintf(tmp_error_buf, ERROR_BUF_SZ, "setrlimit: RLIMIT_NOFILE: %s", xstrerr(xerrno));
            fatal_dump(tmp_error_buf);
        }
    }
#endif /* HAVE_SETRLIMIT */

#if HAVE_SETRLIMIT && defined(RLIMIT_DATA) && !_SQUID_CYGWIN_
    if (getrlimit(RLIMIT_DATA, &rl) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, "getrlimit: RLIMIT_DATA: " << xstrerr(xerrno));
    } else if (rl.rlim_max > rl.rlim_cur) {
        rl.rlim_cur = rl.rlim_max;  /* set it to the max */

        if (setrlimit(RLIMIT_DATA, &rl) < 0) {
            int xerrno = errno;
            snprintf(tmp_error_buf, ERROR_BUF_SZ, "setrlimit: RLIMIT_DATA: %s", xstrerr(xerrno));
            fatal_dump(tmp_error_buf);
        }
    }
#endif /* RLIMIT_DATA */
    if (Config.max_filedescriptors > Squid_MaxFD) {
        debugs(50, DBG_IMPORTANT, "NOTICE: Could not increase the number of filedescriptors");
    }

#if HAVE_SETRLIMIT && defined(RLIMIT_VMEM) && !_SQUID_CYGWIN_
    if (getrlimit(RLIMIT_VMEM, &rl) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, "getrlimit: RLIMIT_VMEM: " << xstrerr(xerrno));
    } else if (rl.rlim_max > rl.rlim_cur) {
        rl.rlim_cur = rl.rlim_max;  /* set it to the max */

        if (setrlimit(RLIMIT_VMEM, &rl) < 0) {
            int xerrno = errno;
            snprintf(tmp_error_buf, ERROR_BUF_SZ, "setrlimit: RLIMIT_VMEM: %s", xstrerr(xerrno));
            fatal_dump(tmp_error_buf);
        }
    }
#endif /* RLIMIT_VMEM */
}