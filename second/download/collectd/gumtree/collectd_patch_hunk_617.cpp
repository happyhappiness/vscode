  *  The last argument must be
  *  a NULL pointer to signal end-of-list.
  *
  * RETURNS
  *  The number of values it failed to dispatch (zero on success).
  */
-__attribute__((sentinel))
-int plugin_dispatch_multivalue (value_list_t const *vl,
-		_Bool store_percentage, int store_type, ...);
+__attribute__((sentinel)) int plugin_dispatch_multivalue(value_list_t const *vl,
+                                                         _Bool store_percentage,
+                                                         int store_type, ...);
 
-int plugin_dispatch_missing (const value_list_t *vl);
+int plugin_dispatch_missing(const value_list_t *vl);
 
-int plugin_dispatch_notification (const notification_t *notif);
+int plugin_dispatch_notification(const notification_t *notif);
 
-void plugin_log (int level, const char *format, ...)
-	__attribute__ ((format(printf,2,3)));
+void plugin_log(int level, const char *format, ...)
+    __attribute__((format(printf, 2, 3)));
 
 /* These functions return the parsed severity or less than zero on failure. */
-int parse_log_severity (const char *severity);
-int parse_notif_severity (const char *severity);
+int parse_log_severity(const char *severity);
+int parse_notif_severity(const char *severity);
 
-#define ERROR(...)   plugin_log (LOG_ERR,     __VA_ARGS__)
-#define WARNING(...) plugin_log (LOG_WARNING, __VA_ARGS__)
-#define NOTICE(...)  plugin_log (LOG_NOTICE,  __VA_ARGS__)
-#define INFO(...)    plugin_log (LOG_INFO,    __VA_ARGS__)
+#define ERROR(...) plugin_log(LOG_ERR, __VA_ARGS__)
+#define WARNING(...) plugin_log(LOG_WARNING, __VA_ARGS__)
+#define NOTICE(...) plugin_log(LOG_NOTICE, __VA_ARGS__)
+#define INFO(...) plugin_log(LOG_INFO, __VA_ARGS__)
 #if COLLECT_DEBUG
-# define DEBUG(...)  plugin_log (LOG_DEBUG,   __VA_ARGS__)
-#else /* COLLECT_DEBUG */
-# define DEBUG(...)  /* noop */
-#endif /* ! COLLECT_DEBUG */
-
-const data_set_t *plugin_get_ds (const char *name);
-
-int plugin_notification_meta_add_string (notification_t *n,
-    const char *name,
-    const char *value);
-int plugin_notification_meta_add_signed_int (notification_t *n,
-    const char *name,
-    int64_t value);
-int plugin_notification_meta_add_unsigned_int (notification_t *n,
-    const char *name,
-    uint64_t value);
-int plugin_notification_meta_add_double (notification_t *n,
-    const char *name,
-    double value);
-int plugin_notification_meta_add_boolean (notification_t *n,
-    const char *name,
-    _Bool value);
+#define DEBUG(...) plugin_log(LOG_DEBUG, __VA_ARGS__)
+#else              /* COLLECT_DEBUG */
+#define DEBUG(...) /* noop */
+#endif             /* ! COLLECT_DEBUG */
+
+const data_set_t *plugin_get_ds(const char *name);
+
+int plugin_notification_meta_add_string(notification_t *n, const char *name,
+                                        const char *value);
+int plugin_notification_meta_add_signed_int(notification_t *n, const char *name,
+                                            int64_t value);
+int plugin_notification_meta_add_unsigned_int(notification_t *n,
+                                              const char *name, uint64_t value);
+int plugin_notification_meta_add_double(notification_t *n, const char *name,
+                                        double value);
+int plugin_notification_meta_add_boolean(notification_t *n, const char *name,
+                                         _Bool value);
 
-int plugin_notification_meta_copy (notification_t *dst,
-    const notification_t *src);
+int plugin_notification_meta_copy(notification_t *dst,
+                                  const notification_t *src);
 
-int plugin_notification_meta_free (notification_meta_t *n);
+int plugin_notification_meta_free(notification_meta_t *n);
 
 /*
  * Plugin context management.
  */
 
-void plugin_init_ctx (void);
+void plugin_init_ctx(void);
 
-plugin_ctx_t plugin_get_ctx (void);
-plugin_ctx_t plugin_set_ctx (plugin_ctx_t ctx);
+plugin_ctx_t plugin_get_ctx(void);
+plugin_ctx_t plugin_set_ctx(plugin_ctx_t ctx);
 
 /*
  * NAME
  *  plugin_get_interval
  *
  * DESCRIPTION
  *  This function returns the current value of the plugin's interval. The
  *  return value will be strictly greater than zero in all cases. If
  *  everything else fails, it will fall back to 10 seconds.
  */
-cdtime_t plugin_get_interval (void);
+cdtime_t plugin_get_interval(void);
 
 /*
  * Context-aware thread management.
  */
 
-int plugin_thread_create (pthread_t *thread, const pthread_attr_t *attr,
-		void *(*start_routine) (void *), void *arg);
+int plugin_thread_create(pthread_t *thread, const pthread_attr_t *attr,
+                         void *(*start_routine)(void *), void *arg);
 
 /*
  * Plugins need to implement this
  */
 
-void module_register (void);
+void module_register(void);
 
 #endif /* PLUGIN_H */
