@@ -1,6 +1,6 @@
 /*-
  * Copyright (c) 2003-2009 Tim Kientzle
- * Copyright (c) 2010 Michihiro NAKAJIMA
+ * Copyright (c) 2010-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -49,18 +49,17 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #ifdef HAVE_SYS_STAT_H
 #include <sys/stat.h>
 #endif
-#ifdef HAVE_SYS_XATTR_H
+#if defined(HAVE_SYS_XATTR_H)
 #include <sys/xattr.h>
+#elif defined(HAVE_ATTR_XATTR_H)
+#include <attr/xattr.h>
 #endif
 #ifdef HAVE_SYS_EA_H
 #include <sys/ea.h>
 #endif
 #ifdef HAVE_ACL_LIBACL_H
 #include <acl/libacl.h>
 #endif
-#ifdef HAVE_ATTR_XATTR_H
-#include <attr/xattr.h>
-#endif
 #ifdef HAVE_COPYFILE_H
 #include <copyfile.h>
 #endif
@@ -73,6 +72,9 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #ifdef HAVE_LIMITS_H
 #include <limits.h>
 #endif
+#ifdef HAVE_LINUX_TYPES_H
+#include <linux/types.h>
+#endif
 #ifdef HAVE_LINUX_FIEMAP_H
 #include <linux/fiemap.h>
 #endif
@@ -101,6 +103,10 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #include "archive_private.h"
 #include "archive_read_disk_private.h"
 
+#ifndef O_CLOEXEC
+#define O_CLOEXEC	0
+#endif
+
 /*
  * Linux and FreeBSD plug this obvious hole in POSIX.1e in
  * different ways.
@@ -111,14 +117,14 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #define	ACL_GET_PERM acl_get_perm_np
 #endif
 
-static int setup_acls_posix1e(struct archive_read_disk *,
-    struct archive_entry *, int fd);
+static int setup_acls(struct archive_read_disk *,
+    struct archive_entry *, int *fd);
 static int setup_mac_metadata(struct archive_read_disk *,
-    struct archive_entry *, int fd);
+    struct archive_entry *, int *fd);
 static int setup_xattrs(struct archive_read_disk *,
-    struct archive_entry *, int fd);
+    struct archive_entry *, int *fd);
 static int setup_sparse(struct archive_read_disk *,
-    struct archive_entry *, int fd);
+    struct archive_entry *, int *fd);
 
 int
 archive_read_disk_entry_from_file(struct archive *_a,
@@ -187,11 +193,18 @@ archive_read_disk_entry_from_file(struct archive *_a,
 	 * this is an extra step, it has a nice side-effect: We get an
 	 * open file descriptor which we can use in the subsequent lookups. */
 	if ((S_ISREG(st->st_mode) || S_ISDIR(st->st_mode))) {
-		if (fd < 0)
-			fd = open(path, O_RDONLY | O_NONBLOCK);
+		if (fd < 0) {
+			if (a->tree != NULL)
+				fd = a->open_on_current_dir(a->tree, path,
+					O_RDONLY | O_NONBLOCK | O_CLOEXEC);
+			else
+				fd = open(path, O_RDONLY | O_NONBLOCK |
+						O_CLOEXEC);
+			__archive_ensure_cloexec_flag(fd);
+		}
 		if (fd >= 0) {
-			unsigned long stflags;
-			int r = ioctl(fd, EXT2_IOC_GETFLAGS, &stflags);
+			int stflags;
+			r = ioctl(fd, EXT2_IOC_GETFLAGS, &stflags);
 			if (r == 0 && stflags != 0)
 				archive_entry_set_fflags(entry, stflags, 0);
 		}
@@ -210,13 +223,21 @@ archive_read_disk_entry_from_file(struct archive *_a,
 			    "Couldn't read link data");
 			return (ARCHIVE_FAILED);
 		}
+		if (a->tree != NULL) {
 #ifdef HAVE_READLINKAT
-		if (a->entry_wd_fd >= 0)
-			lnklen = readlinkat(a->entry_wd_fd, path,
-			    linkbuffer, linkbuffer_len);
-		else
+			lnklen = readlinkat(a->tree_current_dir_fd(a->tree),
+			    path, linkbuffer, linkbuffer_len);
+#else
+			if (a->tree_enter_working_dir(a->tree) != 0) {
+				archive_set_error(&a->archive, errno,
+				    "Couldn't read link data");
+				free(linkbuffer);
+				return (ARCHIVE_FAILED);
+			}
+			lnklen = readlink(path, linkbuffer, linkbuffer_len);
 #endif /* HAVE_READLINKAT */
-		lnklen = readlink(path, linkbuffer, linkbuffer_len);
+		} else
+			lnklen = readlink(path, linkbuffer, linkbuffer_len);
 		if (lnklen < 0) {
 			archive_set_error(&a->archive, errno,
 			    "Couldn't read link data");
@@ -229,14 +250,16 @@ archive_read_disk_entry_from_file(struct archive *_a,
 	}
 #endif /* HAVE_READLINK || HAVE_READLINKAT */
 
-	r = setup_acls_posix1e(a, entry, fd);
-	r1 = setup_xattrs(a, entry, fd);
-	if (r1 < r)
-		r = r1;
-	r1 = setup_mac_metadata(a, entry, fd);
+	r = setup_acls(a, entry, &fd);
+	r1 = setup_xattrs(a, entry, &fd);
 	if (r1 < r)
 		r = r1;
-	r1 = setup_sparse(a, entry, fd);
+	if (a->enable_copyfile) {
+		r1 = setup_mac_metadata(a, entry, &fd);
+		if (r1 < r)
+			r = r1;
+	}
+	r1 = setup_sparse(a, entry, &fd);
 	if (r1 < r)
 		r = r1;
 
@@ -262,16 +285,18 @@ archive_read_disk_entry_from_file(struct archive *_a,
  */
 static int
 setup_mac_metadata(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	int tempfd = -1;
 	int copyfile_flags = COPYFILE_NOFOLLOW | COPYFILE_ACL | COPYFILE_XATTR;
 	struct stat copyfile_stat;
 	int ret = ARCHIVE_OK;
-	void *buff;
+	void *buff = NULL;
 	int have_attrs;
-	const char *name, *tempdir, *tempfile = NULL;
+	const char *name, *tempdir;
+	struct archive_string tempfile;
 
+	(void)fd; /* UNUSED */
 	name = archive_entry_sourcepath(entry);
 	if (name == NULL)
 		name = archive_entry_pathname(entry);
@@ -281,6 +306,14 @@ setup_mac_metadata(struct archive_read_disk *a,
 		return (ARCHIVE_WARN);
 	}
 
+	if (a->tree != NULL) {
+		if (a->tree_enter_working_dir(a->tree) != 0) {
+			archive_set_error(&a->archive, errno,
+				    "Couldn't change dir");
+				return (ARCHIVE_FAILED);
+		}
+	}
+
 	/* Short-circuit if there's nothing to do. */
 	have_attrs = copyfile(name, NULL, 0, copyfile_flags | COPYFILE_CHECK);
 	if (have_attrs == -1) {
@@ -296,25 +329,28 @@ setup_mac_metadata(struct archive_read_disk *a,
 		tempdir = getenv("TMPDIR");
 	if (tempdir == NULL)
 		tempdir = _PATH_TMP;
-	tempfile = tempnam(tempdir, "tar.md.");
+	archive_string_init(&tempfile);
+	archive_strcpy(&tempfile, tempdir);
+	archive_strcat(&tempfile, "tar.md.XXXXXX");
+	tempfd = mkstemp(tempfile.s);
+	if (tempfd < 0) {
+		archive_set_error(&a->archive, errno,
+		    "Could not open extended attribute file");
+		ret = ARCHIVE_WARN;
+		goto cleanup;
+	}
+	__archive_ensure_cloexec_flag(tempfd);
 
 	/* XXX I wish copyfile() could pack directly to a memory
 	 * buffer; that would avoid the temp file here.  For that
 	 * matter, it would be nice if fcopyfile() actually worked,
 	 * that would reduce the many open/close races here. */
-	if (copyfile(name, tempfile, 0, copyfile_flags | COPYFILE_PACK)) {
+	if (copyfile(name, tempfile.s, 0, copyfile_flags | COPYFILE_PACK)) {
 		archive_set_error(&a->archive, errno,
 		    "Could not pack extended attributes");
 		ret = ARCHIVE_WARN;
 		goto cleanup;
 	}
-	tempfd = open(tempfile, O_RDONLY);
-	if (tempfd < 0) {
-		archive_set_error(&a->archive, errno,
-		    "Could not open extended attribute file");
-		ret = ARCHIVE_WARN;
-		goto cleanup;
-	}
 	if (fstat(tempfd, &copyfile_stat)) {
 		archive_set_error(&a->archive, errno,
 		    "Could not check size of extended attributes");
@@ -337,10 +373,12 @@ setup_mac_metadata(struct archive_read_disk *a,
 	archive_entry_copy_mac_metadata(entry, buff, copyfile_stat.st_size);
 
 cleanup:
-	if (tempfd >= 0)
+	if (tempfd >= 0) {
 		close(tempfd);
-	if (tempfile != NULL)
-		unlink(tempfile);
+		unlink(tempfile.s);
+	}
+	archive_string_free(&tempfile);
+	free(buff);
 	return (ret);
 }
 
@@ -351,7 +389,7 @@ setup_mac_metadata(struct archive_read_disk *a,
  */
 static int
 setup_mac_metadata(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	(void)a; /* UNUSED */
 	(void)entry; /* UNUSED */
@@ -361,26 +399,58 @@ setup_mac_metadata(struct archive_read_disk *a,
 #endif
 
 
-#ifdef HAVE_POSIX_ACL
-static void setup_acl_posix1e(struct archive_read_disk *a,
+#if defined(HAVE_POSIX_ACL) && defined(ACL_TYPE_NFS4)
+static int translate_acl(struct archive_read_disk *a,
     struct archive_entry *entry, acl_t acl, int archive_entry_acl_type);
 
 static int
-setup_acls_posix1e(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+setup_acls(struct archive_read_disk *a,
+    struct archive_entry *entry, int *fd)
 {
 	const char	*accpath;
 	acl_t		 acl;
+#if HAVE_ACL_IS_TRIVIAL_NP
+	int		r;
+#endif
 
 	accpath = archive_entry_sourcepath(entry);
 	if (accpath == NULL)
 		accpath = archive_entry_pathname(entry);
 
 	archive_entry_acl_clear(entry);
 
+	/* Try NFS4 ACL first. */
+	if (*fd >= 0)
+		acl = acl_get_fd(*fd);
+#if HAVE_ACL_GET_LINK_NP
+	else if (!a->follow_symlinks)
+		acl = acl_get_link_np(accpath, ACL_TYPE_NFS4);
+#else
+	else if ((!a->follow_symlinks)
+	    && (archive_entry_filetype(entry) == AE_IFLNK))
+		/* We can't get the ACL of a symlink, so we assume it can't
+		   have one. */
+		acl = NULL;
+#endif
+	else
+		acl = acl_get_file(accpath, ACL_TYPE_NFS4);
+#if HAVE_ACL_IS_TRIVIAL_NP
+	/* Ignore "trivial" ACLs that just mirror the file mode. */
+	acl_is_trivial_np(acl, &r);
+	if (r) {
+		acl_free(acl);
+		acl = NULL;
+	}
+#endif
+	if (acl != NULL) {
+		translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_NFS4);
+		acl_free(acl);
+		return (ARCHIVE_OK);
+	}
+
 	/* Retrieve access ACL from file. */
-	if (fd >= 0)
-		acl = acl_get_fd(fd);
+	if (*fd >= 0)
+		acl = acl_get_fd(*fd);
 #if HAVE_ACL_GET_LINK_NP
 	else if (!a->follow_symlinks)
 		acl = acl_get_link_np(accpath, ACL_TYPE_ACCESS);
@@ -394,7 +464,7 @@ setup_acls_posix1e(struct archive_read_disk *a,
 	else
 		acl = acl_get_file(accpath, ACL_TYPE_ACCESS);
 	if (acl != NULL) {
-		setup_acl_posix1e(a, entry, acl,
+		translate_acl(a, entry, acl,
 		    ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
 		acl_free(acl);
 	}
@@ -403,7 +473,7 @@ setup_acls_posix1e(struct archive_read_disk *a,
 	if (S_ISDIR(archive_entry_mode(entry))) {
 		acl = acl_get_file(accpath, ACL_TYPE_DEFAULT);
 		if (acl != NULL) {
-			setup_acl_posix1e(a, entry, acl,
+			translate_acl(a, entry, acl,
 			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);
 			acl_free(acl);
 		}
@@ -412,69 +482,181 @@ setup_acls_posix1e(struct archive_read_disk *a,
 }
 
 /*
- * Translate POSIX.1e ACL into libarchive internal structure.
+ * Translate system ACL into libarchive internal structure.
  */
-static void
-setup_acl_posix1e(struct archive_read_disk *a,
-    struct archive_entry *entry, acl_t acl, int archive_entry_acl_type)
+
+static struct {
+        int archive_perm;
+        int platform_perm;
+} acl_perm_map[] = {
+        {ARCHIVE_ENTRY_ACL_EXECUTE, ACL_EXECUTE},
+        {ARCHIVE_ENTRY_ACL_WRITE, ACL_WRITE},
+        {ARCHIVE_ENTRY_ACL_READ, ACL_READ},
+        {ARCHIVE_ENTRY_ACL_READ_DATA, ACL_READ_DATA},
+        {ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACL_LIST_DIRECTORY},
+        {ARCHIVE_ENTRY_ACL_WRITE_DATA, ACL_WRITE_DATA},
+        {ARCHIVE_ENTRY_ACL_ADD_FILE, ACL_ADD_FILE},
+        {ARCHIVE_ENTRY_ACL_APPEND_DATA, ACL_APPEND_DATA},
+        {ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACL_ADD_SUBDIRECTORY},
+        {ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACL_READ_NAMED_ATTRS},
+        {ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACL_WRITE_NAMED_ATTRS},
+        {ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACL_DELETE_CHILD},
+        {ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACL_READ_ATTRIBUTES},
+        {ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACL_WRITE_ATTRIBUTES},
+        {ARCHIVE_ENTRY_ACL_DELETE, ACL_DELETE},
+        {ARCHIVE_ENTRY_ACL_READ_ACL, ACL_READ_ACL},
+        {ARCHIVE_ENTRY_ACL_WRITE_ACL, ACL_WRITE_ACL},
+        {ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACL_WRITE_OWNER},
+        {ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACL_SYNCHRONIZE}
+};
+
+static struct {
+        int archive_inherit;
+        int platform_inherit;
+} acl_inherit_map[] = {
+        {ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_FILE_INHERIT},
+	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACL_ENTRY_DIRECTORY_INHERIT},
+	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACL_ENTRY_NO_PROPAGATE_INHERIT},
+	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACL_ENTRY_INHERIT_ONLY}
+};
+
+static int
+translate_acl(struct archive_read_disk *a,
+    struct archive_entry *entry, acl_t acl, int default_entry_acl_type)
 {
 	acl_tag_t	 acl_tag;
+	acl_entry_type_t acl_type;
+	acl_flagset_t	 acl_flagset;
 	acl_entry_t	 acl_entry;
 	acl_permset_t	 acl_permset;
+	int		 brand, i, r, entry_acl_type;
 	int		 s, ae_id, ae_tag, ae_perm;
 	const char	*ae_name;
 
+
+	// FreeBSD "brands" ACLs as POSIX.1e or NFSv4
+	// Make sure the "brand" on this ACL is consistent
+	// with the default_entry_acl_type bits provided.
+	acl_get_brand_np(acl, &brand);
+	switch (brand) {
+	case ACL_BRAND_POSIX:
+		switch (default_entry_acl_type) {
+		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
+		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
+			break;
+		default:
+			// XXX set warning message?
+			return ARCHIVE_FAILED;
+		}
+		break;
+	case ACL_BRAND_NFS4:
+		if (default_entry_acl_type & ~ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
+			// XXX set warning message?
+			return ARCHIVE_FAILED;
+		}
+		break;
+	default:
+		// XXX set warning message?
+		return ARCHIVE_FAILED;
+		break;
+	}
+
+
 	s = acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_entry);
 	while (s == 1) {
 		ae_id = -1;
 		ae_name = NULL;
+		ae_perm = 0;
 
 		acl_get_tag_type(acl_entry, &acl_tag);
-		if (acl_tag == ACL_USER) {
+		switch (acl_tag) {
+		case ACL_USER:
 			ae_id = (int)*(uid_t *)acl_get_qualifier(acl_entry);
 			ae_name = archive_read_disk_uname(&a->archive, ae_id);
 			ae_tag = ARCHIVE_ENTRY_ACL_USER;
-		} else if (acl_tag == ACL_GROUP) {
+			break;
+		case ACL_GROUP:
 			ae_id = (int)*(gid_t *)acl_get_qualifier(acl_entry);
 			ae_name = archive_read_disk_gname(&a->archive, ae_id);
 			ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
-		} else if (acl_tag == ACL_MASK) {
+			break;
+		case ACL_MASK:
 			ae_tag = ARCHIVE_ENTRY_ACL_MASK;
-		} else if (acl_tag == ACL_USER_OBJ) {
+			break;
+		case ACL_USER_OBJ:
 			ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
-		} else if (acl_tag == ACL_GROUP_OBJ) {
+			break;
+		case ACL_GROUP_OBJ:
 			ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
-		} else if (acl_tag == ACL_OTHER) {
+			break;
+		case ACL_OTHER:
 			ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
-		} else {
+			break;
+		case ACL_EVERYONE:
+			ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
+			break;
+		default:
 			/* Skip types that libarchive can't support. */
+			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
 			continue;
 		}
 
-		acl_get_permset(acl_entry, &acl_permset);
-		ae_perm = 0;
+		// XXX acl type maps to allow/deny/audit/YYYY bits
+		// XXX acl_get_entry_type_np on FreeBSD returns EINVAL for
+		// non-NFSv4 ACLs
+		entry_acl_type = default_entry_acl_type;
+		r = acl_get_entry_type_np(acl_entry, &acl_type);
+		if (r == 0) {
+			switch (acl_type) {
+			case ACL_ENTRY_TYPE_ALLOW:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
+				break;
+			case ACL_ENTRY_TYPE_DENY:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
+				break;
+			case ACL_ENTRY_TYPE_AUDIT:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_AUDIT;
+				break;
+			case ACL_ENTRY_TYPE_ALARM:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
+				break;
+			}
+		}
+
 		/*
-		 * acl_get_perm() is spelled differently on different
-		 * platforms; see above.
+		 * Libarchive stores "flag" (NFSv4 inheritance bits)
+		 * in the ae_perm bitmap.
 		 */
-		if (ACL_GET_PERM(acl_permset, ACL_EXECUTE))
-			ae_perm |= ARCHIVE_ENTRY_ACL_EXECUTE;
-		if (ACL_GET_PERM(acl_permset, ACL_READ))
-			ae_perm |= ARCHIVE_ENTRY_ACL_READ;
-		if (ACL_GET_PERM(acl_permset, ACL_WRITE))
-			ae_perm |= ARCHIVE_ENTRY_ACL_WRITE;
+		acl_get_flagset_np(acl_entry, &acl_flagset);
+                for (i = 0; i < (int)(sizeof(acl_inherit_map) / sizeof(acl_inherit_map[0])); ++i) {
+			if (acl_get_flag_np(acl_flagset,
+					    acl_inherit_map[i].platform_inherit))
+				ae_perm |= acl_inherit_map[i].archive_inherit;
 
-		archive_entry_acl_add_entry(entry,
-		    archive_entry_acl_type, ae_perm, ae_tag,
-		    ae_id, ae_name);
+                }
+
+		acl_get_permset(acl_entry, &acl_permset);
+                for (i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
+			/*
+			 * acl_get_perm() is spelled differently on different
+			 * platforms; see above.
+			 */
+			if (ACL_GET_PERM(acl_permset, acl_perm_map[i].platform_perm))
+				ae_perm |= acl_perm_map[i].archive_perm;
+		}
+
+		archive_entry_acl_add_entry(entry, entry_acl_type,
+					    ae_perm, ae_tag,
+					    ae_id, ae_name);
 
 		s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
 	}
+	return (ARCHIVE_OK);
 }
 #else
 static int
-setup_acls_posix1e(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+setup_acls(struct archive_read_disk *a,
+    struct archive_entry *entry, int *fd)
 {
 	(void)a;      /* UNUSED */
 	(void)entry;  /* UNUSED */
@@ -568,7 +750,7 @@ setup_xattr(struct archive_read_disk *a,
 
 static int
 setup_xattrs(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	char *list, *p;
 	const char *path;
@@ -578,16 +760,30 @@ setup_xattrs(struct archive_read_disk *a,
 	if (path == NULL)
 		path = archive_entry_pathname(entry);
 
+	if (*fd < 0 && a->tree != NULL) {
+		if (a->follow_symlinks ||
+		    archive_entry_filetype(entry) != AE_IFLNK)
+			*fd = a->open_on_current_dir(a->tree, path,
+				O_RDONLY | O_NONBLOCK);
+		if (*fd < 0) {
+			if (a->tree_enter_working_dir(a->tree) != 0) {
+				archive_set_error(&a->archive, errno,
+				    "Couldn't access %s", path);
+				return (ARCHIVE_FAILED);
+			}
+		}
+	}
+
 #if HAVE_FLISTXATTR
-	if (fd >= 0)
-		list_size = flistxattr(fd, NULL, 0);
+	if (*fd >= 0)
+		list_size = flistxattr(*fd, NULL, 0);
 	else if (!a->follow_symlinks)
 		list_size = llistxattr(path, NULL, 0);
 	else
 		list_size = listxattr(path, NULL, 0);
 #elif HAVE_FLISTEA
-	if (fd >= 0)
-		list_size = flistea(fd, NULL, 0);
+	if (*fd >= 0)
+		list_size = flistea(*fd, NULL, 0);
 	else if (!a->follow_symlinks)
 		list_size = llistea(path, NULL, 0);
 	else
@@ -611,15 +807,15 @@ setup_xattrs(struct archive_read_disk *a,
 	}
 
 #if HAVE_FLISTXATTR
-	if (fd >= 0)
-		list_size = flistxattr(fd, list, list_size);
+	if (*fd >= 0)
+		list_size = flistxattr(*fd, list, list_size);
 	else if (!a->follow_symlinks)
 		list_size = llistxattr(path, list, list_size);
 	else
 		list_size = listxattr(path, list, list_size);
 #elif HAVE_FLISTEA
-	if (fd >= 0)
-		list_size = flistea(fd, list, list_size);
+	if (*fd >= 0)
+		list_size = flistea(*fd, list, list_size);
 	else if (!a->follow_symlinks)
 		list_size = llistea(path, list, list_size);
 	else
@@ -637,7 +833,7 @@ setup_xattrs(struct archive_read_disk *a,
 		if (strncmp(p, "system.", 7) == 0 ||
 				strncmp(p, "xfsroot.", 8) == 0)
 			continue;
-		setup_xattr(a, entry, p, fd);
+		setup_xattr(a, entry, p, *fd);
 	}
 
 	free(list);
@@ -698,6 +894,7 @@ setup_xattr(struct archive_read_disk *a, struct archive_entry *entry,
 		size = extattr_get_file(accpath, namespace, name, value, size);
 
 	if (size == -1) {
+		free(value);
 		archive_set_error(&a->archive, errno,
 		    "Couldn't read extended attribute");
 		return (ARCHIVE_WARN);
@@ -711,7 +908,7 @@ setup_xattr(struct archive_read_disk *a, struct archive_entry *entry,
 
 static int
 setup_xattrs(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	char buff[512];
 	char *list, *p;
@@ -723,8 +920,22 @@ setup_xattrs(struct archive_read_disk *a,
 	if (path == NULL)
 		path = archive_entry_pathname(entry);
 
-	if (fd >= 0)
-		list_size = extattr_list_fd(fd, namespace, NULL, 0);
+	if (*fd < 0 && a->tree != NULL) {
+		if (a->follow_symlinks ||
+		    archive_entry_filetype(entry) != AE_IFLNK)
+			*fd = a->open_on_current_dir(a->tree, path,
+				O_RDONLY | O_NONBLOCK);
+		if (*fd < 0) {
+			if (a->tree_enter_working_dir(a->tree) != 0) {
+				archive_set_error(&a->archive, errno,
+				    "Couldn't access %s", path);
+				return (ARCHIVE_FAILED);
+			}
+		}
+	}
+
+	if (*fd >= 0)
+		list_size = extattr_list_fd(*fd, namespace, NULL, 0);
 	else if (!a->follow_symlinks)
 		list_size = extattr_list_link(path, namespace, NULL, 0);
 	else
@@ -746,8 +957,8 @@ setup_xattrs(struct archive_read_disk *a,
 		return (ARCHIVE_FATAL);
 	}
 
-	if (fd >= 0)
-		list_size = extattr_list_fd(fd, namespace, list, list_size);
+	if (*fd >= 0)
+		list_size = extattr_list_fd(*fd, namespace, list, list_size);
 	else if (!a->follow_symlinks)
 		list_size = extattr_list_link(path, namespace, list, list_size);
 	else
@@ -769,7 +980,7 @@ setup_xattrs(struct archive_read_disk *a,
 		name = buff + strlen(buff);
 		memcpy(name, p + 1, len);
 		name[len] = '\0';
-		setup_xattr(a, entry, namespace, name, buff, fd);
+		setup_xattr(a, entry, namespace, name, buff, *fd);
 		p += 1 + len;
 	}
 
@@ -784,7 +995,7 @@ setup_xattrs(struct archive_read_disk *a,
  */
 static int
 setup_xattrs(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	(void)a;     /* UNUSED */
 	(void)entry; /* UNUSED */
@@ -813,35 +1024,41 @@ setup_xattrs(struct archive_read_disk *a,
 
 static int
 setup_sparse(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	char buff[4096];
 	struct fiemap *fm;
 	struct fiemap_extent *fe;
 	int64_t size;
 	int count, do_fiemap;
-	int initial_fd = fd;
 	int exit_sts = ARCHIVE_OK;
 
 	if (archive_entry_filetype(entry) != AE_IFREG
 	    || archive_entry_size(entry) <= 0
 	    || archive_entry_hardlink(entry) != NULL)
 		return (ARCHIVE_OK);
 
-	if (fd < 0) {
+	if (*fd < 0) {
 		const char *path;
 
 		path = archive_entry_sourcepath(entry);
 		if (path == NULL)
 			path = archive_entry_pathname(entry);
-		fd = open(path, O_RDONLY | O_NONBLOCK);
-		if (fd < 0) {
+		if (a->tree != NULL)
+			*fd = a->open_on_current_dir(a->tree, path,
+				O_RDONLY | O_NONBLOCK | O_CLOEXEC);
+		else
+			*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
+		if (*fd < 0) {
 			archive_set_error(&a->archive, errno,
 			    "Can't open `%s'", path);
 			return (ARCHIVE_FAILED);
 		}
+		__archive_ensure_cloexec_flag(*fd);
 	}
 
+	/* Initialize buffer to avoid the error valgrind complains about. */
+	memset(buff, 0, sizeof(buff));
 	count = (sizeof(buff) - sizeof(*fm))/sizeof(*fe);
 	fm = (struct fiemap *)buff;
 	fm->fm_start = 0;
@@ -853,29 +1070,22 @@ setup_sparse(struct archive_read_disk *a,
 	for (;;) {
 		int i, r;
 
-		r = ioctl(fd, FS_IOC_FIEMAP, fm); 
+		r = ioctl(*fd, FS_IOC_FIEMAP, fm); 
 		if (r < 0) {
-			/* When errno is ENOTTY, it is better we should
-			 * return ARCHIVE_OK because an earlier version
-			 *(<2.6.28) cannot perfom FS_IOC_FIEMAP.
-			 * We should also check if errno is EOPNOTSUPP,
-			 * it means "Operation not supported". */
-			if (errno != ENOTTY && errno != EOPNOTSUPP) {
-				archive_set_error(&a->archive, errno,
-				    "FIEMAP failed");
-				exit_sts = ARCHIVE_FAILED;
-			}
+			/* When something error happens, it is better we
+			 * should return ARCHIVE_OK because an earlier
+			 * version(<2.6.28) cannot perfom FS_IOC_FIEMAP. */
 			goto exit_setup_sparse;
 		}
 		if (fm->fm_mapped_extents == 0)
 			break;
 		fe = fm->fm_extents;
-		for (i = 0; i < fm->fm_mapped_extents; i++, fe++) {
+		for (i = 0; i < (int)fm->fm_mapped_extents; i++, fe++) {
 			if (!(fe->fe_flags & FIEMAP_EXTENT_UNWRITTEN)) {
 				/* The fe_length of the last block does not
 				 * adjust itself to its size files. */
 				int64_t length = fe->fe_length;
-				if (fe->fe_logical + length > size)
+				if (fe->fe_logical + length > (uint64_t)size)
 					length -= fe->fe_logical + length - size;
 				if (fe->fe_logical == 0 && length == size) {
 					/* This is not sparse. */
@@ -896,8 +1106,6 @@ setup_sparse(struct archive_read_disk *a,
 			break;
 	}
 exit_setup_sparse:
-	if (initial_fd != fd)
-		close(fd);
 	return (exit_sts);
 }
 
@@ -909,10 +1117,9 @@ setup_sparse(struct archive_read_disk *a,
 
 static int
 setup_sparse(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	int64_t size;
-	int initial_fd = fd;
 	off_t initial_off; /* FreeBSD/Solaris only, so off_t okay here */
 	off_t off_s, off_e; /* FreeBSD/Solaris only, so off_t okay here */
 	int exit_sts = ARCHIVE_OK;
@@ -923,33 +1130,50 @@ setup_sparse(struct archive_read_disk *a,
 		return (ARCHIVE_OK);
 
 	/* Does filesystem support the reporting of hole ? */
-	if (fd >= 0) {
-		if (fpathconf(fd, _PC_MIN_HOLE_SIZE) <= 0)
+	if (*fd < 0 && a->tree != NULL) {
+		const char *path;
+
+		path = archive_entry_sourcepath(entry);
+		if (path == NULL)
+			path = archive_entry_pathname(entry);
+		*fd = a->open_on_current_dir(a->tree, path,
+				O_RDONLY | O_NONBLOCK);
+		if (*fd < 0) {
+			archive_set_error(&a->archive, errno,
+			    "Can't open `%s'", path);
+			return (ARCHIVE_FAILED);
+		}
+	}
+
+	if (*fd >= 0) {
+		if (fpathconf(*fd, _PC_MIN_HOLE_SIZE) <= 0)
 			return (ARCHIVE_OK);
-		initial_off = lseek(fd, 0, SEEK_CUR);
+		initial_off = lseek(*fd, 0, SEEK_CUR);
 		if (initial_off != 0)
-			lseek(fd, 0, SEEK_SET);
+			lseek(*fd, 0, SEEK_SET);
 	} else {
 		const char *path;
 
 		path = archive_entry_sourcepath(entry);
 		if (path == NULL)
 			path = archive_entry_pathname(entry);
+			
 		if (pathconf(path, _PC_MIN_HOLE_SIZE) <= 0)
 			return (ARCHIVE_OK);
-		fd = open(path, O_RDONLY | O_NONBLOCK);
-		if (fd < 0) {
+		*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
+		if (*fd < 0) {
 			archive_set_error(&a->archive, errno,
 			    "Can't open `%s'", path);
 			return (ARCHIVE_FAILED);
 		}
+		__archive_ensure_cloexec_flag(*fd);
 		initial_off = 0;
 	}
 
 	off_s = 0;
 	size = archive_entry_size(entry);
 	while (off_s < size) {
-		off_s = lseek(fd, off_s, SEEK_DATA);
+		off_s = lseek(*fd, off_s, SEEK_DATA);
 		if (off_s == (off_t)-1) {
 			if (errno == ENXIO)
 				break;/* no more hole */
@@ -958,10 +1182,10 @@ setup_sparse(struct archive_read_disk *a,
 			exit_sts = ARCHIVE_FAILED;
 			goto exit_setup_sparse;
 		}
-		off_e = lseek(fd, off_s, SEEK_HOLE);
-		if (off_s == (off_t)-1) {
+		off_e = lseek(*fd, off_s, SEEK_HOLE);
+		if (off_e == (off_t)-1) {
 			if (errno == ENXIO) {
-				off_e = lseek(fd, 0, SEEK_END);
+				off_e = lseek(*fd, 0, SEEK_END);
 				if (off_e != (off_t)-1)
 					break;/* no more data */
 			}
@@ -977,10 +1201,7 @@ setup_sparse(struct archive_read_disk *a,
 		off_s = off_e;
 	}
 exit_setup_sparse:
-	if (initial_fd != fd)
-		close(fd);
-	else
-		lseek(fd, initial_off, SEEK_SET);
+	lseek(*fd, initial_off, SEEK_SET);
 	return (exit_sts);
 }
 
@@ -991,7 +1212,7 @@ setup_sparse(struct archive_read_disk *a,
  */
 static int
 setup_sparse(struct archive_read_disk *a,
-    struct archive_entry *entry, int fd)
+    struct archive_entry *entry, int *fd)
 {
 	(void)a;     /* UNUSED */
 	(void)entry; /* UNUSED */