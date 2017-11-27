 	char    recvline[1024];
 	char   *tokptr;
 	char   *toksaveptr;
 	char   *key;
 	double  value;
 
-	static complain_t compl;
-
 #if APCMAIN
 # define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
 #else
 # define PRINT_VALUE(name, val) /**/
 #endif
 
 	if (global_sockfd < 0)
 	{
-		if ((global_sockfd = net_open (host, NULL, port)) < 0)
+		global_sockfd = net_open (host, port);
+		if (global_sockfd < 0)
 		{
-			plugin_complain (LOG_ERR, &compl, "apcups plugin: "
-					"Connecting to the apcupsd failed.");
+			ERROR ("apcups plugin: Connecting to the "
+					"apcupsd failed.");
 			return (-1);
 		}
-		else
-		{
-			plugin_relief (LOG_NOTICE, &compl, "apcups plugin: "
-					"Connection re-established to the apcupsd.");
-		}
 	}
 
 	if (net_send (&global_sockfd, "status", 6) < 0)
 	{
 		ERROR ("apcups plugin: Writing to the socket failed.");
 		return (-1);
 	}
 
 	while ((n = net_recv (&global_sockfd, recvline, sizeof (recvline) - 1)) > 0)
 	{
-		assert (n < sizeof (recvline));
+		assert ((unsigned int)n < sizeof (recvline));
 		recvline[n] = '\0';
 #if APCMAIN
 		printf ("net_recv = `%s';\n", recvline);
 #endif /* if APCMAIN */
 
 		toksaveptr = NULL;
