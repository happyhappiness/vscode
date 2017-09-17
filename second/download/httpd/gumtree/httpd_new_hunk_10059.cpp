#ifdef NEED_HASHBANG_EMUL
    printf(" -D NEED_HASHBANG_EMUL\n");
#endif
#ifdef SHARED_CORE
    printf(" -D SHARED_CORE\n");
#endif

/* This list displays the compiled-in default paths: */
#ifdef HTTPD_ROOT
    printf(" -D HTTPD_ROOT=\"" HTTPD_ROOT "\"\n");
#endif
#ifdef SUEXEC_BIN
    printf(" -D SUEXEC_BIN=\"" SUEXEC_BIN "\"\n");
#endif
#ifdef SHARED_CORE_DIR
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
#ifdef DEFAULT_XFERLOG
    printf(" -D DEFAULT_XFERLOG=\"" DEFAULT_XFERLOG "\"\n");
#endif
#ifdef DEFAULT_ERRORLOG
    printf(" -D DEFAULT_ERRORLOG=\"" DEFAULT_ERRORLOG "\"\n");
#endif
#ifdef TYPES_CONFIG_FILE
    printf(" -D TYPES_CONFIG_FILE=\"" TYPES_CONFIG_FILE "\"\n");
#endif
#ifdef SERVER_CONFIG_FILE
    printf(" -D SERVER_CONFIG_FILE=\"" SERVER_CONFIG_FILE "\"\n");
#endif
#ifdef ACCESS_CONFIG_FILE
    printf(" -D ACCESS_CONFIG_FILE=\"" ACCESS_CONFIG_FILE "\"\n");
#endif
#ifdef RESOURCE_CONFIG_FILE
    printf(" -D RESOURCE_CONFIG_FILE=\"" RESOURCE_CONFIG_FILE "\"\n");
#endif
}


/* Some init code that's common between win32 and unix... well actually
 * some of it is #ifdef'd but was duplicated before anyhow.  This stuff
 * is still a mess.
