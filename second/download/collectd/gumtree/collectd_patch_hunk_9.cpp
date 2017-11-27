 
 	if (dir == NULL)
 		dir = PLUGINDIR;
 
 	if ((dh = opendir (dir)) == NULL)
 	{
-		fprintf (stderr, "Cannot read plugin directory `%s'\n", dir);
+		fprintf (stderr, "Error: Cannot read plugin directory `%s'\n", dir);
 		return (0);
 	}
 
 	while ((de = readdir (dh)) != NULL)
 	{
 		if (snprintf (filename, BUFSIZE, "%s/%s", dir, de->d_name) >= BUFSIZE)
