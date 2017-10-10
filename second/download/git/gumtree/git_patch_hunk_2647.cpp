 #include "send-pack.h"
 #include "quote.h"
 #include "transport.h"
 #include "version.h"
 #include "sha1-array.h"
 #include "gpg-interface.h"
+#include "cache.h"
+
+int option_parse_push_signed(const struct option *opt,
+			     const char *arg, int unset)
+{
+	if (unset) {
+		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_NEVER;
+		return 0;
+	}
+	switch (git_parse_maybe_bool(arg)) {
+	case 1:
+		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_ALWAYS;
+		return 0;
+	case 0:
+		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_NEVER;
+		return 0;
+	}
+	if (!strcasecmp("if-asked", arg)) {
+		*(int *)(opt->value) = SEND_PACK_PUSH_CERT_IF_ASKED;
+		return 0;
+	}
+	die("bad %s argument: %s", opt->long_name, arg);
+}
 
 static int feed_object(const unsigned char *sha1, int fd, int negative)
 {
 	char buf[42];
 
 	if (negative && !has_sha1_file(sha1))
