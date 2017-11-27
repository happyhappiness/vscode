 
 	/* Return `okay' even if there was an error, because it's not a syntax
 	 * problem.. */
 	return (LC_CBRET_OKAY);
 }
 
-/*
- * `cf_callback_mode_switch'
- *   Change the contents of the global variable `operating_mode'
- *
- *   This should be command line options. One *can* do this in the config
- *   files, but I will not document this. Don't whine abount it not working as
- *   you expect if you do it anyways.
- */
-int cf_callback_mode_switch (const char *shortvar, const char *var,
+static int cf_callback_socket (const char *shortvar, const char *var,
 		const char *arguments, const char *value, lc_flags_t flags,
 		void *extra)
 {
+	char *buffer;
+
+	char *fields[3];
+	int   numfields;
+
+	char *node;
+	char *service = NET_DEFAULT_PORT;
+
 	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
 			shortvar, var, arguments, value);
 
-	if (strcasecmp (shortvar, "Client") == 0)
-		operating_mode = MODE_CLIENT;
-	else if (strcasecmp (shortvar, "Local") == 0)
-		operating_mode = MODE_LOCAL;
-	else if (strcasecmp (shortvar, "Server") == 0)
-		operating_mode = MODE_SERVER;
-	else
+	buffer = strdup (value);
+	if (buffer == NULL)
+		return (LC_CBRET_ERROR);
+
+	numfields = strsplit (buffer, fields, 3);
+
+	if ((numfields != 1) && (numfields != 2))
 	{
-		fprintf (stderr, "cf_callback_mode_switch: Wrong mode!\n");
+		syslog (LOG_ERR, "Invalid number of arguments to `%s'",
+				shortvar);
+		free (buffer);
 		return (LC_CBRET_ERROR);
 	}
 
+	node = fields[0];
+	if (numfields == 2)
+		service = fields[1];
+
+	/* Still return `LC_CBRET_OKAY' because this is not an syntax error */
+	if (network_create_socket (node, service) < 1)
+		syslog (LOG_ERR, "network_create_socket (%s, %s) failed",
+				node, service);
+
+	free (buffer);
+
 	return (LC_CBRET_OKAY);
 }
 
 /*
  * `cf_callback_plugin'
  *   Start/end section `plugin'
  *
  * <Plugin `arguments'>
  *   ...
  * </Plugin>
  */
-int cf_callback_plugin (const char *shortvar, const char *var,
+static int cf_callback_plugin (const char *shortvar, const char *var,
 		const char *arguments, const char *value, lc_flags_t flags,
 		void *extra)
 {
 	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
 			shortvar, var, arguments, value);
 
