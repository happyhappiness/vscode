 	char const *links = "no ";
 	char const *iconv = "no ";
 	char const *ipv6 = "no ";
 	STRUCT_STAT *dumstat;
 
 #if SUBPROTOCOL_VERSION != 0
-	asprintf(&subprotocol, ".PR%d", SUBPROTOCOL_VERSION);
+	if (asprintf(&subprotocol, ".PR%d", SUBPROTOCOL_VERSION) < 0)
+		out_of_memory("print_rsync_version");
 #endif
 #ifdef HAVE_SOCKETPAIR
 	got_socketpair = "";
 #endif
 #ifdef HAVE_FTRUNCATE
 	have_inplace = "";
