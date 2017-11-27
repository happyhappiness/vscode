 	}
 	
 	return (0);
 }
 #endif /* HAVE_LIBRRD */
 
-int pidfile_create (void)
+int pidfile_create (char *file)
 {
 	FILE *fh;
 
-	if ((fh = fopen (PIDFILE, "w")) == NULL)
+	if (file == NULL)
+		file = PIDFILE;
+
+	if ((fh = fopen (file, "w")) == NULL)
 	{
-		syslog (LOG_ERR, "fopen (pidfile): %s", strerror (errno));
+		syslog (LOG_ERR, "fopen (%s): %s", file, strerror (errno));
 		return (1);
 	}
 
 	fprintf (fh, "%d\n", getpid());
 	fclose(fh);
 
