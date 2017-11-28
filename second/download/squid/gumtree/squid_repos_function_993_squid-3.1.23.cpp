void
_db_print(const char *format,...)
{
    char f[BUFSIZ];
    f[0]='\0';
    va_list args1;
    va_list args2;
    va_list args3;

#ifdef _SQUID_MSWIN_
    /* Multiple WIN32 threads may call this simultaneously */

    if (!dbg_mutex) {
        HMODULE krnl_lib = GetModuleHandle("Kernel32");
        PFInitializeCriticalSectionAndSpinCount InitializeCriticalSectionAndSpinCount = NULL;

        if (krnl_lib)
            InitializeCriticalSectionAndSpinCount =
                (PFInitializeCriticalSectionAndSpinCount) GetProcAddress(krnl_lib,
                        "InitializeCriticalSectionAndSpinCount");

        dbg_mutex = static_cast<CRITICAL_SECTION*>(xcalloc(1, sizeof(CRITICAL_SECTION)));

        if (InitializeCriticalSectionAndSpinCount) {
            /* let multiprocessor systems EnterCriticalSection() fast */

            if (!InitializeCriticalSectionAndSpinCount(dbg_mutex, 4000)) {
                if (debug_log) {
                    fprintf(debug_log, "FATAL: _db_print: can't initialize critical section\n");
                    fflush(debug_log);
                }

                fprintf(stderr, "FATAL: _db_print: can't initialize critical section\n");
                abort();
            } else
                InitializeCriticalSection(dbg_mutex);
        }
    }

    EnterCriticalSection(dbg_mutex);
#endif

    /* give a chance to context-based debugging to print current context */
    if (!Ctx_Lock)
        ctx_print();

    va_start(args1, format);
    va_start(args2, format);
    va_start(args3, format);

    snprintf(f, BUFSIZ, "%s| %s",
             debugLogTime(),
             format);

    _db_print_file(f, args1);
    _db_print_stderr(f, args2);

#if HAVE_SYSLOG
    _db_print_syslog(format, args3);
#endif

#ifdef _SQUID_MSWIN_
    LeaveCriticalSection(dbg_mutex);
#endif

    va_end(args1);
    va_end(args2);
    va_end(args3);
}