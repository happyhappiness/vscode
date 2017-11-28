 
 /* Legacy debug style. Still used in some places. needs to die... */
 #define do_debug(SECTION, LEVEL)   ((Debug::level = (LEVEL)) <= Debug::Levels[SECTION])
 #define old_debug(SECTION, LEVEL)  if do_debug((SECTION), (LEVEL)) _db_print
 
 /* Legacy debug function definitions */
-extern void _db_init(const char *logfile, const char *options);
-extern void _db_print(const char *,...) PRINTF_FORMAT_ARG1;
-extern void _db_set_syslog(const char *facility);
-extern void _db_rotate_log(void);
+void _db_init(const char *logfile, const char *options);
+void _db_print(const char *,...) PRINTF_FORMAT_ARG1;
+void _db_set_syslog(const char *facility);
+void _db_rotate_log(void);
 
 #endif /* SQUID_DEBUG_H */
