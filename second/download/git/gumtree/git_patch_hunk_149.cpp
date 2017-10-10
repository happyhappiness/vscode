 
 	if (!(config_file = fopen(config_filename, "rb"))) {
 		/* no config file means nothing to rename, no error */
 		goto unlock_and_out;
 	}
 
+	fstat(fileno(config_file), &st);
+
+	if (chmod(lock->filename, st.st_mode & 07777) < 0) {
+		ret = error("chmod on %s failed: %s",
+				lock->filename, strerror(errno));
+		goto out;
+	}
+
 	while (fgets(buf, sizeof(buf), config_file)) {
 		int i;
 		int length;
 		char *output = buf;
 		for (i = 0; buf[i] && isspace(buf[i]); i++)
 			; /* do nothing */
