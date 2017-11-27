 			continue;
 
 		status = ssnprintf (filename, sizeof (filename),
 				"%s/%s", dir, de->d_name);
 		if ((status < 0) || ((size_t) status >= sizeof (filename)))
 		{
-			WARNING ("snprintf: truncated: `%s/%s'", dir, de->d_name);
+			WARNING ("plugin_load: Filename too long: \"%s/%s\"",
+					dir, de->d_name);
 			continue;
 		}
 
 		if (lstat (filename, &statbuf) == -1)
 		{
 			char errbuf[1024];
-			WARNING ("stat %s: %s", filename,
+			WARNING ("plugin_load: stat (\"%s\") failed: %s",
+					filename,
 					sstrerror (errno, errbuf, sizeof (errbuf)));
 			continue;
 		}
 		else if (!S_ISREG (statbuf.st_mode))
 		{
 			/* don't follow symlinks */
-			WARNING ("stat %s: not a regular file", filename);
+			WARNING ("plugin_load: %s is not a regular file.",
+				       	filename);
 			continue;
 		}
 
-		if (plugin_load_file (filename, flags) == 0)
+		status = plugin_load_file (filename, flags);
+		if (status == 0)
 		{
 			/* success */
 			ret = 0;
 			break;
 		}
 		else
 		{
-			fprintf (stderr, "Unable to load plugin %s.\n", type);
+			ERROR ("plugin_load: Load plugin \"%s\" failed with "
+					"status %i.", type, status);
 		}
 	}
 
 	closedir (dh);
 
-	if (filename[0] == '\0')
-		fprintf (stderr, "Could not find plugin %s.\n", type);
+	if (filename[0] == 0)
+		ERROR ("plugin_load: Could not find plugin \"%s\" in %s",
+				type, dir);
 
 	return (ret);
 }
 
 /*
  * The `register_*' functions follow
