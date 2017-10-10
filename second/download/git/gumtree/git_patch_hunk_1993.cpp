  */
 
 #include "cache.h"
 #include "credential.h"
 #include "exec_cmd.h"
 #include "run-command.h"
+#include "parse-options.h"
 #ifdef NO_OPENSSL
 typedef void *SSL;
 #endif
+#ifdef USE_CURL_FOR_IMAP_SEND
+#include "http.h"
+#endif
+
+static int verbosity;
+static int use_curl; /* strictly opt in */
 
-static const char imap_send_usage[] = "git imap-send < <mbox>";
+static const char * const imap_send_usage[] = { "git imap-send [-v] [-q] [--[no-]curl] < <mbox>", NULL };
+
+static struct option imap_send_options[] = {
+	OPT__VERBOSITY(&verbosity),
+	OPT_BOOL(0, "curl", &use_curl, "use libcurl to communicate with the IMAP server"),
+	OPT_END()
+};
 
 #undef DRV_OK
 #define DRV_OK          0
 #define DRV_MSG_BAD     -1
 #define DRV_BOX_BAD     -2
 #define DRV_STORE_BAD   -3
 
-static int Verbose, Quiet;
-
 __attribute__((format (printf, 1, 2)))
 static void imap_info(const char *, ...);
 __attribute__((format (printf, 1, 2)))
 static void imap_warn(const char *, ...);
 
 static char *next_arg(char **);
