 	if (plugin_load_all (plugindir) < 1)
 	{
 		fprintf (stderr, "Error: No plugins found.\n");
 		return (1);
 	}
 
-	if (change_basedir (basedir))
+	if (change_basedir (datadir))
 	{
-		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", basedir);
+		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", datadir);
 		return (1);
 	}
 
 	/*
 	 * install signal handlers
 	 */
