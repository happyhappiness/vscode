 		log_ref_write(ref_target, old_sha1, new_sha1, logmsg);
 
 	free(git_HEAD);
 	return 0;
 }
 
-static char *ref_msg(const char *line, const char *endp)
-{
-	const char *ep;
-	line += 82;
-	ep = memchr(line, '\n', endp - line);
-	if (!ep)
-		ep = endp;
-	return xmemdupz(line, ep - line);
+struct read_ref_at_cb {
+	const char *refname;
+	unsigned long at_time;
+	int cnt;
+	int reccnt;
+	unsigned char *sha1;
+	int found_it;
+
+	unsigned char osha1[20];
+	unsigned char nsha1[20];
+	int tz;
+	unsigned long date;
+	char **msg;
+	unsigned long *cutoff_time;
+	int *cutoff_tz;
+	int *cutoff_cnt;
+};
+
+static int read_ref_at_ent(unsigned char *osha1, unsigned char *nsha1,
+		const char *email, unsigned long timestamp, int tz,
+		const char *message, void *cb_data)
+{
+	struct read_ref_at_cb *cb = cb_data;
+
+	cb->reccnt++;
+	cb->tz = tz;
+	cb->date = timestamp;
+
+	if (timestamp <= cb->at_time || cb->cnt == 0) {
+		if (cb->msg)
+			*cb->msg = xstrdup(message);
+		if (cb->cutoff_time)
+			*cb->cutoff_time = timestamp;
+		if (cb->cutoff_tz)
+			*cb->cutoff_tz = tz;
+		if (cb->cutoff_cnt)
+			*cb->cutoff_cnt = cb->reccnt - 1;
+		/*
+		 * we have not yet updated cb->[n|o]sha1 so they still
+		 * hold the values for the previous record.
+		 */
+		if (!is_null_sha1(cb->osha1)) {
+			hashcpy(cb->sha1, nsha1);
+			if (hashcmp(cb->osha1, nsha1))
+				warning("Log for ref %s has gap after %s.",
+					cb->refname, show_date(cb->date, cb->tz, DATE_RFC2822));
+		}
+		else if (cb->date == cb->at_time)
+			hashcpy(cb->sha1, nsha1);
+		else if (hashcmp(nsha1, cb->sha1))
+			warning("Log for ref %s unexpectedly ended on %s.",
+				cb->refname, show_date(cb->date, cb->tz,
+						   DATE_RFC2822));
+		hashcpy(cb->osha1, osha1);
+		hashcpy(cb->nsha1, nsha1);
+		cb->found_it = 1;
+		return 1;
+	}
+	hashcpy(cb->osha1, osha1);
+	hashcpy(cb->nsha1, nsha1);
+	if (cb->cnt > 0)
+		cb->cnt--;
+	return 0;
+}
+
+static int read_ref_at_ent_oldest(unsigned char *osha1, unsigned char *nsha1,
+				  const char *email, unsigned long timestamp,
+				  int tz, const char *message, void *cb_data)
+{
+	struct read_ref_at_cb *cb = cb_data;
+
+	if (cb->msg)
+		*cb->msg = xstrdup(message);
+	if (cb->cutoff_time)
+		*cb->cutoff_time = timestamp;
+	if (cb->cutoff_tz)
+		*cb->cutoff_tz = tz;
+	if (cb->cutoff_cnt)
+		*cb->cutoff_cnt = cb->reccnt;
+	hashcpy(cb->sha1, osha1);
+	if (is_null_sha1(cb->sha1))
+		hashcpy(cb->sha1, nsha1);
+	/* We just want the first entry */
+	return 1;
 }
 
 int read_ref_at(const char *refname, unsigned long at_time, int cnt,
 		unsigned char *sha1, char **msg,
 		unsigned long *cutoff_time, int *cutoff_tz, int *cutoff_cnt)
 {
-	const char *logfile, *logdata, *logend, *rec, *lastgt, *lastrec;
-	char *tz_c;
-	int logfd, tz, reccnt = 0;
-	struct stat st;
-	unsigned long date;
-	unsigned char logged_sha1[20];
-	void *log_mapped;
-	size_t mapsz;
+	struct read_ref_at_cb cb;
 
-	logfile = git_path("logs/%s", refname);
-	logfd = open(logfile, O_RDONLY, 0);
-	if (logfd < 0)
-		die_errno("Unable to read log '%s'", logfile);
-	fstat(logfd, &st);
-	if (!st.st_size)
-		die("Log %s is empty.", logfile);
-	mapsz = xsize_t(st.st_size);
-	log_mapped = xmmap(NULL, mapsz, PROT_READ, MAP_PRIVATE, logfd, 0);
-	logdata = log_mapped;
-	close(logfd);
+	memset(&cb, 0, sizeof(cb));
+	cb.refname = refname;
+	cb.at_time = at_time;
+	cb.cnt = cnt;
+	cb.msg = msg;
+	cb.cutoff_time = cutoff_time;
+	cb.cutoff_tz = cutoff_tz;
+	cb.cutoff_cnt = cutoff_cnt;
+	cb.sha1 = sha1;
+
+	for_each_reflog_ent_reverse(refname, read_ref_at_ent, &cb);
+
+	if (!cb.reccnt)
+		die("Log for %s is empty.", refname);
+	if (cb.found_it)
+		return 0;
+
+	for_each_reflog_ent(refname, read_ref_at_ent_oldest, &cb);
 
-	lastrec = NULL;
-	rec = logend = logdata + st.st_size;
-	while (logdata < rec) {
-		reccnt++;
-		if (logdata < rec && *(rec-1) == '\n')
-			rec--;
-		lastgt = NULL;
-		while (logdata < rec && *(rec-1) != '\n') {
-			rec--;
-			if (*rec == '>')
-				lastgt = rec;
-		}
-		if (!lastgt)
-			die("Log %s is corrupt.", logfile);
-		date = strtoul(lastgt + 1, &tz_c, 10);
-		if (date <= at_time || cnt == 0) {
-			tz = strtoul(tz_c, NULL, 10);
-			if (msg)
-				*msg = ref_msg(rec, logend);
-			if (cutoff_time)
-				*cutoff_time = date;
-			if (cutoff_tz)
-				*cutoff_tz = tz;
-			if (cutoff_cnt)
-				*cutoff_cnt = reccnt - 1;
-			if (lastrec) {
-				if (get_sha1_hex(lastrec, logged_sha1))
-					die("Log %s is corrupt.", logfile);
-				if (get_sha1_hex(rec + 41, sha1))
-					die("Log %s is corrupt.", logfile);
-				if (hashcmp(logged_sha1, sha1)) {
-					warning("Log %s has gap after %s.",
-						logfile, show_date(date, tz, DATE_RFC2822));
-				}
-			}
-			else if (date == at_time) {
-				if (get_sha1_hex(rec + 41, sha1))
-					die("Log %s is corrupt.", logfile);
-			}
-			else {
-				if (get_sha1_hex(rec + 41, logged_sha1))
-					die("Log %s is corrupt.", logfile);
-				if (hashcmp(logged_sha1, sha1)) {
-					warning("Log %s unexpectedly ended on %s.",
-						logfile, show_date(date, tz, DATE_RFC2822));
-				}
-			}
-			munmap(log_mapped, mapsz);
-			return 0;
-		}
-		lastrec = rec;
-		if (cnt > 0)
-			cnt--;
-	}
-
-	rec = logdata;
-	while (rec < logend && *rec != '>' && *rec != '\n')
-		rec++;
-	if (rec == logend || *rec == '\n')
-		die("Log %s is corrupt.", logfile);
-	date = strtoul(rec + 1, &tz_c, 10);
-	tz = strtoul(tz_c, NULL, 10);
-	if (get_sha1_hex(logdata, sha1))
-		die("Log %s is corrupt.", logfile);
-	if (is_null_sha1(sha1)) {
-		if (get_sha1_hex(logdata + 41, sha1))
-			die("Log %s is corrupt.", logfile);
-	}
-	if (msg)
-		*msg = ref_msg(logdata, logend);
-	munmap(log_mapped, mapsz);
-
-	if (cutoff_time)
-		*cutoff_time = date;
-	if (cutoff_tz)
-		*cutoff_tz = tz;
-	if (cutoff_cnt)
-		*cutoff_cnt = reccnt;
 	return 1;
 }
 
+int reflog_exists(const char *refname)
+{
+	struct stat st;
+
+	return !lstat(git_path("logs/%s", refname), &st) &&
+		S_ISREG(st.st_mode);
+}
+
+int delete_reflog(const char *refname)
+{
+	return remove_path(git_path("logs/%s", refname));
+}
+
 static int show_one_reflog_ent(struct strbuf *sb, each_reflog_ent_fn fn, void *cb_data)
 {
 	unsigned char osha1[20], nsha1[20];
 	char *email_end, *message;
 	unsigned long timestamp;
 	int tz;
