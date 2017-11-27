 	double timeout = 0.0;
 	char **plugins = NULL;
 	size_t plugins_num = 0;
 	char **identifiers = NULL;
 	size_t identifiers_num = 0;
 
-	size_t i;
-
 #define PRINT_TO_SOCK(fh, ...) \
 	do { \
 		if (fprintf (fh, __VA_ARGS__) < 0) { \
 			char errbuf[1024]; \
 			WARNING ("handle_flush: failed to write to socket #%i: %s", \
 					fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
