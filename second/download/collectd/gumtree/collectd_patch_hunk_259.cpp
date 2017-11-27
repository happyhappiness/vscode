  **/
 
 #include "collectd.h"
 #include "common.h"
 #include "plugin.h"
 
+#include "utils_parse_option.h"
+
 #define print_to_socket(fh, ...) \
 	if (fprintf (fh, __VA_ARGS__) < 0) { \
 		char errbuf[1024]; \
 		WARNING ("handle_putval: failed to write to socket #%i: %s", \
 				fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
 		return -1; \
 	}
 
 static int parse_value (const data_set_t *ds, value_list_t *vl,
-		const char *type,
 	       	FILE *fh, char *buffer)
 {
 	char *dummy;
 	char *ptr;
 	char *saveptr;
 	int i;
