 
 int plugin_dispatch_notification (const notification_t *notif);
 
 void plugin_log (int level, const char *format, ...)
 	__attribute__ ((format(printf,2,3)));
 
+/* These functions return the parsed severity or less than zero on failure. */
+int parse_log_severity (const char *severity);
+int parse_notif_severity (const char *severity);
+
 #define ERROR(...)   plugin_log (LOG_ERR,     __VA_ARGS__)
 #define WARNING(...) plugin_log (LOG_WARNING, __VA_ARGS__)
 #define NOTICE(...)  plugin_log (LOG_NOTICE,  __VA_ARGS__)
 #define INFO(...)    plugin_log (LOG_INFO,    __VA_ARGS__)
 #if COLLECT_DEBUG
 # define DEBUG(...)  plugin_log (LOG_DEBUG,   __VA_ARGS__)
