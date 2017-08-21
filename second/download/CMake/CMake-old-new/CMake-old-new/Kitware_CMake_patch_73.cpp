@@ -88,7 +88,7 @@ typedef enum {
 	WT_RVIS,
 	/* conversion, unsupported */
 	WT_CONV,
-	/* continutation, unsupported at the moment */
+	/* continuation, unsupported at the moment */
 	WT_CONT,
 	/* invalid type */
 	LAST_WT
@@ -134,8 +134,8 @@ static ssize_t _warc_rdlen(const char *buf, size_t bsz);
 static time_t _warc_rdrtm(const char *buf, size_t bsz);
 static time_t _warc_rdmtm(const char *buf, size_t bsz);
 static const char *_warc_find_eoh(const char *buf, size_t bsz);
+static const char *_warc_find_eol(const char *buf, size_t bsz);
 
-
 int
 archive_read_support_format_warc(struct archive *_a)
 {
@@ -146,12 +146,11 @@ archive_read_support_format_warc(struct archive *_a)
 	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
 	    ARCHIVE_STATE_NEW, "archive_read_support_format_warc");
 
-	if ((w = malloc(sizeof(*w))) == NULL) {
+	if ((w = calloc(1, sizeof(*w))) == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate warc data");
 		return (ARCHIVE_FATAL);
 	}
-	memset(w, 0, sizeof(*w));
 
 	r = __archive_read_register_format(
 		a, w, "warc",
@@ -199,8 +198,8 @@ _warc_bid(struct archive_read *a, int best_bid)
 
 	/* otherwise snarf the record's version number */
 	ver = _warc_rdver(hdr, nrd);
-	if (ver == 0U || ver > 10000U) {
-		/* oh oh oh, best not to wager ... */
+	if (ver < 1200U || ver > 10000U) {
+		/* we only support WARC 0.12 to 1.0 */
 		return -1;
 	}
 
@@ -255,23 +254,32 @@ _warc_rdhdr(struct archive_read *a, struct archive_entry *entry)
 			&a->archive, ARCHIVE_ERRNO_MISC,
 			"Bad record header");
 		return (ARCHIVE_FATAL);
-	} else if ((ver = _warc_rdver(buf, eoh - buf)) > 10000U) {
-		/* nawww, I wish they promised backward compatibility
-		 * anyhoo, in their infinite wisdom the 28500 guys might
-		 * come up with something we can't possibly handle so
-		 * best end things here */
+	}
+	ver = _warc_rdver(buf, eoh - buf);
+	/* we currently support WARC 0.12 to 1.0 */
+	if (ver == 0U) {
 		archive_set_error(
 			&a->archive, ARCHIVE_ERRNO_MISC,
-			"Unsupported record version");
+			"Invalid record version");
 		return (ARCHIVE_FATAL);
-	} else if ((cntlen = _warc_rdlen(buf, eoh - buf)) < 0) {
+	} else if (ver < 1200U || ver > 10000U) {
+		archive_set_error(
+			&a->archive, ARCHIVE_ERRNO_MISC,
+			"Unsupported record version: %u.%u",
+			ver / 10000, (ver % 10000) / 100);
+		return (ARCHIVE_FATAL);
+	}
+	cntlen = _warc_rdlen(buf, eoh - buf);
+	if (cntlen < 0) {
 		/* nightmare!  the specs say content-length is mandatory
 		 * so I don't feel overly bad stopping the reader here */
 		archive_set_error(
 			&a->archive, EINVAL,
 			"Bad content length");
 		return (ARCHIVE_FATAL);
-	} else if ((rtime = _warc_rdrtm(buf, eoh - buf)) == (time_t)-1) {
+	}
+	rtime = _warc_rdrtm(buf, eoh - buf);
+	if (rtime == (time_t)-1) {
 		/* record time is mandatory as per WARC/1.0,
 		 * so just barf here, fast and loud */
 		archive_set_error(
@@ -285,7 +293,7 @@ _warc_rdhdr(struct archive_read *a, struct archive_entry *entry)
 	if (ver != w->pver) {
 		/* stringify this entry's version */
 		archive_string_sprintf(&w->sver,
-			"WARC/%u.%u", ver / 10000, ver % 10000);
+			"WARC/%u.%u", ver / 10000, (ver % 10000) / 100);
 		/* remember the version */
 		w->pver = ver;
 	}
@@ -318,7 +326,7 @@ _warc_rdhdr(struct archive_read *a, struct archive_entry *entry)
 		}
 		memcpy(w->pool.str, fnam.str, fnam.len);
 		w->pool.str[fnam.len] = '\0';
-		/* let noone else know about the pool, it's a secret, shhh */
+		/* let no one else know about the pool, it's a secret, shhh */
 		fnam.str = w->pool.str;
 
 		/* snarf mtime or deduce from rtime
@@ -535,7 +543,8 @@ xstrpisotime(const char *s, char **endptr)
 
 	/* as a courtesy to our callers, and since this is a non-standard
 	 * routine, we skip leading whitespace */
-	for (; isspace(*s); s++);
+	while (isblank((unsigned char)*s))
+		++s;
 
 	/* read year */
 	if ((tm.tm_year = strtoi_lim(s, &s, 1583, 4095)) < 0 || *s++ != '-') {
@@ -562,7 +571,7 @@ xstrpisotime(const char *s, char **endptr)
 		goto out;
 	}
 
-	/* massage TM to fulfill some of POSIX' contraints */
+	/* massage TM to fulfill some of POSIX' constraints */
 	tm.tm_year -= 1900;
 	tm.tm_mon--;
 
@@ -577,51 +586,41 @@ xstrpisotime(const char *s, char **endptr)
 }
 
 static unsigned int
-_warc_rdver(const char buf[10], size_t bsz)
+_warc_rdver(const char *buf, size_t bsz)
 {
 	static const char magic[] = "WARC/";
-	unsigned int ver;
-
-	(void)bsz; /* UNUSED */
+	unsigned int ver = 0U;
+	unsigned int end = 0U;
 
-	if (memcmp(buf, magic, sizeof(magic) - 1U) != 0) {
-		/* nope */
-		return 99999U;
+	if (bsz < 12 || memcmp(buf, magic, sizeof(magic) - 1U) != 0) {
+		/* buffer too small or invalid magic */
+		return ver;
 	}
 	/* looks good so far, read the version number for a laugh */
 	buf += sizeof(magic) - 1U;
-	/* most common case gets a quick-check here */
-	if (memcmp(buf, "1.0\r\n", 5U) == 0) {
-		ver = 10000U;
-	} else {
-		switch (*buf) {
-		case '0':
-		case '1':
-		case '2':
-		case '3':
-		case '4':
-		case '5':
-		case '6':
-		case '7':
-		case '8':
-			if (buf[1U] == '.') {
-				char *on;
-
-				/* set up major version */
-				ver = (buf[0U] - '0') * 10000U;
-				/* minor version, anyone? */
-				ver += (strtol(buf + 2U, &on, 10)) * 100U;
-				/* don't parse anything else */
-				if (on > buf + 2U) {
-					break;
-				}
-			}
-			/* FALLTHROUGH */
-		case '9':
-		default:
-			/* just make the version ridiculously high */
-			ver = 999999U;
-			break;
+
+	if (isdigit(buf[0U]) && (buf[1U] == '.') && isdigit(buf[2U])) {
+		/* we support a maximum of 2 digits in the minor version */
+		if (isdigit(buf[3U]))
+			end = 1U;
+		/* set up major version */
+		ver = (buf[0U] - '0') * 10000U;
+		/* set up minor version */
+		if (end == 1U) {
+			ver += (buf[2U] - '0') * 1000U;
+			ver += (buf[3U] - '0') * 100U;
+		} else
+			ver += (buf[2U] - '0') * 100U;
+		/*
+		 * WARC below version 0.12 has a space-separated header
+		 * WARC 0.12 and above terminates the version with a CRLF
+		 */
+		if (ver >= 1200U) {
+			if (memcmp(buf + 3U + end, "\r\n", 2U) != 0)
+				ver = 0U;
+		} else if (ver < 1200U) {
+			if (!isblank(*(buf + 3U + end)))
+				ver = 0U;
 		}
 	}
 	return ver;
@@ -631,32 +630,27 @@ static unsigned int
 _warc_rdtyp(const char *buf, size_t bsz)
 {
 	static const char _key[] = "\r\nWARC-Type:";
-	const char *const eob = buf + bsz;
-	const char *val;
+	const char *val, *eol;
 
 	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
 		/* no bother */
 		return WT_NONE;
 	}
+	val += sizeof(_key) - 1U;
+	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL) {
+		/* no end of line */
+		return WT_NONE;
+	}
+
 	/* overread whitespace */
-	for (val += sizeof(_key) - 1U; val < eob && isspace(*val); val++);
-
-	if (val + 8U > eob) {
-		;
-	} else if (memcmp(val, "resource", 8U) == 0) {
-		return WT_RSRC;
-	} else if (memcmp(val, "warcinfo", 8U) == 0) {
-		return WT_INFO;
-	} else if (memcmp(val, "metadata", 8U) == 0) {
-		return WT_META;
-	} else if (memcmp(val, "request", 7U) == 0) {
-		return WT_REQ;
-	} else if (memcmp(val, "response", 8U) == 0) {
-		return WT_RSP;
-	} else if (memcmp(val, "conversi", 8U) == 0) {
-		return WT_CONV;
-	} else if (memcmp(val, "continua", 8U) == 0) {
-		return WT_CONT;
+	while (val < eol && isblank((unsigned char)*val))
+		++val;
+
+	if (val + 8U == eol) {
+		if (memcmp(val, "resource", 8U) == 0)
+			return WT_RSRC;
+		else if (memcmp(val, "response", 8U) == 0)
+			return WT_RSP;
 	}
 	return WT_NONE;
 }
@@ -665,34 +659,41 @@ static warc_string_t
 _warc_rduri(const char *buf, size_t bsz)
 {
 	static const char _key[] = "\r\nWARC-Target-URI:";
-	const char *const eob = buf + bsz;
-	const char *val;
-	const char *uri;
-	const char *eol;
+	const char *val, *uri, *eol, *p;
 	warc_string_t res = {0U, NULL};
 
 	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
 		/* no bother */
 		return res;
 	}
 	/* overread whitespace */
-	for (val += sizeof(_key) - 1U; val < eob && isspace(*val); val++);
+	val += sizeof(_key) - 1U;
+	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL) {
+		/* no end of line */
+		return res;
+	}
+
+	while (val < eol && isblank((unsigned char)*val))
+		++val;
 
 	/* overread URL designators */
-	if ((uri = xmemmem(val, eob - val, "://", 3U)) == NULL) {
+	if ((uri = xmemmem(val, eol - val, "://", 3U)) == NULL) {
 		/* not touching that! */
 		return res;
-	} else if ((eol = memchr(uri, '\n', eob - uri)) == NULL) {
-		/* no end of line? :O */
-		return res;
 	}
 
-	/* massage uri to point to after :// */
+	/* spaces inside uri are not allowed, CRLF should follow */
+	for (p = val; p < eol; p++) {
+		if (isspace(*p))
+			return res;
+	}
+
+	/* there must be at least space for ftp */
+	if (uri < (val + 3U))
+		return res;
+
+	/* move uri to point to after :// */
 	uri += 3U;
-	/* also massage eol to point to the first whitespace
-	 * after the last non-whitespace character before
-	 * the end of the line */
-	for (; eol > uri && isspace(eol[-1]); eol--);
 
 	/* now then, inspect the URI */
 	if (memcmp(val, "file", 4U) == 0) {
@@ -715,44 +716,58 @@ static ssize_t
 _warc_rdlen(const char *buf, size_t bsz)
 {
 	static const char _key[] = "\r\nContent-Length:";
-	const char *val;
+	const char *val, *eol;
 	char *on = NULL;
 	long int len;
 
 	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
 		/* no bother */
 		return -1;
 	}
-
-	/* strtol kindly overreads whitespace for us, so use that */
 	val += sizeof(_key) - 1U;
+	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL) {
+		/* no end of line */
+		return -1;
+	}
+
+	/* skip leading whitespace */
+	while (val < eol && isblank(*val))
+		val++;
+	/* there must be at least one digit */
+	if (!isdigit(*val))
+		return -1;
 	len = strtol(val, &on, 10);
-	if (on == NULL || !isspace(*on)) {
-		/* hm, can we trust that number?  Best not. */
+	if (on != eol) {
+		/* line must end here */
 		return -1;
 	}
+
 	return (size_t)len;
 }
 
 static time_t
 _warc_rdrtm(const char *buf, size_t bsz)
 {
 	static const char _key[] = "\r\nWARC-Date:";
-	const char *val;
+	const char *val, *eol;
 	char *on = NULL;
 	time_t res;
 
 	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
 		/* no bother */
 		return (time_t)-1;
 	}
+	val += sizeof(_key) - 1U;
+	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL ) {
+		/* no end of line */
+		return -1;
+	}
 
 	/* xstrpisotime() kindly overreads whitespace for us, so use that */
-	val += sizeof(_key) - 1U;
 	res = xstrpisotime(val, &on);
-	if (on == NULL || !isspace(*on)) {
-		/* hm, can we trust that number?  Best not. */
-		return (time_t)-1;
+	if (on != eol) {
+		/* line must end here */
+		return -1;
 	}
 	return res;
 }
@@ -761,21 +776,25 @@ static time_t
 _warc_rdmtm(const char *buf, size_t bsz)
 {
 	static const char _key[] = "\r\nLast-Modified:";
-	const char *val;
+	const char *val, *eol;
 	char *on = NULL;
 	time_t res;
 
 	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
 		/* no bother */
 		return (time_t)-1;
 	}
+	val += sizeof(_key) - 1U;
+	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL ) {
+		/* no end of line */
+		return -1;
+	}
 
 	/* xstrpisotime() kindly overreads whitespace for us, so use that */
-	val += sizeof(_key) - 1U;
 	res = xstrpisotime(val, &on);
-	if (on == NULL || !isspace(*on)) {
-		/* hm, can we trust that number?  Best not. */
-		return (time_t)-1;
+	if (on != eol) {
+		/* line must end here */
+		return -1;
 	}
 	return res;
 }
@@ -792,4 +811,12 @@ _warc_find_eoh(const char *buf, size_t bsz)
 	return hit;
 }
 
+static const char*
+_warc_find_eol(const char *buf, size_t bsz)
+{
+	static const char _marker[] = "\r\n";
+	const char *hit = xmemmem(buf, bsz, _marker, sizeof(_marker) - 1U);
+
+	return hit;
+}
 /* archive_read_support_format_warc.c ends here */