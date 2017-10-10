 		return 0;
 
 	f = fopen(filename, "r");
 	if (!f) {
 		if (errno == ENOENT)
 			return 0;
-		return error("unable to open mailmap at %s: %s",
-			     filename, strerror(errno));
+		return error_errno("unable to open mailmap at %s", filename);
 	}
 
 	while (fgets(buffer, sizeof(buffer), f) != NULL)
 		read_mailmap_line(map, buffer, repo_abbrev);
 	fclose(f);
 	return 0;
