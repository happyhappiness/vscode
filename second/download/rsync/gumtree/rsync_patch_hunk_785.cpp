 
 	if (tmpdir) {
 		args[ac++] = "--temp-dir";
 		args[ac++] = tmpdir;
 	}
 
-	if (compare_dest && am_sender) {
+	if (basis_dir[0] && am_sender) {
 		/* the server only needs this option if it is not the sender,
 		 *   and it may be an older version that doesn't know this
 		 *   option, so don't send it if client is the sender.
 		 */
-		args[ac++] = link_dest ? "--link-dest" : "--compare-dest";
-		args[ac++] = compare_dest;
+		int i;
+		for (i = 0; i < basis_dir_cnt; i++) {
+			args[ac++] = dest_option;
+			args[ac++] = basis_dir[i];
+		}
 	}
 
-	if (files_from && (!am_sender || remote_filesfrom_file)) {
-		if (remote_filesfrom_file) {
+	if (files_from && (!am_sender || filesfrom_host)) {
+		if (filesfrom_host) {
 			args[ac++] = "--files-from";
-			args[ac++] = remote_filesfrom_file;
+			args[ac++] = files_from;
 			if (eol_nulls)
 				args[ac++] = "--from0";
 		} else {
 			args[ac++] = "--files-from=-";
 			args[ac++] = "--from0";
 		}
+		if (!relative_paths)
+			args[ac++] = "--no-relative";
 	}
+	if (!implied_dirs && !am_sender)
+		args[ac++] = "--no-implied-dirs";
+
+	if (fuzzy_basis && am_sender)
+		args[ac++] = "--fuzzy";
+
+	if (remove_sent_files)
+		args[ac++] = "--remove-sent-files";
 
 	*argc = ac;
 	return;
 
     oom:
 	out_of_memory("server_options");
 }
 
-/**
- * Return the position of a ':' IF it is not part of a filename (i.e. as
- * long as it doesn't occur after a slash.
- */
-char *find_colon(char *s)
+/* Look for a HOST specfication of the form "HOST:PATH", "HOST::PATH", or
+ * "rsync://HOST:PORT/PATH".  If found, *host_ptr will be set to some allocated
+ * memory with the HOST.  If a daemon-accessing spec was specified, the value
+ * of *port_ptr will contain a non-0 port number, otherwise it will be set to
+ * 0.  The return value is a pointer to the PATH.  Note that the HOST spec can
+ * be an IPv6 literal address enclosed in '[' and ']' (such as "[::1]" or
+ * "[::ffff:127.0.0.1]") which is returned without the '[' and ']'. */
+char *check_for_hostspec(char *s, char **host_ptr, int *port_ptr)
 {
-	char *p, *p2;
+	char *p;
+	int not_host;
+
+	if (port_ptr && strncasecmp(URL_PREFIX, s, strlen(URL_PREFIX)) == 0) {
+		char *path;
+		int hostlen;
+		s += strlen(URL_PREFIX);
+		if ((p = strchr(s, '/')) != NULL) {
+			hostlen = p - s;
+			path = p + 1;
+		} else {
+			hostlen = strlen(s);
+			path = "";
+		}
+		if (*s == '[' && (p = strchr(s, ']')) != NULL) {
+			s++;
+			hostlen = p - s;
+			if (p[1] == ':')
+				*port_ptr = atoi(p+2);
+		} else {
+			if ((p = strchr(s, ':')) != NULL) {
+				hostlen = p - s;
+				*port_ptr = atoi(p+1);
+			}
+		}
+		if (!*port_ptr)
+			*port_ptr = RSYNC_PORT;
+		*host_ptr = new_array(char, hostlen + 1);
+		strlcpy(*host_ptr, s, hostlen + 1);
+		return path;
+	}
 
-	p = strchr(s,':');
-	if (!p)
-		return NULL;
-
-	/* now check to see if there is a / in the string before the : - if there is then
-	   discard the colon on the assumption that the : is part of a filename */
-	p2 = strchr(s,'/');
-	if (p2 && p2 < p)
-		return NULL;
+	if (*s == '[' && (p = strchr(s, ']')) != NULL && p[1] == ':') {
+		s++;
+		*p = '\0';
+		not_host = strchr(s, '/') || !strchr(s, ':');
+		*p = ']';
+		if (not_host)
+			return NULL;
+		p++;
+	} else {
+		if (!(p = strchr(s, ':')))
+			return NULL;
+		*p = '\0';
+		not_host = strchr(s, '/') != NULL;
+		*p = ':';
+		if (not_host)
+			return NULL;
+	}
+
+	*host_ptr = new_array(char, p - s + 1);
+	strlcpy(*host_ptr, s, p - s + 1);
+
+	if (p[1] == ':') {
+		if (port_ptr && !*port_ptr)
+			*port_ptr = RSYNC_PORT;
+		return p + 2;
+	}
+	if (port_ptr)
+		*port_ptr = 0;
 
-	return p;
+	return p + 1;
 }
