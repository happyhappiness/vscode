 
 /* APLOG_NOERRNO is ignored and should not be used.  It will be
  * removed in a future release of Apache.
  */
 #define APLOG_NOERRNO		(APLOG_LEVELMASK + 1)
 
-/* Use APLOG_TOCLIENT on ap_log_rerror() to give content
- * handlers the option of including the error text in the 
+/** Use APLOG_TOCLIENT on ap_log_rerror() to give content
+ * handlers the option of including the error text in the
  * ErrorDocument sent back to the client. Setting APLOG_TOCLIENT
- * will cause the error text to be saved in the request_rec->notes 
+ * will cause the error text to be saved in the request_rec->notes
  * table, keyed to the string "error-notes", if and only if:
  * - the severity level of the message is APLOG_WARNING or greater
  * - there are no other "error-notes" set in request_rec->notes
  * Once error-notes is set, it is up to the content handler to
  * determine whether this text should be sent back to the client.
- * Note: Client generated text streams sent back to the client MUST 
+ * Note: Client generated text streams sent back to the client MUST
  * be escaped to prevent CSS attacks.
  */
 #define APLOG_TOCLIENT          ((APLOG_LEVELMASK + 1) * 2)
 
 /* normal but significant condition on startup, usually printed to stderr */
-#define APLOG_STARTUP           ((APLOG_LEVELMASK + 1) * 4) 
+#define APLOG_STARTUP           ((APLOG_LEVELMASK + 1) * 4)
 
 #ifndef DEFAULT_LOGLEVEL
 #define DEFAULT_LOGLEVEL	APLOG_WARNING
 #endif
 
+/**
+ * APLOGNO() should be used at the start of the format string passed
+ * to ap_log_error() and friends. The argument must be a 5 digit decimal
+ * number. It creates a tag of the form "AH02182: "
+ * See docs/log-message-tags/README for details.
+ */
+#define APLOGNO(n)              "AH" #n ": "
+
+/**
+ * APLOG_NO_MODULE may be passed as module_index to ap_log_error() and related
+ * functions if the module causing the log message is not known. Normally this
+ * should not be used directly. Use ::APLOG_MARK or ::APLOG_MODULE_INDEX
+ * instead.
+ *
+ * @see APLOG_MARK
+ * @see APLOG_MODULE_INDEX
+ * @see ap_log_error
+ */
 #define APLOG_NO_MODULE         -1
 
-/*
+#ifdef __cplusplus
+/**
+ * C++ modules must invoke ::APLOG_USE_MODULE or ::AP_DECLARE_MODULE in
+ * every file which uses ap_log_* before the first use of ::APLOG_MARK
+ * or ::APLOG_MODULE_INDEX.
+ * (C modules *should* do that as well, to enable module-specific log
+ * levels. C modules need not obey the ordering, though).
+ */
+#else /* __cplusplus */
+/**
+ * Constant to store module_index for the current file.
  * Objects with static storage duration are set to NULL if not
- * initialized explicitly. This means if aplog_module_index
- * is not initalized using the APLOG_USE_MODULE or the
- * AP_DECLARE_MODULE macro, we can safely fall back to
- * use APLOG_NO_MODULE.
+ * initialized explicitly. This means that if aplog_module_index
+ * is not initalized using the ::APLOG_USE_MODULE or the
+ * ::AP_DECLARE_MODULE macro, we can safely fall back to
+ * use ::APLOG_NO_MODULE. This variable will usually be optimized away.
  */
 static int * const aplog_module_index;
+#endif /* __cplusplus */
+
+/**
+ * APLOG_MODULE_INDEX contains the module_index of the current module if
+ * it has been set via the ::APLOG_USE_MODULE or ::AP_DECLARE_MODULE macro.
+ * Otherwise it contains ::APLOG_NO_MODULE (for example in unmodified httpd
+ * 2.2 modules).
+ *
+ * If ::APLOG_MARK is used in ap_log_error() and related functions,
+ * ::APLOG_MODULE_INDEX will be passed as module_index. In cases where
+ * ::APLOG_MARK cannot be used, ::APLOG_MODULE_INDEX should normally be passed
+ * as module_index.
+ *
+ * @see APLOG_MARK
+ * @see ap_log_error
+ */
+#ifdef __cplusplus
+#define APLOG_MODULE_INDEX (*aplog_module_index)
+#else /* __cplusplus */
 #define APLOG_MODULE_INDEX  \
     (aplog_module_index ? *aplog_module_index : APLOG_NO_MODULE)
+#endif /* __cplusplus */
 
-/*
- * APLOG_MAX_LOGLEVEL can be used to remove logging above some
+/**
+ * APLOG_MAX_LOGLEVEL can be defined to remove logging above some
  * specified level at compile time.
+ *
+ * This requires a C99 compiler.
  */
+#ifdef DOXYGEN
+#define APLOG_MAX_LOGLEVEL
+#endif
 #ifndef APLOG_MAX_LOGLEVEL
 #define APLOG_MODULE_IS_LEVEL(s,module_index,level)              \
           ( (((level)&APLOG_LEVELMASK) <= APLOG_NOTICE) ||       \
             (s == NULL) ||                                       \
             (ap_get_server_module_loglevel(s, module_index)      \
              >= ((level)&APLOG_LEVELMASK) ) )
