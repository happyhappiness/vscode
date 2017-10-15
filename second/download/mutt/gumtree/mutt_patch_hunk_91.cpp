 /*
  * C version by Wessel Dankers <wsl@fruit.eu.org>
  *
  * This code is in the public domain.
  *
  */
+#ifdef HAVE_CONFIG_H
+#include "config.h"
+#endif
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 
+void print_usage(const char *progname) {
+	fprintf(stderr, "Command line usage: %s [flags] -- prefix [recipients]\n", progname);
+	exit(1);
+}
+
 int main(int argc, char **argv) {
 	char **opts, **opt, *pfx;
 	int i;
 
+	if (argc <= 1) {
+		print_usage(argv[0]);
+        }
+
 	opts = malloc((2 * argc + 1) * sizeof (* opts));	/* __MEM_CHECKED__ */
 	if(!opts) {
 		perror(argv[0]);
 		exit(2);
 	}
 
