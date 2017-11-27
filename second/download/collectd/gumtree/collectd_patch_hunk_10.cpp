 	char    recvline[1024];
 	char   *tokptr;
 	char   *key;
 	double  value;
 
 	static int sockfd   = -1;
-	static unsigned int complain = 0;
+	static complain_t compl;
 
 #if APCMAIN
 # define PRINT_VALUE(name, val) printf("  Found property: name = %s; value = %f;\n", name, val)
 #else
 # define PRINT_VALUE(name, val) /**/
 #endif
 
 	if (sockfd < 0)
 	{
 		if ((sockfd = net_open (host, NULL, port)) < 0)
 		{
-			/* Complain once every six hours. */
-			int complain_step = 21600 / atoi (COLLECTD_STEP);
-
-			if ((complain % complain_step) == 0)
-				syslog (LOG_ERR, "apcups plugin: Connecting to the apcupsd failed.");
-			complain++;
-
+			plugin_complain (LOG_ERR, &compl, "apcups plugin: "
+					"Connecting to the apcupsd failed.");
 			return (-1);
 		}
-		else if (complain > 1)
+		else
 		{
-			syslog (LOG_NOTICE, "apcups plugin: Connection re-established to the apcupsd.");
-			complain = 0;
+			plugin_relief (LOG_NOTICE, &compl, "apcups plugin: "
+					"Connection re-established to the apcupsd.");
 		}
 	}
 
 	if (net_send (&sockfd, "status", 6) < 0)
 	{
 		syslog (LOG_ERR, "apcups plugin: Writing to the socket failed.");
