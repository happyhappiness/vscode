 		}
 				
 	}
 
 	/*
 	 * Load plugins and change to output directory
+	 * Loading plugins is done first so relative paths work as expected..
 	 */
 	if (plugin_load_all (plugindir) < 1)
 	{
 		fprintf (stderr, "Error: No plugins found.\n");
 		return (1);
 	}
 
 	if (change_basedir (basedir))
 	{
-		fprintf (stderr, "Unable to change to directory `%s'.\n", basedir);
+		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", basedir);
 		return (1);
 	}
 
 	/*
 	 * install signal handlers
 	 */
