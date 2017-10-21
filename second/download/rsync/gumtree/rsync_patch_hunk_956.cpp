 	sum_update(input, sizeof input);
 	len = sum_end(digest);
 
 	base64_encode(digest, len, challenge, 0);
 }
 
+/* Generate an MD4 hash created from the combination of the password
+ * and the challenge string and return it base64-encoded. */
+static void generate_hash(const char *in, const char *challenge, char *out)
+{
+	char buf[MAX_DIGEST_LEN];
+	int len;
+
+	sum_init(0);
+	sum_update(in, strlen(in));
+	sum_update(challenge, strlen(challenge));
+	len = sum_end(buf);
+
+	base64_encode(buf, len, out, 0);
+}
 
 /* Return the secret for a user from the secret file, null terminated.
  * Maximum length is len (not counting the null). */
-static int get_secret(int module, const char *user, char *secret, int len)
+static const char *check_secret(int module, const char *user, const char *group,
+				const char *challenge, const char *pass)
 {
+	char line[1024];
+	char pass2[MAX_DIGEST_LEN*2];
 	const char *fname = lp_secrets_file(module);
 	STRUCT_STAT st;
 	int fd, ok = 1;
-	const char *p;
-	char ch, *s;
-
-	if (!fname || !*fname)
-		return 0;
+	int user_len = strlen(user);
+	int group_len = group ? strlen(group) : 0;
+	char *err;
 
-	if ((fd = open(fname, O_RDONLY)) < 0)
-		return 0;
+	if (!fname || !*fname || (fd = open(fname, O_RDONLY)) < 0)
+		return "no secrets file";
 
-	if (do_stat(fname, &st) == -1) {
-		rsyserr(FLOG, errno, "stat(%s)", fname);
+	if (do_fstat(fd, &st) == -1) {
+		rsyserr(FLOG, errno, "fstat(%s)", fname);
 		ok = 0;
 	} else if (lp_strict_modes(module)) {
 		if ((st.st_mode & 06) != 0) {
 			rprintf(FLOG, "secrets file must not be other-accessible (see strict modes option)\n");
 			ok = 0;
 		} else if (MY_UID() == 0 && st.st_uid != 0) {
 			rprintf(FLOG, "secrets file must be owned by root when running as root (see strict modes)\n");
 			ok = 0;
 		}
 	}
 	if (!ok) {
-		rprintf(FLOG, "continuing without secrets file\n");
 		close(fd);
-		return 0;
+		return "ignoring secrets file";
 	}
 
 	if (*user == '#') {
 		/* Reject attempt to match a comment. */
 		close(fd);
-		return 0;
+		return "invalid username";
 	}
 
-	/* Try to find a line that starts with the user name and a ':'. */
-	p = user;
-	while (1) {
-		if (read(fd, &ch, 1) != 1) {
-			close(fd);
-			return 0;
+	/* Try to find a line that starts with the user (or @group) name and a ':'. */
+	err = "secret not found";
+	while ((user || group) && read_line_old(fd, line, sizeof line, 1)) {
+		const char **ptr, *s;
+		int len;
+		if (*line == '@') {
+			ptr = &group;
+			len = group_len;
+			s = line+1;
+		} else {
+			ptr = &user;
+			len = user_len;
+			s = line;
 		}
-		if (ch == '\n')
-			p = user;
-		else if (p) {
-			if (*p == ch)
-				p++;
-			else if (!*p && ch == ':')
-				break;
-			else
-				p = NULL;
+		if (!*ptr || strncmp(s, *ptr, len) != 0 || s[len] != ':')
+			continue;
+		generate_hash(s+len+1, challenge, pass2);
+		if (strcmp(pass, pass2) == 0) {
+			err = NULL;
+			break;
 		}
+		err = "password mismatch";
+		*ptr = NULL; /* Don't look for name again. */
 	}
 
-	/* Slurp the secret into the "secret" buffer. */
-	s = secret;
-	while (len > 0) {
-		if (read(fd, s, 1) != 1 || *s == '\n')
-			break;
-		if (*s == '\r')
-			continue;
-		s++;
-		len--;
-	}
-	*s = '\0';
 	close(fd);
 
-	return 1;
+	memset(line, 0, sizeof line);
+	memset(pass2, 0, sizeof pass2);
+
+	return err;
 }
 
 static const char *getpassf(const char *filename)
 {
 	STRUCT_STAT st;
 	char buffer[512], *p;
-	int fd, n;
+	int n;
 
 	if (!filename)
 		return NULL;
 
-	if ((fd = open(filename,O_RDONLY)) < 0) {
-		rsyserr(FERROR, errno, "could not open password file %s", filename);
-		exit_cleanup(RERR_SYNTAX);
-	}
+	if (strcmp(filename, "-") == 0) {
+		n = fgets(buffer, sizeof buffer, stdin) == NULL ? -1 : (int)strlen(buffer);
+	} else {
+		int fd;
+
+		if ((fd = open(filename,O_RDONLY)) < 0) {
+			rsyserr(FERROR, errno, "could not open password file %s", filename);
+			exit_cleanup(RERR_SYNTAX);
+		}
 
-	if (do_stat(filename, &st) == -1) {
-		rsyserr(FERROR, errno, "stat(%s)", filename);
-		exit_cleanup(RERR_SYNTAX);
-	}
-	if ((st.st_mode & 06) != 0) {
-		rprintf(FERROR, "ERROR: password file must not be other-accessible\n");
-		exit_cleanup(RERR_SYNTAX);
-	}
-	if (MY_UID() == 0 && st.st_uid != 0) {
-		rprintf(FERROR, "ERROR: password file must be owned by root when running as root\n");
-		exit_cleanup(RERR_SYNTAX);
+		if (do_stat(filename, &st) == -1) {
+			rsyserr(FERROR, errno, "stat(%s)", filename);
+			exit_cleanup(RERR_SYNTAX);
+		}
+		if ((st.st_mode & 06) != 0) {
+			rprintf(FERROR, "ERROR: password file must not be other-accessible\n");
+			exit_cleanup(RERR_SYNTAX);
+		}
+		if (MY_UID() == 0 && st.st_uid != 0) {
+			rprintf(FERROR, "ERROR: password file must be owned by root when running as root\n");
+			exit_cleanup(RERR_SYNTAX);
+		}
+
+		n = read(fd, buffer, sizeof buffer - 1);
+		close(fd);
 	}
 
-	n = read(fd, buffer, sizeof buffer - 1);
-	close(fd);
 	if (n > 0) {
 		buffer[n] = '\0';
 		if ((p = strtok(buffer, "\n\r")) != NULL)
 			return strdup(p);
 	}
 
 	rprintf(FERROR, "ERROR: failed to read a password from %s\n", filename);
 	exit_cleanup(RERR_SYNTAX);
 }
 
-/* Generate an MD4 hash created from the combination of the password
- * and the challenge string and return it base64-encoded. */
-static void generate_hash(const char *in, const char *challenge, char *out)
-{
-	char buf[MAX_DIGEST_LEN];
-	int len;
-
-	sum_init(0);
-	sum_update(in, strlen(in));
-	sum_update(challenge, strlen(challenge));
-	len = sum_end(buf);
-
-	base64_encode(buf, len, out, 0);
-}
-
 /* Possibly negotiate authentication with the client.  Use "leader" to
  * start off the auth if necessary.
  *
  * Return NULL if authentication failed.  Return "" if anonymous access.
  * Otherwise return username.
  */
 char *auth_server(int f_in, int f_out, int module, const char *host,
 		  const char *addr, const char *leader)
 {
 	char *users = lp_auth_users(module);
 	char challenge[MAX_DIGEST_LEN*2];
 	char line[BIGPATHBUFLEN];
-	char secret[512];
-	char pass2[MAX_DIGEST_LEN*2];
+	char **auth_uid_groups = NULL;
+	int auth_uid_groups_cnt = -1;
+	const char *err = NULL;
+	int group_match = -1;
 	char *tok, *pass;
+	char opt_ch = '\0';
 
 	/* if no auth list then allow anyone in! */
 	if (!users || !*users)
 		return "";
 
 	gen_challenge(addr, challenge);
 
 	io_printf(f_out, "%s%s\n", leader, challenge);
 
-	if (!read_line_old(f_in, line, sizeof line)
+	if (!read_line_old(f_in, line, sizeof line, 0)
 	 || (pass = strchr(line, ' ')) == NULL) {
 		rprintf(FLOG, "auth failed on module %s from %s (%s): "
 			"invalid challenge response\n",
 			lp_name(module), host, addr);
 		return NULL;
 	}
 	*pass++ = '\0';
 
 	if (!(users = strdup(users)))
 		out_of_memory("auth_server");
 
 	for (tok = strtok(users, " ,\t"); tok; tok = strtok(NULL, " ,\t")) {
-		if (wildmatch(tok, line))
-			break;
+		char *opts;
+		/* See if the user appended :deny, :ro, or :rw. */
+		if ((opts = strchr(tok, ':')) != NULL) {
+			*opts++ = '\0';
+			opt_ch = isUpper(opts) ? toLower(opts) : *opts;
+			if (opt_ch == 'r') { /* handle ro and rw */
+				opt_ch = isUpper(opts+1) ? toLower(opts+1) : opts[1];
+				if (opt_ch == 'o')
+					opt_ch = 'r';
+				else if (opt_ch != 'w')
+					opt_ch = '\0';
+			} else if (opt_ch != 'd') /* if it's not deny, ignore it */
+				opt_ch = '\0';
+		} else
+			opt_ch = '\0';
+		if (*tok != '@') {
+			/* Match the username */
+			if (wildmatch(tok, line))
+				break;
+		} else {
+#ifdef HAVE_GETGROUPLIST
+			int j;
+			/* See if authorizing user is a real user, and if so, see
+			 * if it is in a group that matches tok+1 wildmat. */
+			if (auth_uid_groups_cnt < 0) {
+				gid_t gid_list[64];
+				uid_t auth_uid;
+				auth_uid_groups_cnt = sizeof gid_list / sizeof (gid_t);
+				if (!user_to_uid(line, &auth_uid, False)
+				 || getallgroups(auth_uid, gid_list, &auth_uid_groups_cnt) != NULL)
+					auth_uid_groups_cnt = 0;
+				else {
+					if ((auth_uid_groups = new_array(char *, auth_uid_groups_cnt)) == NULL)
+						out_of_memory("auth_server");
+					for (j = 0; j < auth_uid_groups_cnt; j++)
+						auth_uid_groups[j] = gid_to_group(gid_list[j]);
+				}
+			}
+			for (j = 0; j < auth_uid_groups_cnt; j++) {
+				if (auth_uid_groups[j] && wildmatch(tok+1, auth_uid_groups[j])) {
+					group_match = j;
+					break;
+				}
+			}
+			if (group_match >= 0)
+				break;
+#else
+			rprintf(FLOG, "your computer doesn't support getgrouplist(), so no @group authorization is possible.\n");
+#endif
+		}
 	}
+
 	free(users);
 
-	if (!tok) {
-		rprintf(FLOG, "auth failed on module %s from %s (%s): "
-			"unauthorized user\n",
-			lp_name(module), host, addr);
-		return NULL;
+	if (!tok)
+		err = "no matching rule";
+	else if (opt_ch == 'd')
+		err = "denied by rule";
+	else {
+		char *group = group_match >= 0 ? auth_uid_groups[group_match] : NULL;
+		err = check_secret(module, line, group, challenge, pass);
+	}
+
+	memset(challenge, 0, sizeof challenge);
+	memset(pass, 0, strlen(pass));
+
+	if (auth_uid_groups) {
+		int j;
+		for (j = 0; j < auth_uid_groups_cnt; j++) {
+			if (auth_uid_groups[j])
+				free(auth_uid_groups[j]);
+		}
+		free(auth_uid_groups);
 	}
 
-	memset(secret, 0, sizeof secret);
-	if (!get_secret(module, line, secret, sizeof secret - 1)) {
-		memset(secret, 0, sizeof secret);
-		rprintf(FLOG, "auth failed on module %s from %s (%s): "
-			"missing secret for user \"%s\"\n",
-			lp_name(module), host, addr, line);
+	if (err) {
+		rprintf(FLOG, "auth failed on module %s from %s (%s) for %s: %s\n",
+			lp_name(module), host, addr, line, err);
 		return NULL;
 	}
 
-	generate_hash(secret, challenge, pass2);
-	memset(secret, 0, sizeof secret);
-
-	if (strcmp(pass, pass2) != 0) {
-		rprintf(FLOG, "auth failed on module %s from %s (%s): "
-			"password mismatch\n",
-			lp_name(module), host, addr);
-		return NULL;
-	}
+	if (opt_ch == 'r')
+		read_only = 1;
+	else if (opt_ch == 'w')
+		read_only = 0;
 
 	return strdup(line);
 }
 
 void auth_client(int fd, const char *user, const char *challenge)
 {
