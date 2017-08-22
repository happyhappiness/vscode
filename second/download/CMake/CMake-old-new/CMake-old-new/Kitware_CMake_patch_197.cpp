@@ -139,16 +139,19 @@ get_time_t_max(void)
 #if defined(TIME_T_MAX)
 	return TIME_T_MAX;
 #else
-	static time_t t;
-	time_t a;
-	if (t == 0) {
-		a = 1;
-		while (a > t) {
-			t = a;
-			a = a * 2 + 1;
-		}
+	/* ISO C allows time_t to be a floating-point type,
+	   but POSIX requires an integer type.  The following
+	   should work on any system that follows the POSIX
+	   conventions. */
+	if (((time_t)0) < ((time_t)-1)) {
+		/* Time_t is unsigned */
+		return (~(time_t)0);
+	} else {
+		/* Time_t is signed. */
+		const uintmax_t max_unsigned_time_t = (uintmax_t)(~(time_t)0);
+		const uintmax_t max_signed_time_t = max_unsigned_time_t >> 1;
+		return (time_t)max_signed_time_t;
 	}
-	return t;
 #endif
 }
 
@@ -158,20 +161,16 @@ get_time_t_min(void)
 #if defined(TIME_T_MIN)
 	return TIME_T_MIN;
 #else
-	/* 't' will hold the minimum value, which will be zero (if
-	 * time_t is unsigned) or -2^n (if time_t is signed). */
-	static int computed;
-	static time_t t;
-	time_t a;
-	if (computed == 0) {
-		a = (time_t)-1;
-		while (a < t) {
-			t = a;
-			a = a * 2;
-		}			
-		computed = 1;
+	if (((time_t)0) < ((time_t)-1)) {
+		/* Time_t is unsigned */
+		return (time_t)0;
+	} else {
+		/* Time_t is signed. */
+		const uintmax_t max_unsigned_time_t = (uintmax_t)(~(time_t)0);
+		const uintmax_t max_signed_time_t = max_unsigned_time_t >> 1;
+		const intmax_t min_signed_time_t = (intmax_t)~max_signed_time_t;
+		return (time_t)min_signed_time_t;
 	}
-	return t;
 #endif
 }
 
@@ -532,32 +531,34 @@ bid_entry(const char *p, ssize_t len, ssize_t nl, int *last_is_path)
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* E0 - EF */
 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F0 - FF */
 	};
-	ssize_t ll = len;
+	ssize_t ll;
 	const char *pp = p;
+	const char * const pp_end = pp + len;
 
 	*last_is_path = 0;
 	/*
 	 * Skip the path-name which is quoted.
 	 */
-	while (ll > 0 && *pp != ' ' &&*pp != '\t' && *pp != '\r' &&
-	    *pp != '\n') {
+	for (;pp < pp_end; ++pp) {
 		if (!safe_char[*(const unsigned char *)pp]) {
-			f = 0;
+			if (*pp != ' ' && *pp != '\t' && *pp != '\r'
+			    && *pp != '\n')
+				f = 0;
 			break;
 		}
-		++pp;
-		--ll;
-		++f;
+		f = 1;
 	}
+	ll = pp_end - pp;
+
 	/* If a path-name was not found at the first, try to check
-	 * a mtree format ``NetBSD's mtree -D'' creates, which
-	 * places the path-name at the last. */
+	 * a mtree format(a.k.a form D) ``NetBSD's mtree -D'' creates,
+	 * which places the path-name at the last. */
 	if (f == 0) {
 		const char *pb = p + len - nl;
 		int name_len = 0;
 		int slash;
 
-		/* Do not accept multi lines for form D. */
+		/* The form D accepts only a single line for an entry. */
 		if (pb-2 >= p &&
 		    pb[-1] == '\\' && (pb[-2] == ' ' || pb[-2] == '\t'))
 			return (-1);
@@ -1056,7 +1057,8 @@ read_header(struct archive_read *a, struct archive_entry *entry)
 		}
 		if (!mtree->this_entry->used) {
 			use_next = 0;
-			r = parse_file(a, entry, mtree, mtree->this_entry, &use_next);
+			r = parse_file(a, entry, mtree, mtree->this_entry,
+				&use_next);
 			if (use_next == 0)
 				return (r);
 		}
@@ -1151,8 +1153,8 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 			mtree->fd = open(path, O_RDONLY | O_BINARY | O_CLOEXEC);
 			__archive_ensure_cloexec_flag(mtree->fd);
 			if (mtree->fd == -1 &&
-					(errno != ENOENT ||
-					 archive_strlen(&mtree->contents_name) > 0)) {
+				(errno != ENOENT ||
+				 archive_strlen(&mtree->contents_name) > 0)) {
 				archive_set_error(&a->archive, errno,
 						"Can't open %s", path);
 				r = ARCHIVE_WARN;
@@ -1175,76 +1177,79 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 		}
 
 		/*
-		 * Check for a mismatch between the type in the specification and
-		 * the type of the contents object on disk.
+		 * Check for a mismatch between the type in the specification
+		 * and the type of the contents object on disk.
 		 */
 		if (st != NULL) {
-			if (
-					((st->st_mode & S_IFMT) == S_IFREG &&
-					 archive_entry_filetype(entry) == AE_IFREG)
+			if (((st->st_mode & S_IFMT) == S_IFREG &&
+			      archive_entry_filetype(entry) == AE_IFREG)
 #ifdef S_IFLNK
-					|| ((st->st_mode & S_IFMT) == S_IFLNK &&
-						archive_entry_filetype(entry) == AE_IFLNK)
+			  ||((st->st_mode & S_IFMT) == S_IFLNK &&
+			      archive_entry_filetype(entry) == AE_IFLNK)
 #endif
 #ifdef S_IFSOCK
-					|| ((st->st_mode & S_IFSOCK) == S_IFSOCK &&
-						archive_entry_filetype(entry) == AE_IFSOCK)
+			  ||((st->st_mode & S_IFSOCK) == S_IFSOCK &&
+			      archive_entry_filetype(entry) == AE_IFSOCK)
 #endif
 #ifdef S_IFCHR
-					|| ((st->st_mode & S_IFMT) == S_IFCHR &&
-						archive_entry_filetype(entry) == AE_IFCHR)
+			  ||((st->st_mode & S_IFMT) == S_IFCHR &&
+			      archive_entry_filetype(entry) == AE_IFCHR)
 #endif
 #ifdef S_IFBLK
-					|| ((st->st_mode & S_IFMT) == S_IFBLK &&
-						archive_entry_filetype(entry) == AE_IFBLK)
+			  ||((st->st_mode & S_IFMT) == S_IFBLK &&
+			      archive_entry_filetype(entry) == AE_IFBLK)
 #endif
-					|| ((st->st_mode & S_IFMT) == S_IFDIR &&
-						archive_entry_filetype(entry) == AE_IFDIR)
+			  ||((st->st_mode & S_IFMT) == S_IFDIR &&
+			      archive_entry_filetype(entry) == AE_IFDIR)
 #ifdef S_IFIFO
-					|| ((st->st_mode & S_IFMT) == S_IFIFO &&
-							archive_entry_filetype(entry) == AE_IFIFO)
+			  ||((st->st_mode & S_IFMT) == S_IFIFO &&
+			      archive_entry_filetype(entry) == AE_IFIFO)
 #endif
-					) {
-						/* Types match. */
-					} else {
-						/* Types don't match; bail out gracefully. */
-						if (mtree->fd >= 0)
-							close(mtree->fd);
-						mtree->fd = -1;
-						if (parsed_kws & MTREE_HAS_OPTIONAL) {
-							/* It's not an error for an optional entry
-							   to not match disk. */
-							*use_next = 1;
-						} else if (r == ARCHIVE_OK) {
-							archive_set_error(&a->archive,
-									ARCHIVE_ERRNO_MISC,
-									"mtree specification has different type for %s",
-									archive_entry_pathname(entry));
-							r = ARCHIVE_WARN;
-						}
-						return r;
-					}
+			) {
+				/* Types match. */
+			} else {
+				/* Types don't match; bail out gracefully. */
+				if (mtree->fd >= 0)
+					close(mtree->fd);
+				mtree->fd = -1;
+				if (parsed_kws & MTREE_HAS_OPTIONAL) {
+					/* It's not an error for an optional
+					 * entry to not match disk. */
+					*use_next = 1;
+				} else if (r == ARCHIVE_OK) {
+					archive_set_error(&a->archive,
+					    ARCHIVE_ERRNO_MISC,
+					    "mtree specification has different"
+					    " type for %s",
+					    archive_entry_pathname(entry));
+					r = ARCHIVE_WARN;
+				}
+				return (r);
+			}
 		}
 
 		/*
-		 * If there is a contents file on disk, pick some of the metadata
-		 * from that file.  For most of these, we only set it from the contents
-		 * if it wasn't already parsed from the specification.
+		 * If there is a contents file on disk, pick some of the
+		 * metadata from that file.  For most of these, we only
+		 * set it from the contents if it wasn't already parsed
+		 * from the specification.
 		 */
 		if (st != NULL) {
 			if (((parsed_kws & MTREE_HAS_DEVICE) == 0 ||
-						(parsed_kws & MTREE_HAS_NOCHANGE) != 0) &&
-					(archive_entry_filetype(entry) == AE_IFCHR ||
-					 archive_entry_filetype(entry) == AE_IFBLK))
+				(parsed_kws & MTREE_HAS_NOCHANGE) != 0) &&
+				(archive_entry_filetype(entry) == AE_IFCHR ||
+				 archive_entry_filetype(entry) == AE_IFBLK))
 				archive_entry_set_rdev(entry, st->st_rdev);
-			if ((parsed_kws & (MTREE_HAS_GID | MTREE_HAS_GNAME)) == 0 ||
-					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+			if ((parsed_kws & (MTREE_HAS_GID | MTREE_HAS_GNAME))
+				== 0 ||
+			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 				archive_entry_set_gid(entry, st->st_gid);
-			if ((parsed_kws & (MTREE_HAS_UID | MTREE_HAS_UNAME)) == 0 ||
-					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+			if ((parsed_kws & (MTREE_HAS_UID | MTREE_HAS_UNAME))
+				== 0 ||
+			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 				archive_entry_set_uid(entry, st->st_uid);
 			if ((parsed_kws & MTREE_HAS_MTIME) == 0 ||
-					(parsed_kws & MTREE_HAS_NOCHANGE) != 0) {
+			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0) {
 #if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC
 				archive_entry_set_mtime(entry, st->st_mtime,
 						st->st_mtimespec.tv_nsec);
@@ -1265,23 +1270,24 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 #endif
 			}
 			if ((parsed_kws & MTREE_HAS_NLINK) == 0 ||
-					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 				archive_entry_set_nlink(entry, st->st_nlink);
 			if ((parsed_kws & MTREE_HAS_PERM) == 0 ||
-					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 				archive_entry_set_perm(entry, st->st_mode);
 			if ((parsed_kws & MTREE_HAS_SIZE) == 0 ||
-					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
 				archive_entry_set_size(entry, st->st_size);
 			archive_entry_set_ino(entry, st->st_ino);
 			archive_entry_set_dev(entry, st->st_dev);
 
-			archive_entry_linkify(mtree->resolver, &entry, &sparse_entry);
+			archive_entry_linkify(mtree->resolver, &entry,
+				&sparse_entry);
 		} else if (parsed_kws & MTREE_HAS_OPTIONAL) {
 			/*
 			 * Couldn't open the entry, stat it or the on-disk type
-			 * didn't match.  If this entry is optional, just ignore it
-			 * and read the next header entry.
+			 * didn't match.  If this entry is optional, just
+			 * ignore it and read the next header entry.
 			 */
 			*use_next = 1;
 			return ARCHIVE_OK;
@@ -1370,7 +1376,7 @@ parse_device(dev_t *pdev, struct archive *a, char *val)
 				    "Missing number");
 				return ARCHIVE_WARN;
 			}
-			numbers[argc++] = mtree_atol(&p);
+			numbers[argc++] = (unsigned long)mtree_atol(&p);
 			if (argc > MAX_PACK_ARGS) {
 				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
 				    "Too many arguments");
@@ -1583,32 +1589,38 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 				}
 			case 'c':
 				if (strcmp(val, "char") == 0) {
-					archive_entry_set_filetype(entry, AE_IFCHR);
+					archive_entry_set_filetype(entry,
+						AE_IFCHR);
 					break;
 				}
 			case 'd':
 				if (strcmp(val, "dir") == 0) {
-					archive_entry_set_filetype(entry, AE_IFDIR);
+					archive_entry_set_filetype(entry,
+						AE_IFDIR);
 					break;
 				}
 			case 'f':
 				if (strcmp(val, "fifo") == 0) {
-					archive_entry_set_filetype(entry, AE_IFIFO);
+					archive_entry_set_filetype(entry,
+						AE_IFIFO);
 					break;
 				}
 				if (strcmp(val, "file") == 0) {
-					archive_entry_set_filetype(entry, AE_IFREG);
+					archive_entry_set_filetype(entry,
+						AE_IFREG);
 					break;
 				}
 			case 'l':
 				if (strcmp(val, "link") == 0) {
-					archive_entry_set_filetype(entry, AE_IFLNK);
+					archive_entry_set_filetype(entry,
+						AE_IFLNK);
 					break;
 				}
 			default:
 				archive_set_error(&a->archive,
 				    ARCHIVE_ERRNO_FILE_FORMAT,
-				    "Unrecognized file type \"%s\"; assuming \"file\"", val);
+				    "Unrecognized file type \"%s\"; "
+				    "assuming \"file\"", val);
 				archive_entry_set_filetype(entry, AE_IFREG);
 				return (ARCHIVE_WARN);
 			}
@@ -1635,7 +1647,8 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 }
 
 static int
-read_data(struct archive_read *a, const void **buff, size_t *size, int64_t *offset)
+read_data(struct archive_read *a, const void **buff, size_t *size,
+    int64_t *offset)
 {
 	size_t bytes_to_read;
 	ssize_t bytes_read;
@@ -1761,6 +1774,10 @@ parse_escapes(char *src, struct mtree_entry *mentry)
 				c = '\v';
 				++src;
 				break;
+			case '\\':
+				c = '\\';
+				++src;
+				break;
 			}
 		}
 		*dest++ = c;
@@ -1898,14 +1915,14 @@ mtree_atol(char **p)
  * point to first character of line.
  */
 static ssize_t
-readline(struct archive_read *a, struct mtree *mtree, char **start, ssize_t limit)
+readline(struct archive_read *a, struct mtree *mtree, char **start,
+    ssize_t limit)
 {
 	ssize_t bytes_read;
 	ssize_t total_size = 0;
 	ssize_t find_off = 0;
 	const void *t;
-	const char *s;
-	void *p;
+	void *nl;
 	char *u;
 
 	/* Accumulate line in a line buffer. */
@@ -1916,11 +1933,10 @@ readline(struct archive_read *a, struct mtree *mtree, char **start, ssize_t limi
 			return (0);
 		if (bytes_read < 0)
 			return (ARCHIVE_FATAL);
-		s = t;  /* Start of line? */
-		p = memchr(t, '\n', bytes_read);
-		/* If we found '\n', trim the read. */
-		if (p != NULL) {
-			bytes_read = 1 + ((const char *)p) - s;
+		nl = memchr(t, '\n', bytes_read);
+		/* If we found '\n', trim the read to end exactly there. */
+		if (nl != NULL) {
+			bytes_read = ((const char *)nl) - ((const char *)t) + 1;
 		}
 		if (total_size + bytes_read + 1 > limit) {
 			archive_set_error(&a->archive,
@@ -1934,38 +1950,34 @@ readline(struct archive_read *a, struct mtree *mtree, char **start, ssize_t limi
 			    "Can't allocate working buffer");
 			return (ARCHIVE_FATAL);
 		}
+		/* Append new bytes to string. */
 		memcpy(mtree->line.s + total_size, t, bytes_read);
 		__archive_read_consume(a, bytes_read);
 		total_size += bytes_read;
-		/* Null terminate. */
 		mtree->line.s[total_size] = '\0';
-		/* If we found an unescaped '\n', clean up and return. */
+
 		for (u = mtree->line.s + find_off; *u; ++u) {
 			if (u[0] == '\n') {
+				/* Ends with unescaped newline. */
 				*start = mtree->line.s;
 				return total_size;
-			}
-			if (u[0] == '#') {
-				if (p == NULL)
+			} else if (u[0] == '#') {
+				/* Ends with comment sequence #...\n */
+				if (nl == NULL) {
+					/* But we've not found the \n yet */
 					break;
-				*start = mtree->line.s;
-				return total_size;
-			}
-			if (u[0] != '\\')
-				continue;
-			if (u[1] == '\\') {
-				++u;
-				continue;
-			}
-			if (u[1] == '\n') {
-				memmove(u, u + 1,
-				    total_size - (u - mtree->line.s) + 1);
-				--total_size;
-				++u;
-				break;
+				}
+			} else if (u[0] == '\\') {
+				if (u[1] == '\n') {
+					/* Trim escaped newline. */
+					total_size -= 2;
+					mtree->line.s[total_size] = '\0';
+					break;
+				} else if (u[1] != '\0') {
+					/* Skip the two-char escape sequence */
+					++u;
+				}
 			}
-			if (u[1] == '\0')
-				break;
 		}
 		find_off = u - mtree->line.s;
 	}