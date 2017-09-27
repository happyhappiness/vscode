#endif

#ifdef NEED_HASHBANG_EMUL
    printf(" -D NEED_HASHBANG_EMUL\n");
#endif

#ifdef SHARED_CORE
    printf(" -D SHARED_CORE\n");
#endif

/* This list displays the compiled in default paths: */
#ifdef HTTPD_ROOT
    printf(" -D HTTPD_ROOT=\"" HTTPD_ROOT "\"\n");
#endif

#ifdef SUEXEC_BIN
    printf(" -D SUEXEC_BIN=\"" SUEXEC_BIN "\"\n");
#endif

#if defined(SHARED_CORE) && defined(SHARED_CORE_DIR)
    printf(" -D SHARED_CORE_DIR=\"" SHARED_CORE_DIR "\"\n");
#endif

#ifdef DEFAULT_PIDLOG
    printf(" -D DEFAULT_PIDLOG=\"" DEFAULT_PIDLOG "\"\n");
#endif

#ifdef DEFAULT_SCOREBOARD
    printf(" -D DEFAULT_SCOREBOARD=\"" DEFAULT_SCOREBOARD "\"\n");
#endif

#ifdef DEFAULT_LOCKFILE
    printf(" -D DEFAULT_LOCKFILE=\"" DEFAULT_LOCKFILE "\"\n");
#endif

#ifdef DEFAULT_ERRORLOG
    printf(" -D DEFAULT_ERRORLOG=\"" DEFAULT_ERRORLOG "\"\n");
#endif

#ifdef AP_TYPES_CONFIG_FILE
    printf(" -D AP_TYPES_CONFIG_FILE=\"" AP_TYPES_CONFIG_FILE "\"\n");
