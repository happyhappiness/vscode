 extern NORETURN void usage_msg_opt(const char *msg,
 				   const char * const *usagestr,
 				   const struct option *options);
 
 extern int optbug(const struct option *opt, const char *reason);
 extern int opterror(const struct option *opt, const char *reason, int flags);
-#if defined(__GNUC__) && ! defined(__clang__)
-#define opterror(o,r,f) (opterror((o),(r),(f)), -1)
+#if defined(__GNUC__)
+#define opterror(o,r,f) (opterror((o),(r),(f)), const_error())
 #endif
 
 /*----- incremental advanced APIs -----*/
 
 enum {
 	PARSE_OPT_HELP = -1,
