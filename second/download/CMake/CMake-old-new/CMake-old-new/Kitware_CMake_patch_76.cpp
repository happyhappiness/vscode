@@ -110,6 +110,18 @@ __FBSDID("$FreeBSD$");
 #include <sys/fcntl1.h>
 #endif
 
+/*
+ * Macro to cast st_mtime and time_t to an int64 so that 2 numbers can reliably be compared.
+ *
+ * It assumes that the input is an integer type of no more than 64 bits.
+ * If the number is less than zero, t must be a signed type, so it fits in
+ * int64_t. Otherwise, it's a nonnegative value so we can cast it to uint64_t
+ * without loss. But it could be a large unsigned value, so we have to clip it
+ * to INT64_MAX.*
+ */
+#define to_int64_time(t) \
+   ((t) < 0 ? (int64_t)(t) : (uint64_t)(t) > (uint64_t)INT64_MAX ? INT64_MAX : (int64_t)(t))
+
 #if __APPLE__
 #include <TargetConditionals.h>
 #if TARGET_OS_MAC && !TARGET_OS_EMBEDDED && HAVE_QUARANTINE_H
@@ -140,7 +152,17 @@ __FBSDID("$FreeBSD$");
 #define O_BINARY 0
 #endif
 #ifndef O_CLOEXEC
-#define O_CLOEXEC	0
+#define O_CLOEXEC 0
+#endif
+
+/* Ignore non-int O_NOFOLLOW constant. */
+/* gnulib's fcntl.h does this on AIX, but it seems practical everywhere */
+#if defined O_NOFOLLOW && !(INT_MIN <= O_NOFOLLOW && O_NOFOLLOW <= INT_MAX)
+#undef O_NOFOLLOW
+#endif
+
+#ifndef O_NOFOLLOW
+#define O_NOFOLLOW 0
 #endif
 
 struct fixup_entry {
@@ -298,7 +320,7 @@ struct archive_write_disk {
 #define	MAXIMUM_DIR_MODE 0775
 
 /*
- * Maxinum uncompressed size of a decmpfs block.
+ * Maximum uncompressed size of a decmpfs block.
  */
 #define MAX_DECMPFS_BLOCK_SIZE	(64 * 1024)
 /*
@@ -313,7 +335,7 @@ struct archive_write_disk {
 #define RSRC_F_SIZE	50	/* Size of Resource fork footer. */
 /* Size to write compressed data to resource fork. */
 #define COMPRESSED_W_SIZE	(64 * 1024)
-/* decmpfs difinitions. */
+/* decmpfs definitions. */
 #define MAX_DECMPFS_XATTR_SIZE		3802
 #ifndef DECMPFS_XATTR_NAME
 #define DECMPFS_XATTR_NAME		"com.apple.decmpfs"
@@ -326,12 +348,19 @@ struct archive_write_disk {
 
 #define HFS_BLOCKS(s)	((s) >> 12)
 
+static void	fsobj_error(int *, struct archive_string *, int, const char *,
+		    const char *);
+static int	check_symlinks_fsobj(char *, int *, struct archive_string *,
+		    int);
 static int	check_symlinks(struct archive_write_disk *);
 static int	create_filesystem_object(struct archive_write_disk *);
-static struct fixup_entry *current_fixup(struct archive_write_disk *, const char *pathname);
+static struct fixup_entry *current_fixup(struct archive_write_disk *,
+		    const char *pathname);
 #if defined(HAVE_FCHDIR) && defined(PATH_MAX)
 static void	edit_deep_directories(struct archive_write_disk *ad);
 #endif
+static int	cleanup_pathname_fsobj(char *, int *, struct archive_string *,
+		    int);
 static int	cleanup_pathname(struct archive_write_disk *);
 static int	create_dir(struct archive_write_disk *, char *);
 static int	create_parent_dir(struct archive_write_disk *, char *);
@@ -362,11 +391,14 @@ static struct archive_vtable *archive_write_disk_vtable(void);
 
 static int	_archive_write_disk_close(struct archive *);
 static int	_archive_write_disk_free(struct archive *);
-static int	_archive_write_disk_header(struct archive *, struct archive_entry *);
+static int	_archive_write_disk_header(struct archive *,
+		    struct archive_entry *);
 static int64_t	_archive_write_disk_filter_bytes(struct archive *, int);
 static int	_archive_write_disk_finish_entry(struct archive *);
-static ssize_t	_archive_write_disk_data(struct archive *, const void *, size_t);
-static ssize_t	_archive_write_disk_data_block(struct archive *, const void *, size_t, int64_t);
+static ssize_t	_archive_write_disk_data(struct archive *, const void *,
+		    size_t);
+static ssize_t	_archive_write_disk_data_block(struct archive *, const void *,
+		    size_t, int64_t);
 
 static int
 lazy_stat(struct archive_write_disk *a)
@@ -612,9 +644,9 @@ _archive_write_disk_header(struct archive *_a, struct archive_entry *entry)
 		/*
 		 * NOTE: UF_COMPRESSED is ignored even if the filesystem
 		 * supports HFS+ Compression because the file should
-		 * have at least an extended attriute "com.apple.decmpfs"
+		 * have at least an extended attribute "com.apple.decmpfs"
 		 * before the flag is set to indicate that the file have
-		 * been compressed. If hte filesystem does not support
+		 * been compressed. If the filesystem does not support
 		 * HFS+ Compression the system call will fail.
 		 */
 		if (a->fd < 0 || fchflags(a->fd, UF_COMPRESSED) != 0)
@@ -637,7 +669,8 @@ _archive_write_disk_header(struct archive *_a, struct archive_entry *entry)
 	if (a->restore_pwd >= 0) {
 		r = fchdir(a->restore_pwd);
 		if (r != 0) {
-			archive_set_error(&a->archive, errno, "chdir() failure");
+			archive_set_error(&a->archive, errno,
+			    "chdir() failure");
 			ret = ARCHIVE_FATAL;
 		}
 		close(a->restore_pwd);
@@ -685,7 +718,8 @@ _archive_write_disk_header(struct archive *_a, struct archive_entry *entry)
 		}
 		if (archive_entry_birthtime_is_set(entry)) {
 			fe->birthtime = archive_entry_birthtime(entry);
-			fe->birthtime_nanos = archive_entry_birthtime_nsec(entry);
+			fe->birthtime_nanos = archive_entry_birthtime_nsec(
+			    entry);
 		} else {
 			/* If birthtime is unset, use mtime. */
 			fe->birthtime = fe->mtime;
@@ -711,7 +745,8 @@ _archive_write_disk_header(struct archive *_a, struct archive_entry *entry)
 				return (ARCHIVE_FATAL);
 			fe->mac_metadata = malloc(metadata_size);
 			if (fe->mac_metadata != NULL) {
-				memcpy(fe->mac_metadata, metadata, metadata_size);
+				memcpy(fe->mac_metadata, metadata,
+				    metadata_size);
 				fe->mac_metadata_size = metadata_size;
 				fe->fixup |= TODO_MAC_METADATA;
 			}
@@ -1224,7 +1259,7 @@ hfs_drive_compressor(struct archive_write_disk *a, const char *buff,
 		ret = hfs_write_compressed_data(a, bytes_used + rsrc_size);
 		a->compressed_buffer_remaining = a->compressed_buffer_size;
 
-		/* If the compressed size is not enouph smaller than
+		/* If the compressed size is not enough smaller than
 		 * the uncompressed size. cancel HFS+ compression.
 		 * TODO: study a behavior of ditto utility and improve
 		 * the condition to fall back into no HFS+ compression. */
@@ -1329,7 +1364,7 @@ hfs_write_decmpfs_block(struct archive_write_disk *a, const char *buff,
 		    (uint32_t *)(a->resource_fork + RSRC_H_SIZE);
 		/* Set the block count to the resource fork. */
 		archive_le32enc(a->decmpfs_block_info++, block_count);
-		/* Get the position where we are goint to set compressed
+		/* Get the position where we are going to set compressed
 		 * data. */
 		a->compressed_rsrc_position =
 		    RSRC_H_SIZE + 4 + (block_count * 8);
@@ -1402,7 +1437,7 @@ hfs_write_data_block(struct archive_write_disk *a, const char *buff,
 		bytes_to_write = size;
 		/* Seek if necessary to the specified offset. */
 		if (a->offset < a->fd_offset) {
-			/* Can't support backword move. */
+			/* Can't support backward move. */
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "Seek failed");
 			return (ARCHIVE_FATAL);
@@ -1468,7 +1503,8 @@ _archive_write_disk_data_block(struct archive *_a,
 		return (r);
 	if ((size_t)r < size) {
 		archive_set_error(&a->archive, 0,
-		    "Too much data: Truncating file at %ju bytes", (uintmax_t)a->filesize);
+		    "Too much data: Truncating file at %ju bytes",
+		    (uintmax_t)a->filesize);
 		return (ARCHIVE_WARN);
 	}
 #if ARCHIVE_VERSION_NUMBER < 3999000
@@ -1666,10 +1702,25 @@ _archive_write_disk_finish_entry(struct archive *_a)
 	 * ACLs that prevent attribute changes (including time).
 	 */
 	if (a->todo & TODO_ACLS) {
-		int r2 = archive_write_disk_set_acls(&a->archive, a->fd,
-				  archive_entry_pathname(a->entry),
-				  archive_entry_acl(a->entry));
+		int r2;
+#ifdef HAVE_DARWIN_ACL
+		/*
+		 * On Mac OS, platform ACLs are stored also in mac_metadata by
+		 * the operating system. If mac_metadata is present it takes
+		 * precedence and we skip extracting libarchive NFSv4 ACLs
+		 */
+		const void *metadata;
+		size_t metadata_size;
+		metadata = archive_entry_mac_metadata(a->entry, &metadata_size);
+		if (metadata == NULL || metadata_size == 0) {
+#endif
+		r2 = archive_write_disk_set_acls(&a->archive, a->fd,
+		    archive_entry_pathname(a->entry),
+		    archive_entry_acl(a->entry));
 		if (r2 < ret) ret = r2;
+#ifdef HAVE_DARWIN_ACL
+		}
+#endif
 	}
 
 finish_metadata:
@@ -1755,10 +1806,9 @@ archive_write_disk_new(void)
 {
 	struct archive_write_disk *a;
 
-	a = (struct archive_write_disk *)malloc(sizeof(*a));
+	a = (struct archive_write_disk *)calloc(1, sizeof(*a));
 	if (a == NULL)
 		return (NULL);
-	memset(a, 0, sizeof(*a));
 	a->archive.magic = ARCHIVE_WRITE_DISK_MAGIC;
 	/* We're ready to write a header immediately. */
 	a->archive.state = ARCHIVE_STATE_HEADER;
@@ -1796,7 +1846,7 @@ edit_deep_directories(struct archive_write_disk *a)
 	char *tail = a->name;
 
 	/* If path is short, avoid the open() below. */
-	if (strlen(tail) <= PATH_MAX)
+	if (strlen(tail) < PATH_MAX)
 		return;
 
 	/* Try to record our starting dir. */
@@ -1806,7 +1856,7 @@ edit_deep_directories(struct archive_write_disk *a)
 		return;
 
 	/* As long as the path is too long... */
-	while (strlen(tail) > PATH_MAX) {
+	while (strlen(tail) >= PATH_MAX) {
 		/* Locate a dir prefix shorter than PATH_MAX. */
 		tail += PATH_MAX - 8;
 		while (tail > a->name && *tail != '/')
@@ -1993,8 +2043,9 @@ restore_entry(struct archive_write_disk *a)
 
 	if (en) {
 		/* Everything failed; give up here. */
-		archive_set_error(&a->archive, en, "Can't create '%s'",
-		    a->name);
+		if ((&a->archive)->error == NULL)
+			archive_set_error(&a->archive, en, "Can't create '%s'",
+			    a->name);
 		return (ARCHIVE_FAILED);
 	}
 
@@ -2014,6 +2065,11 @@ create_filesystem_object(struct archive_write_disk *a)
 	const char *linkname;
 	mode_t final_mode, mode;
 	int r;
+	/* these for check_symlinks_fsobj */
+	char *linkname_copy;	/* non-const copy of linkname */
+	struct stat st;
+	struct archive_string error_string;
+	int error_number;
 
 	/* We identify hard/symlinks according to the link names. */
 	/* Since link(2) and symlink(2) don't handle modes, we're done here. */
@@ -2022,6 +2078,43 @@ create_filesystem_object(struct archive_write_disk *a)
 #if !HAVE_LINK
 		return (EPERM);
 #else
+		archive_string_init(&error_string);
+		linkname_copy = strdup(linkname);
+		if (linkname_copy == NULL) {
+		    return (EPERM);
+		}
+		/*
+		 * TODO: consider using the cleaned-up path as the link
+		 * target?
+		 */
+		r = cleanup_pathname_fsobj(linkname_copy, &error_number,
+		    &error_string, a->flags);
+		if (r != ARCHIVE_OK) {
+			archive_set_error(&a->archive, error_number, "%s",
+			    error_string.s);
+			free(linkname_copy);
+			archive_string_free(&error_string);
+			/*
+			 * EPERM is more appropriate than error_number for our
+			 * callers
+			 */
+			return (EPERM);
+		}
+		r = check_symlinks_fsobj(linkname_copy, &error_number,
+		    &error_string, a->flags);
+		if (r != ARCHIVE_OK) {
+			archive_set_error(&a->archive, error_number, "%s",
+			    error_string.s);
+			free(linkname_copy);
+			archive_string_free(&error_string);
+			/*
+			 * EPERM is more appropriate than error_number for our
+			 * callers
+			 */
+			return (EPERM);
+		}
+		free(linkname_copy);
+		archive_string_free(&error_string);
 		r = link(linkname, a->name) ? errno : 0;
 		/*
 		 * New cpio and pax formats allow hardlink entries
@@ -2039,11 +2132,20 @@ create_filesystem_object(struct archive_write_disk *a)
 			a->todo = 0;
 			a->deferred = 0;
 		} else if (r == 0 && a->filesize > 0) {
-			a->fd = open(a->name,
-				     O_WRONLY | O_TRUNC | O_BINARY | O_CLOEXEC);
-			__archive_ensure_cloexec_flag(a->fd);
-			if (a->fd < 0)
+#ifdef HAVE_LSTAT
+			r = lstat(a->name, &st);
+#else
+			r = stat(a->name, &st);
+#endif
+			if (r != 0)
 				r = errno;
+			else if ((st.st_mode & AE_IFMT) == AE_IFREG) {
+				a->fd = open(a->name, O_WRONLY | O_TRUNC |
+				    O_BINARY | O_CLOEXEC | O_NOFOLLOW);
+				__archive_ensure_cloexec_flag(a->fd);
+				if (a->fd < 0)
+					r = errno;
+			}
 		}
 		return (r);
 #endif
@@ -2190,8 +2292,12 @@ _archive_write_disk_close(struct archive *_a)
 		if (p->fixup & TODO_MODE_BASE)
 			chmod(p->name, p->mode);
 		if (p->fixup & TODO_ACLS)
-			archive_write_disk_set_acls(&a->archive,
-						    -1, p->name, &p->acl);
+#ifdef HAVE_DARWIN_ACL
+			if (p->mac_metadata == NULL ||
+			    p->mac_metadata_size == 0)
+#endif
+				archive_write_disk_set_acls(&a->archive,
+				    -1, p->name, &p->acl);
 		if (p->fixup & TODO_FFLAGS)
 			set_fflags_platform(a, -1, p->name,
 			    p->mode, p->fflags_set, 0);
@@ -2351,116 +2457,283 @@ current_fixup(struct archive_write_disk *a, const char *pathname)
 	return (a->current_fixup);
 }
 
-/* TODO: Make this work. */
-/*
- * TODO: The deep-directory support bypasses this; disable deep directory
- * support if we're doing symlink checks.
- */
+/* Error helper for new *_fsobj functions */
+static void
+fsobj_error(int *a_eno, struct archive_string *a_estr,
+    int err, const char *errstr, const char *path)
+{
+	if (a_eno)
+		*a_eno = err;
+	if (a_estr)
+		archive_string_sprintf(a_estr, errstr, path);
+}
+
 /*
  * TODO: Someday, integrate this with the deep dir support; they both
  * scan the path and both can be optimized by comparing against other
  * recent paths.
  */
 /* TODO: Extend this to support symlinks on Windows Vista and later. */
+
+/*
+ * Checks the given path to see if any elements along it are symlinks.  Returns
+ * ARCHIVE_OK if there are none, otherwise puts an error in errmsg.
+ */
 static int
-check_symlinks(struct archive_write_disk *a)
+check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
+    int flags)
 {
 #if !defined(HAVE_LSTAT)
 	/* Platform doesn't have lstat, so we can't look for symlinks. */
-	(void)a; /* UNUSED */
+	(void)path; /* UNUSED */
+	(void)error_number; /* UNUSED */
+	(void)error_string; /* UNUSED */
+	(void)flags; /* UNUSED */
 	return (ARCHIVE_OK);
 #else
-	char *pn;
+	int res = ARCHIVE_OK;
+	char *tail;
+	char *head;
+	int last;
 	char c;
 	int r;
 	struct stat st;
+	int restore_pwd;
+
+	/* Nothing to do here if name is empty */
+	if(path[0] == '\0')
+	    return (ARCHIVE_OK);
 
 	/*
 	 * Guard against symlink tricks.  Reject any archive entry whose
 	 * destination would be altered by a symlink.
+	 *
+	 * Walk the filename in chunks separated by '/'.  For each segment:
+	 *  - if it doesn't exist, continue
+	 *  - if it's symlink, abort or remove it
+	 *  - if it's a directory and it's not the last chunk, cd into it
+	 * As we go:
+	 *  head points to the current (relative) path
+	 *  tail points to the temporary \0 terminating the segment we're
+	 *      currently examining
+	 *  c holds what used to be in *tail
+	 *  last is 1 if this is the last tail
 	 */
-	/* Whatever we checked last time doesn't need to be re-checked. */
-	pn = a->name;
-	if (archive_strlen(&(a->path_safe)) > 0) {
-		char *p = a->path_safe.s;
-		while ((*pn != '\0') && (*p == *pn))
-			++p, ++pn;
-	}
+	restore_pwd = open(".", O_RDONLY | O_BINARY | O_CLOEXEC);
+	__archive_ensure_cloexec_flag(restore_pwd);
+	if (restore_pwd < 0)
+		return (ARCHIVE_FATAL);
+	head = path;
+	tail = path;
+	last = 0;
+	/* TODO: reintroduce a safe cache here? */
 	/* Skip the root directory if the path is absolute. */
-	if(pn == a->name && pn[0] == '/')
-		++pn;
-	c = pn[0];
-	/* Keep going until we've checked the entire name. */
-	while (pn[0] != '\0' && (pn[0] != '/' || pn[1] != '\0')) {
+	if(tail == path && tail[0] == '/')
+		++tail;
+	/* Keep going until we've checked the entire name.
+	 * head, tail, path all alias the same string, which is
+	 * temporarily zeroed at tail, so be careful restoring the
+	 * stashed (c=tail[0]) for error messages.
+	 * Exiting the loop with break is okay; continue is not.
+	 */
+	while (!last) {
+		/*
+		 * Skip the separator we just consumed, plus any adjacent ones
+		 */
+		while (*tail == '/')
+		    ++tail;
 		/* Skip the next path element. */
-		while (*pn != '\0' && *pn != '/')
-			++pn;
-		c = pn[0];
-		pn[0] = '\0';
+		while (*tail != '\0' && *tail != '/')
+			++tail;
+		/* is this the last path component? */
+		last = (tail[0] == '\0') || (tail[0] == '/' && tail[1] == '\0');
+		/* temporarily truncate the string here */
+		c = tail[0];
+		tail[0] = '\0';
 		/* Check that we haven't hit a symlink. */
-		r = lstat(a->name, &st);
+		r = lstat(head, &st);
 		if (r != 0) {
+			tail[0] = c;
 			/* We've hit a dir that doesn't exist; stop now. */
-			if (errno == ENOENT)
+			if (errno == ENOENT) {
+				break;
+			} else {
+				/*
+				 * Treat any other error as fatal - best to be
+				 * paranoid here.
+				 * Note: This effectively disables deep
+				 * directory support when security checks are
+				 * enabled. Otherwise, very long pathnames that
+				 * trigger an error here could evade the
+				 * sandbox.
+				 * TODO: We could do better, but it would
+				 * probably require merging the symlink checks
+				 * with the deep-directory editing.
+				 */
+				fsobj_error(a_eno, a_estr, errno,
+				    "Could not stat %s", path);
+				res = ARCHIVE_FAILED;
 				break;
+			}
+		} else if (S_ISDIR(st.st_mode)) {
+			if (!last) {
+				if (chdir(head) != 0) {
+					tail[0] = c;
+					fsobj_error(a_eno, a_estr, errno,
+					    "Could not chdir %s", path);
+					res = (ARCHIVE_FATAL);
+					break;
+				}
+				/* Our view is now from inside this dir: */
+				head = tail + 1;
+			}
 		} else if (S_ISLNK(st.st_mode)) {
-			if (c == '\0') {
+			if (last) {
 				/*
 				 * Last element is symlink; remove it
 				 * so we can overwrite it with the
 				 * item being extracted.
 				 */
-				if (unlink(a->name)) {
-					archive_set_error(&a->archive, errno,
+				if (unlink(head)) {
+					tail[0] = c;
+					fsobj_error(a_eno, a_estr, errno,
 					    "Could not remove symlink %s",
-					    a->name);
-					pn[0] = c;
-					return (ARCHIVE_FAILED);
+					    path);
+					res = ARCHIVE_FAILED;
+					break;
 				}
-				a->pst = NULL;
 				/*
 				 * Even if we did remove it, a warning
 				 * is in order.  The warning is silly,
 				 * though, if we're just replacing one
 				 * symlink with another symlink.
 				 */
-				if (!S_ISLNK(a->mode)) {
-					archive_set_error(&a->archive, 0,
-					    "Removing symlink %s",
-					    a->name);
+				tail[0] = c;
+				/*
+				 * FIXME:  not sure how important this is to
+				 * restore
+				 */
+				/*
+				if (!S_ISLNK(path)) {
+					fsobj_error(a_eno, a_estr, 0,
+					    "Removing symlink %s", path);
 				}
+				*/
 				/* Symlink gone.  No more problem! */
-				pn[0] = c;
-				return (0);
-			} else if (a->flags & ARCHIVE_EXTRACT_UNLINK) {
+				res = ARCHIVE_OK;
+				break;
+			} else if (flags & ARCHIVE_EXTRACT_UNLINK) {
 				/* User asked us to remove problems. */
-				if (unlink(a->name) != 0) {
-					archive_set_error(&a->archive, 0,
-					    "Cannot remove intervening symlink %s",
-					    a->name);
-					pn[0] = c;
-					return (ARCHIVE_FAILED);
+				if (unlink(head) != 0) {
+					tail[0] = c;
+					fsobj_error(a_eno, a_estr, 0,
+					    "Cannot remove intervening "
+					    "symlink %s", path);
+					res = ARCHIVE_FAILED;
+					break;
+				}
+				tail[0] = c;
+			} else if ((flags &
+			    ARCHIVE_EXTRACT_SECURE_SYMLINKS) == 0) {
+				/*
+				 * We are not the last element and we want to
+				 * follow symlinks if they are a directory.
+				 * 
+				 * This is needed to extract hardlinks over
+				 * symlinks.
+				 */
+				r = stat(head, &st);
+				if (r != 0) {
+					tail[0] = c;
+					if (errno == ENOENT) {
+						break;
+					} else {
+						fsobj_error(a_eno, a_estr,
+						    errno,
+						    "Could not stat %s", path);
+						res = (ARCHIVE_FAILED);
+						break;
+					}
+				} else if (S_ISDIR(st.st_mode)) {
+					if (chdir(head) != 0) {
+						tail[0] = c;
+						fsobj_error(a_eno, a_estr,
+						    errno,
+						    "Could not chdir %s", path);
+						res = (ARCHIVE_FATAL);
+						break;
+					}
+					/*
+					 * Our view is now from inside
+					 * this dir:
+					 */
+					head = tail + 1;
+				} else {
+					tail[0] = c;
+					fsobj_error(a_eno, a_estr, 0,
+					    "Cannot extract through "
+					    "symlink %s", path);
+					res = ARCHIVE_FAILED;
+					break;
 				}
-				a->pst = NULL;
 			} else {
-				archive_set_error(&a->archive, 0,
-				    "Cannot extract through symlink %s",
-				    a->name);
-				pn[0] = c;
-				return (ARCHIVE_FAILED);
+				tail[0] = c;
+				fsobj_error(a_eno, a_estr, 0,
+				    "Cannot extract through symlink %s", path);
+				res = ARCHIVE_FAILED;
+				break;
 			}
 		}
-		pn[0] = c;
-		if (pn[0] != '\0')
-			pn++; /* Advance to the next segment. */
+		/* be sure to always maintain this */
+		tail[0] = c;
+		if (tail[0] != '\0')
+			tail++; /* Advance to the next segment. */
+	}
+	/* Catches loop exits via break */
+	tail[0] = c;
+#ifdef HAVE_FCHDIR
+	/* If we changed directory above, restore it here. */
+	if (restore_pwd >= 0) {
+		r = fchdir(restore_pwd);
+		if (r != 0) {
+			fsobj_error(a_eno, a_estr, errno,
+			    "chdir() failure", "");
+		}
+		close(restore_pwd);
+		restore_pwd = -1;
+		if (r != 0) {
+			res = (ARCHIVE_FATAL);
+		}
 	}
-	pn[0] = c;
-	/* We've checked and/or cleaned the whole path, so remember it. */
-	archive_strcpy(&a->path_safe, a->name);
-	return (ARCHIVE_OK);
+#endif
+	/* TODO: reintroduce a safe cache here? */
+	return res;
 #endif
 }
 
+/*
+ * Check a->name for symlinks, returning ARCHIVE_OK if its clean, otherwise
+ * calls archive_set_error and returns ARCHIVE_{FATAL,FAILED}
+ */
+static int
+check_symlinks(struct archive_write_disk *a)
+{
+	struct archive_string error_string;
+	int error_number;
+	int rc;
+	archive_string_init(&error_string);
+	rc = check_symlinks_fsobj(a->name, &error_number, &error_string,
+	    a->flags);
+	if (rc != ARCHIVE_OK) {
+		archive_set_error(&a->archive, error_number, "%s",
+		    error_string.s);
+	}
+	archive_string_free(&error_string);
+	a->pst = NULL;	/* to be safe */
+	return rc;
+}
+
+
 #if defined(__CYGWIN__)
 /*
  * 1. Convert a path separator from '\' to '/' .
@@ -2471,7 +2744,7 @@ check_symlinks(struct archive_write_disk *a)
  * See also : http://msdn.microsoft.com/en-us/library/aa365247.aspx
  */
 static void
-cleanup_pathname_win(struct archive_write_disk *a)
+cleanup_pathname_win(char *path)
 {
 	wchar_t wc;
 	char *p;
@@ -2482,7 +2755,7 @@ cleanup_pathname_win(struct archive_write_disk *a)
 	mb = 0;
 	complete = 1;
 	utf8 = (strcmp(nl_langinfo(CODESET), "UTF-8") == 0)? 1: 0;
-	for (p = a->name; *p != '\0'; p++) {
+	for (p = path; *p != '\0'; p++) {
 		++alen;
 		if (*p == '\\') {
 			/* If previous byte is smaller than 128,
@@ -2507,7 +2780,7 @@ cleanup_pathname_win(struct archive_write_disk *a)
 	/*
 	 * Convert path separator in wide-character.
 	 */
-	p = a->name;
+	p = path;
 	while (*p != '\0' && alen) {
 		l = mbtowc(&wc, p, alen);
 		if (l == (size_t)-1) {
@@ -2534,26 +2807,27 @@ cleanup_pathname_win(struct archive_write_disk *a)
  * is set) if the path is absolute.
  */
 static int
-cleanup_pathname(struct archive_write_disk *a)
+cleanup_pathname_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
+    int flags)
 {
 	char *dest, *src;
 	char separator = '\0';
 
-	dest = src = a->name;
+	dest = src = path;
 	if (*src == '\0') {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Invalid empty pathname");
+		fsobj_error(a_eno, a_estr, ARCHIVE_ERRNO_MISC,
+		    "Invalid empty ", "pathname");
 		return (ARCHIVE_FAILED);
 	}
 
 #if defined(__CYGWIN__)
-	cleanup_pathname_win(a);
+	cleanup_pathname_win(path);
 #endif
 	/* Skip leading '/'. */
 	if (*src == '/') {
-		if (a->flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			                  "Path is absolute");
+		if (flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {
+			fsobj_error(a_eno, a_estr, ARCHIVE_ERRNO_MISC,
+			    "Path is ", "absolute");
 			return (ARCHIVE_FAILED);
 		}
 
@@ -2580,10 +2854,11 @@ cleanup_pathname(struct archive_write_disk *a)
 			} else if (src[1] == '.') {
 				if (src[2] == '/' || src[2] == '\0') {
 					/* Conditionally warn about '..' */
-					if (a->flags & ARCHIVE_EXTRACT_SECURE_NODOTDOT) {
-						archive_set_error(&a->archive,
+					if (flags
+					    & ARCHIVE_EXTRACT_SECURE_NODOTDOT) {
+						fsobj_error(a_eno, a_estr,
 						    ARCHIVE_ERRNO_MISC,
-						    "Path contains '..'");
+						    "Path contains ", "'..'");
 						return (ARCHIVE_FAILED);
 					}
 				}
@@ -2614,7 +2889,7 @@ cleanup_pathname(struct archive_write_disk *a)
 	 * We've just copied zero or more path elements, not including the
 	 * final '/'.
 	 */
-	if (dest == a->name) {
+	if (dest == path) {
 		/*
 		 * Nothing got copied.  The path must have been something
 		 * like '.' or '/' or './' or '/././././/./'.
@@ -2629,6 +2904,23 @@ cleanup_pathname(struct archive_write_disk *a)
 	return (ARCHIVE_OK);
 }
 
+static int
+cleanup_pathname(struct archive_write_disk *a)
+{
+	struct archive_string error_string;
+	int error_number;
+	int rc;
+	archive_string_init(&error_string);
+	rc = cleanup_pathname_fsobj(a->name, &error_number, &error_string,
+	    a->flags);
+	if (rc != ARCHIVE_OK) {
+		archive_set_error(&a->archive, error_number, "%s",
+		    error_string.s);
+	}
+	archive_string_free(&error_string);
+	return rc;
+}
+
 /*
  * Create the parent directory of the specified path, assuming path
  * is already in mutable storage.
@@ -2707,7 +2999,8 @@ create_dir(struct archive_write_disk *a, char *path)
 		}
 	} else if (errno != ENOENT && errno != ENOTDIR) {
 		/* Stat failed? */
-		archive_set_error(&a->archive, errno, "Can't test directory '%s'", path);
+		archive_set_error(&a->archive, errno,
+		    "Can't test directory '%s'", path);
 		return (ARCHIVE_FAILED);
 	} else if (slash != NULL) {
 		*slash = '\0';
@@ -3232,7 +3525,8 @@ clear_nochange_fflags(struct archive_write_disk *a)
 	nochange_flags |= EXT2_IMMUTABLE_FL;
 #endif
 
-	return (set_fflags_platform(a, a->fd, a->name, mode, 0, nochange_flags));
+	return (set_fflags_platform(a, a->fd, a->name, mode, 0,
+	    nochange_flags));
 }
 
 
@@ -3487,6 +3781,9 @@ copy_xattrs(struct archive_write_disk *a, int tmpfd, int dffd)
 static int
 copy_acls(struct archive_write_disk *a, int tmpfd, int dffd)
 {
+#ifndef HAVE_SYS_ACL_H
+	return 0;
+#else
 	acl_t acl, dfacl = NULL;
 	int acl_r, ret = ARCHIVE_OK;
 
@@ -3514,6 +3811,7 @@ copy_acls(struct archive_write_disk *a, int tmpfd, int dffd)
 	if (dfacl)
 		acl_free(dfacl);
 	return (ret);
+#endif
 }
 
 static int
@@ -3753,7 +4051,8 @@ set_xattrs(struct archive_write_disk *a)
 				if (errno == ENOTSUP || errno == ENOSYS) {
 					if (!warning_done) {
 						warning_done = 1;
-						archive_set_error(&a->archive, errno,
+						archive_set_error(&a->archive,
+						    errno,
 						    "Cannot restore extended "
 						    "attributes on this file "
 						    "system");
@@ -3764,7 +4063,8 @@ set_xattrs(struct archive_write_disk *a)
 				ret = ARCHIVE_WARN;
 			}
 		} else {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Invalid extended attribute encountered");
 			ret = ARCHIVE_WARN;
 		}
@@ -3808,19 +4108,22 @@ set_xattrs(struct archive_write_disk *a)
 			errno = 0;
 #if HAVE_EXTATTR_SET_FD
 			if (a->fd >= 0)
-				e = extattr_set_fd(a->fd, namespace, name, value, size);
+				e = extattr_set_fd(a->fd, namespace, name,
+				    value, size);
 			else
 #endif
 			/* TODO: should we use extattr_set_link() instead? */
 			{
-				e = extattr_set_file(archive_entry_pathname(entry),
-				    namespace, name, value, size);
+				e = extattr_set_file(
+				    archive_entry_pathname(entry), namespace,
+				    name, value, size);
 			}
 			if (e != (int)size) {
 				if (errno == ENOTSUP || errno == ENOSYS) {
 					if (!warning_done) {
 						warning_done = 1;
-						archive_set_error(&a->archive, errno,
+						archive_set_error(&a->archive,
+						    errno,
 						    "Cannot restore extended "
 						    "attributes on this file "
 						    "system");
@@ -3866,10 +4169,10 @@ older(struct stat *st, struct archive_entry *entry)
 {
 	/* First, test the seconds and return if we have a definite answer. */
 	/* Definitely older. */
-	if (st->st_mtime < archive_entry_mtime(entry))
+	if (to_int64_time(st->st_mtime) < to_int64_time(archive_entry_mtime(entry)))
 		return (1);
 	/* Definitely younger. */
-	if (st->st_mtime > archive_entry_mtime(entry))
+	if (to_int64_time(st->st_mtime) > to_int64_time(archive_entry_mtime(entry)))
 		return (0);
 	/* If this platform supports fractional seconds, try those. */
 #if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC