@@ -51,6 +51,7 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_support_format_mtree.c 2011
 #include "archive_private.h"
 #include "archive_read_private.h"
 #include "archive_string.h"
+#include "archive_pack_dev.h"
 
 #ifndef O_BINARY
 #define	O_BINARY 0
@@ -103,6 +104,7 @@ struct mtree {
 	struct archive_entry_linkresolver *resolver;
 
 	int64_t			 cur_size;
+	char checkfs;
 };
 
 static int	bid_keycmp(const char *, const char *, ssize_t);
@@ -173,6 +175,29 @@ get_time_t_min(void)
 #endif
 }
 
+static int
+archive_read_format_mtree_options(struct archive_read *a,
+    const char *key, const char *val)
+{
+	struct mtree *mtree;
+
+	mtree = (struct mtree *)(a->format->data);
+	if (strcmp(key, "checkfs")  == 0) {
+		/* Allows to read information missing from the mtree from the file system */
+		if (val == NULL || val[0] == 0) {
+			mtree->checkfs = 0;
+		} else {
+			mtree->checkfs = 1;
+		}
+		return (ARCHIVE_OK);
+	}
+
+	/* Note: The "warn" return is just to inform the options
+	 * supervisor that we didn't handle it.  It will generate
+	 * a suitable error if no one used this option. */
+	return (ARCHIVE_WARN);
+}
+
 static void
 free_options(struct mtree_option *head)
 {
@@ -205,7 +230,7 @@ archive_read_support_format_mtree(struct archive *_a)
 	mtree->fd = -1;
 
 	r = __archive_read_register_format(a, mtree, "mtree",
-	    mtree_bid, NULL, read_header, read_data, skip, NULL, cleanup);
+           mtree_bid, archive_read_format_mtree_options, read_header, read_data, skip, NULL, cleanup, NULL, NULL);
 
 	if (r != ARCHIVE_OK)
 		free(mtree);
@@ -367,7 +392,7 @@ bid_keyword(const char *p,  ssize_t len)
 		"gid", "gname", NULL
 	};
 	static const char *keys_il[] = {
-		"ignore", "link", NULL
+		"ignore", "inode", "link", NULL
 	};
 	static const char *keys_m[] = {
 		"md5", "md5digest", "mode", NULL
@@ -376,7 +401,7 @@ bid_keyword(const char *p,  ssize_t len)
 		"nlink", "nochange", "optional", NULL
 	};
 	static const char *keys_r[] = {
-		"rmd160", "rmd160digest", NULL
+		"resdevice", "rmd160", "rmd160digest", NULL
 	};
 	static const char *keys_s[] = {
 		"sha1", "sha1digest",
@@ -1103,162 +1128,164 @@ parse_file(struct archive_read *a, struct archive_entry *entry,
 			mtree->current_dir.length = n;
 	}
 
-	/*
-	 * Try to open and stat the file to get the real size
-	 * and other file info.  It would be nice to avoid
-	 * this here so that getting a listing of an mtree
-	 * wouldn't require opening every referenced contents
-	 * file.  But then we wouldn't know the actual
-	 * contents size, so I don't see a really viable way
-	 * around this.  (Also, we may want to someday pull
-	 * other unspecified info from the contents file on
-	 * disk.)
-	 */
-	mtree->fd = -1;
-	if (archive_strlen(&mtree->contents_name) > 0)
-		path = mtree->contents_name.s;
-	else
-		path = archive_entry_pathname(entry);
-
-	if (archive_entry_filetype(entry) == AE_IFREG ||
-	    archive_entry_filetype(entry) == AE_IFDIR) {
-		mtree->fd = open(path, O_RDONLY | O_BINARY | O_CLOEXEC);
-		__archive_ensure_cloexec_flag(mtree->fd);
-		if (mtree->fd == -1 &&
-		    (errno != ENOENT ||
-		     archive_strlen(&mtree->contents_name) > 0)) {
-			archive_set_error(&a->archive, errno,
-			    "Can't open %s", path);
-			r = ARCHIVE_WARN;
+	if (mtree->checkfs) {
+		/*
+		 * Try to open and stat the file to get the real size
+		 * and other file info.  It would be nice to avoid
+		 * this here so that getting a listing of an mtree
+		 * wouldn't require opening every referenced contents
+		 * file.  But then we wouldn't know the actual
+		 * contents size, so I don't see a really viable way
+		 * around this.  (Also, we may want to someday pull
+		 * other unspecified info from the contents file on
+		 * disk.)
+		 */
+		mtree->fd = -1;
+		if (archive_strlen(&mtree->contents_name) > 0)
+			path = mtree->contents_name.s;
+		else
+			path = archive_entry_pathname(entry);
+
+		if (archive_entry_filetype(entry) == AE_IFREG ||
+				archive_entry_filetype(entry) == AE_IFDIR) {
+			mtree->fd = open(path, O_RDONLY | O_BINARY | O_CLOEXEC);
+			__archive_ensure_cloexec_flag(mtree->fd);
+			if (mtree->fd == -1 &&
+					(errno != ENOENT ||
+					 archive_strlen(&mtree->contents_name) > 0)) {
+				archive_set_error(&a->archive, errno,
+						"Can't open %s", path);
+				r = ARCHIVE_WARN;
+			}
 		}
-	}
 
-	st = &st_storage;
-	if (mtree->fd >= 0) {
-		if (fstat(mtree->fd, st) == -1) {
-			archive_set_error(&a->archive, errno,
-			    "Could not fstat %s", path);
-			r = ARCHIVE_WARN;
-			/* If we can't stat it, don't keep it open. */
-			close(mtree->fd);
-			mtree->fd = -1;
+		st = &st_storage;
+		if (mtree->fd >= 0) {
+			if (fstat(mtree->fd, st) == -1) {
+				archive_set_error(&a->archive, errno,
+						"Could not fstat %s", path);
+				r = ARCHIVE_WARN;
+				/* If we can't stat it, don't keep it open. */
+				close(mtree->fd);
+				mtree->fd = -1;
+				st = NULL;
+			}
+		} else if (lstat(path, st) == -1) {
 			st = NULL;
 		}
-	} else if (lstat(path, st) == -1) {
-		st = NULL;
-	}
 
-	/*
-	 * Check for a mismatch between the type in the specification and
-	 * the type of the contents object on disk.
-	 */
-	if (st != NULL) {
-		if (
-		    ((st->st_mode & S_IFMT) == S_IFREG &&
-		     archive_entry_filetype(entry) == AE_IFREG)
+		/*
+		 * Check for a mismatch between the type in the specification and
+		 * the type of the contents object on disk.
+		 */
+		if (st != NULL) {
+			if (
+					((st->st_mode & S_IFMT) == S_IFREG &&
+					 archive_entry_filetype(entry) == AE_IFREG)
 #ifdef S_IFLNK
-		    || ((st->st_mode & S_IFMT) == S_IFLNK &&
-			archive_entry_filetype(entry) == AE_IFLNK)
+					|| ((st->st_mode & S_IFMT) == S_IFLNK &&
+						archive_entry_filetype(entry) == AE_IFLNK)
 #endif
 #ifdef S_IFSOCK
-		    || ((st->st_mode & S_IFSOCK) == S_IFSOCK &&
-			archive_entry_filetype(entry) == AE_IFSOCK)
+					|| ((st->st_mode & S_IFSOCK) == S_IFSOCK &&
+						archive_entry_filetype(entry) == AE_IFSOCK)
 #endif
 #ifdef S_IFCHR
-		    || ((st->st_mode & S_IFMT) == S_IFCHR &&
-			archive_entry_filetype(entry) == AE_IFCHR)
+					|| ((st->st_mode & S_IFMT) == S_IFCHR &&
+						archive_entry_filetype(entry) == AE_IFCHR)
 #endif
 #ifdef S_IFBLK
-		    || ((st->st_mode & S_IFMT) == S_IFBLK &&
-			archive_entry_filetype(entry) == AE_IFBLK)
+					|| ((st->st_mode & S_IFMT) == S_IFBLK &&
+						archive_entry_filetype(entry) == AE_IFBLK)
 #endif
-		    || ((st->st_mode & S_IFMT) == S_IFDIR &&
-			archive_entry_filetype(entry) == AE_IFDIR)
+					|| ((st->st_mode & S_IFMT) == S_IFDIR &&
+						archive_entry_filetype(entry) == AE_IFDIR)
 #ifdef S_IFIFO
-		    || ((st->st_mode & S_IFMT) == S_IFIFO &&
-			archive_entry_filetype(entry) == AE_IFIFO)
+					|| ((st->st_mode & S_IFMT) == S_IFIFO &&
+							archive_entry_filetype(entry) == AE_IFIFO)
 #endif
-		    ) {
-			/* Types match. */
-		} else {
-			/* Types don't match; bail out gracefully. */
-			if (mtree->fd >= 0)
-				close(mtree->fd);
-			mtree->fd = -1;
-			if (parsed_kws & MTREE_HAS_OPTIONAL) {
-				/* It's not an error for an optional entry
-				   to not match disk. */
-				*use_next = 1;
-			} else if (r == ARCHIVE_OK) {
-				archive_set_error(&a->archive,
-				    ARCHIVE_ERRNO_MISC,
-				    "mtree specification has different type for %s",
-				    archive_entry_pathname(entry));
-				r = ARCHIVE_WARN;
-			}
-			return r;
+					) {
+						/* Types match. */
+					} else {
+						/* Types don't match; bail out gracefully. */
+						if (mtree->fd >= 0)
+							close(mtree->fd);
+						mtree->fd = -1;
+						if (parsed_kws & MTREE_HAS_OPTIONAL) {
+							/* It's not an error for an optional entry
+							   to not match disk. */
+							*use_next = 1;
+						} else if (r == ARCHIVE_OK) {
+							archive_set_error(&a->archive,
+									ARCHIVE_ERRNO_MISC,
+									"mtree specification has different type for %s",
+									archive_entry_pathname(entry));
+							r = ARCHIVE_WARN;
+						}
+						return r;
+					}
 		}
-	}
 
-	/*
-	 * If there is a contents file on disk, pick some of the metadata
-	 * from that file.  For most of these, we only set it from the contents
-	 * if it wasn't already parsed from the specification.
-	 */
-	if (st != NULL) {
-		if (((parsed_kws & MTREE_HAS_DEVICE) == 0 ||
-		     (parsed_kws & MTREE_HAS_NOCHANGE) != 0) &&
-		    (archive_entry_filetype(entry) == AE_IFCHR ||
-		     archive_entry_filetype(entry) == AE_IFBLK))
-			archive_entry_set_rdev(entry, st->st_rdev);
-		if ((parsed_kws & (MTREE_HAS_GID | MTREE_HAS_GNAME)) == 0 ||
-		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
-			archive_entry_set_gid(entry, st->st_gid);
-		if ((parsed_kws & (MTREE_HAS_UID | MTREE_HAS_UNAME)) == 0 ||
-		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
-			archive_entry_set_uid(entry, st->st_uid);
-		if ((parsed_kws & MTREE_HAS_MTIME) == 0 ||
-		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0) {
+		/*
+		 * If there is a contents file on disk, pick some of the metadata
+		 * from that file.  For most of these, we only set it from the contents
+		 * if it wasn't already parsed from the specification.
+		 */
+		if (st != NULL) {
+			if (((parsed_kws & MTREE_HAS_DEVICE) == 0 ||
+						(parsed_kws & MTREE_HAS_NOCHANGE) != 0) &&
+					(archive_entry_filetype(entry) == AE_IFCHR ||
+					 archive_entry_filetype(entry) == AE_IFBLK))
+				archive_entry_set_rdev(entry, st->st_rdev);
+			if ((parsed_kws & (MTREE_HAS_GID | MTREE_HAS_GNAME)) == 0 ||
+					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+				archive_entry_set_gid(entry, st->st_gid);
+			if ((parsed_kws & (MTREE_HAS_UID | MTREE_HAS_UNAME)) == 0 ||
+					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+				archive_entry_set_uid(entry, st->st_uid);
+			if ((parsed_kws & MTREE_HAS_MTIME) == 0 ||
+					(parsed_kws & MTREE_HAS_NOCHANGE) != 0) {
 #if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC
-			archive_entry_set_mtime(entry, st->st_mtime,
-			    st->st_mtimespec.tv_nsec);
+				archive_entry_set_mtime(entry, st->st_mtime,
+						st->st_mtimespec.tv_nsec);
 #elif HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
-			archive_entry_set_mtime(entry, st->st_mtime,
-			    st->st_mtim.tv_nsec);
+				archive_entry_set_mtime(entry, st->st_mtime,
+						st->st_mtim.tv_nsec);
 #elif HAVE_STRUCT_STAT_ST_MTIME_N
-			archive_entry_set_mtime(entry, st->st_mtime,
-			    st->st_mtime_n);
+				archive_entry_set_mtime(entry, st->st_mtime,
+						st->st_mtime_n);
 #elif HAVE_STRUCT_STAT_ST_UMTIME
-			archive_entry_set_mtime(entry, st->st_mtime,
-			    st->st_umtime*1000);
+				archive_entry_set_mtime(entry, st->st_mtime,
+						st->st_umtime*1000);
 #elif HAVE_STRUCT_STAT_ST_MTIME_USEC
-			archive_entry_set_mtime(entry, st->st_mtime,
-			    st->st_mtime_usec*1000);
+				archive_entry_set_mtime(entry, st->st_mtime,
+						st->st_mtime_usec*1000);
 #else
-			archive_entry_set_mtime(entry, st->st_mtime, 0);
+				archive_entry_set_mtime(entry, st->st_mtime, 0);
 #endif
+			}
+			if ((parsed_kws & MTREE_HAS_NLINK) == 0 ||
+					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+				archive_entry_set_nlink(entry, st->st_nlink);
+			if ((parsed_kws & MTREE_HAS_PERM) == 0 ||
+					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+				archive_entry_set_perm(entry, st->st_mode);
+			if ((parsed_kws & MTREE_HAS_SIZE) == 0 ||
+					(parsed_kws & MTREE_HAS_NOCHANGE) != 0)
+				archive_entry_set_size(entry, st->st_size);
+			archive_entry_set_ino(entry, st->st_ino);
+			archive_entry_set_dev(entry, st->st_dev);
+
+			archive_entry_linkify(mtree->resolver, &entry, &sparse_entry);
+		} else if (parsed_kws & MTREE_HAS_OPTIONAL) {
+			/*
+			 * Couldn't open the entry, stat it or the on-disk type
+			 * didn't match.  If this entry is optional, just ignore it
+			 * and read the next header entry.
+			 */
+			*use_next = 1;
+			return ARCHIVE_OK;
 		}
-		if ((parsed_kws & MTREE_HAS_NLINK) == 0 ||
-		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
-			archive_entry_set_nlink(entry, st->st_nlink);
-		if ((parsed_kws & MTREE_HAS_PERM) == 0 ||
-		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
-			archive_entry_set_perm(entry, st->st_mode);
-		if ((parsed_kws & MTREE_HAS_SIZE) == 0 ||
-		    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)
-			archive_entry_set_size(entry, st->st_size);
-		archive_entry_set_ino(entry, st->st_ino);
-		archive_entry_set_dev(entry, st->st_dev);
-
-		archive_entry_linkify(mtree->resolver, &entry, &sparse_entry);
-	} else if (parsed_kws & MTREE_HAS_OPTIONAL) {
-		/*
-		 * Couldn't open the entry, stat it or the on-disk type
-		 * didn't match.  If this entry is optional, just ignore it
-		 * and read the next header entry.
-		 */
-		*use_next = 1;
-		return ARCHIVE_OK;
 	}
 
 	mtree->cur_size = archive_entry_size(entry);
@@ -1292,33 +1319,82 @@ parse_line(struct archive_read *a, struct archive_entry *entry,
 
 /*
  * Device entries have one of the following forms:
- * raw dev_t
- * format,major,minor[,subdevice]
- *
- * Just use major and minor, no translation etc is done
- * between formats.
+ *  - raw dev_t
+ *  - format,major,minor[,subdevice]
+ * When parsing succeeded, `pdev' will contain the appropriate dev_t value.
  */
-static int
-parse_device(struct archive *a, struct archive_entry *entry, char *val)
+
+/* strsep() is not in C90, but strcspn() is. */
+/* Taken from http://unixpapa.com/incnote/string.html */
+static char *
+la_strsep(char **sp, char *sep)
 {
-	char *comma1, *comma2;
+	char *p, *s;
+	if (sp == NULL || *sp == NULL || **sp == '\0')
+		return(NULL);
+	s = *sp;
+	p = s + strcspn(s, sep);
+	if (*p != '\0')
+		*p++ = '\0';
+	*sp = p;
+	return(s);
+}
 
-	comma1 = strchr(val, ',');
-	if (comma1 == NULL) {
-		archive_entry_set_dev(entry, (dev_t)mtree_atol10(&val));
-		return (ARCHIVE_OK);
-	}
-	++comma1;
-	comma2 = strchr(comma1, ',');
-	if (comma2 == NULL) {
-		archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
-		    "Malformed device attribute");
-		return (ARCHIVE_WARN);
+static int
+parse_device(dev_t *pdev, struct archive *a, char *val)
+{
+#define MAX_PACK_ARGS 3
+	unsigned long numbers[MAX_PACK_ARGS];
+	char *p, *dev;
+	int argc;
+	pack_t *pack;
+	dev_t result;
+	const char *error = NULL;
+
+	memset(pdev, 0, sizeof(*pdev));
+	if ((dev = strchr(val, ',')) != NULL) {
+		/*
+		 * Device's major/minor are given in a specified format.
+		 * Decode and pack it accordingly.
+		 */
+		*dev++ = '\0';
+		if ((pack = pack_find(val)) == NULL) {
+			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Unknown format `%s'", val);
+			return ARCHIVE_WARN;
+		}
+		argc = 0;
+		while ((p = la_strsep(&dev, ",")) != NULL) {
+			if (*p == '\0') {
+				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
+				    "Missing number");
+				return ARCHIVE_WARN;
+			}
+			numbers[argc++] = mtree_atol(&p);
+			if (argc > MAX_PACK_ARGS) {
+				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
+				    "Too many arguments");
+				return ARCHIVE_WARN;
+			}
+		}
+		if (argc < 2) {
+			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Not enough arguments");
+			return ARCHIVE_WARN;
+		}
+		result = (*pack)(argc, numbers, &error);
+		if (error != NULL) {
+			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
+			    "%s", error);
+			return ARCHIVE_WARN;
+		}
+	} else {
+		/* file system raw value. */
+		result = (dev_t)mtree_atol(&val);
 	}
-	++comma2;
-	archive_entry_set_rdevmajor(entry, (dev_t)mtree_atol(&comma1));
-	archive_entry_set_rdevminor(entry, (dev_t)mtree_atol(&comma2));
-	return (ARCHIVE_OK);
+	*pdev = result;
+	return ARCHIVE_OK;
+#undef MAX_PACK_ARGS
 }
 
 /*
@@ -1374,8 +1450,16 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 			break;
 	case 'd':
 		if (strcmp(key, "device") == 0) {
+			/* stat(2) st_rdev field, e.g. the major/minor IDs
+			 * of a char/block special file */
+			int r;
+			dev_t dev;
+
 			*parsed_kws |= MTREE_HAS_DEVICE;
-			return parse_device(&a->archive, entry, val);
+			r = parse_device(&dev, &a->archive, val);
+			if (r == ARCHIVE_OK)
+				archive_entry_set_rdev(entry, dev);
+			return r;
 		}
 	case 'f':
 		if (strcmp(key, "flags") == 0) {
@@ -1394,6 +1478,11 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 			archive_entry_copy_gname(entry, val);
 			break;
 		}
+	case 'i':
+		if (strcmp(key, "inode") == 0) {
+			archive_entry_set_ino(entry, mtree_atol10(&val));
+			break;
+		}
 	case 'l':
 		if (strcmp(key, "link") == 0) {
 			archive_entry_copy_symlink(entry, val);
@@ -1423,6 +1512,17 @@ parse_keyword(struct archive_read *a, struct mtree *mtree,
 			break;
 		}
 	case 'r':
+		if (strcmp(key, "resdevice") == 0) {
+			/* stat(2) st_dev field, e.g. the device ID where the
+			 * inode resides */
+			int r;
+			dev_t dev;
+
+			r = parse_device(&dev, &a->archive, val);
+			if (r == ARCHIVE_OK)
+				archive_entry_set_dev(entry, dev);
+			return r;
+		}
 		if (strcmp(key, "rmd160") == 0 ||
 		    strcmp(key, "rmd160digest") == 0)
 			break;