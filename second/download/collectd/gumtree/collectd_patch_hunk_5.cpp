 	{
 		/* parent */
 		/* printf ("Running (PID %i)\n", pid); */
 		return (0);
 	}
 #endif
-
-	/* child */
-	while (loop == 0)
-	{
-#if DEBUG
-		fputs ("Starting update\n", stdout);
-#endif
-
-#ifdef HAVE_LIBKSTAT
-		update_kstat ();
-#endif
-
-#if COLLECT_CPU
-		cpu_update ();
-#endif
-#if COLLECT_DISK
-		diskstats_update ();
-#endif
-#if COLLECT_LOAD
-		load_update ();
-#endif
-#if COLLECT_MEMORY
-		mem_update ();
-#endif
-#if COLLECT_PING
-		ping_update ();
-#endif
-#if COLLECT_SENSORS
-		sensors_update ();
-#endif
-#if COLLECT_SWAP
-		swap_update ();
-#endif
-#if COLLECT_TRAFFIC
-		traffic_update ();
-#endif
-
-#if DEBUG
-		fputs ("Sleeping for 10 seconds\n", stdout);
-#endif
-		sleepingtime = 10;
-		while (sleepingtime != 0)
-		{
-			if (loop != 0)
-				break;
-
-			sleepingtime = sleep (sleepingtime);
-		}
-	}
-
-	/* close syslog */
+	
+	/*
+	 * run the actual loops
+	 */
+	if (operating_mode == MODE_SERVER)
+		start_server ();
+	else /* if (operating_mode == MODE_CLIENT || operating_mode == MODE_LOCAL) */
+		start_client ();
+
+	/*
+	 * close syslog
+	 */
 	closelog ();
 
 	return (0);
 }
