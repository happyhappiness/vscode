 	int i;
 	for (i=0;i<num_pids;i++) {
 		if (all_pids[i] != getpid())
 			kill(all_pids[i], sig);
 	}
 }
+
+/* like strncpy but does not 0 fill the buffer and always null 
+   terminates (thus it can use maxlen+1 space in d) */
+void strlcpy(char *d, char *s, int maxlen)
+{
+	int len = strlen(s);
+	if (len > maxlen) len = maxlen;
+	memcpy(d, s, len);
+	d[len] = 0;
+}
+
+/* turn a user name into a uid */
+int name_to_uid(char *name, uid_t *uid)
+{
+	struct passwd *pass;
+	if (!name || !*name) return 0;
+	pass = getpwnam(name);
+	if (pass) {
+		*uid = pass->pw_uid;
+		return 1;
+	}
+	return 0;
+}
+
+/* turn a group name into a gid */
+int name_to_gid(char *name, gid_t *gid)
+{
+	struct group *grp;
+	if (!name || !*name) return 0;
+	grp = getgrnam(name);
+	if (grp) {
+		*gid = grp->gr_gid;
+		return 1;
+	}
+	return 0;
+}
+
+
+/****************************************************************************
+check if a process exists. 
+****************************************************************************/
+int process_exists(int pid)
+{
+	return(kill(pid,0) == 0 || errno != ESRCH);
+}
+
+/* lock a byte range in a open file */
+int lock_range(int fd, int offset, int len)
+{
+	struct flock lock;
+
+	lock.l_type = F_WRLCK;
+	lock.l_whence = SEEK_SET;
+	lock.l_start = offset;
+	lock.l_len = len;
+	lock.l_pid = 0;
+	
+	return fcntl(fd,F_SETLK,&lock) == 0;
+}
+
+
+void glob_expand(char **argv, int *argc, int maxargs)
+{
+#ifndef HAVE_GLOB
+	(*argc)++;
+	return;
+#else
+	glob_t globbuf;
+	int i;
+
+	memset(&globbuf, 0, sizeof(globbuf));
+	glob(argv[*argc], 0, NULL, &globbuf);
+	if (globbuf.gl_pathc == 0) {
+		(*argc)++;
+		globfree(&globbuf);
+		return;
+	}
+	for (i=0; i<(maxargs - (*argc)) && i<globbuf.gl_pathc;i++) {
+		if (i == 0) free(argv[*argc]);
+		argv[(*argc) + i] = strdup(globbuf.gl_pathv[i]);
+		if (!argv[(*argc) + i]) out_of_memory("glob_expand");
+	}
+	globfree(&globbuf);
+	(*argc) += i;
+#endif
+}
+
+
+/*******************************************************************
+  convert a string to lower case
+********************************************************************/
+void strlower(char *s)
+{
+	while (*s) {
+		if (isupper(*s)) *s = tolower(*s);
+		s++;
+	}
+}
