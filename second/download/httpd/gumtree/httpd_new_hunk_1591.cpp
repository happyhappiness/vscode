#endif

#ifdef NEED_HASHBANG_EMUL
    ap_rputs(" -D NEED_HASHBANG_EMUL\n", r);
#endif

/* This list displays the compiled in default paths: */
#ifdef HTTPD_ROOT
    ap_rputs(" -D HTTPD_ROOT=\"" HTTPD_ROOT "\"\n", r);
#endif

#ifdef SUEXEC_BIN
    ap_rputs(" -D SUEXEC_BIN=\"" SUEXEC_BIN "\"\n", r);
#endif

#ifdef DEFAULT_PIDLOG
    ap_rputs(" -D DEFAULT_PIDLOG=\"" DEFAULT_PIDLOG "\"\n", r);
#endif

#ifdef DEFAULT_SCOREBOARD
    ap_rputs(" -D DEFAULT_SCOREBOARD=\"" DEFAULT_SCOREBOARD "\"\n", r);
#endif

#ifdef DEFAULT_ERRORLOG
    ap_rputs(" -D DEFAULT_ERRORLOG=\"" DEFAULT_ERRORLOG "\"\n", r);
#endif


#ifdef AP_TYPES_CONFIG_FILE
