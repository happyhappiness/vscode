@@ -26,23 +26,14 @@
  */
 
 #include "archive_platform.h"
-__FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 201084 2009-12-28 02:14:09Z kientzle $");
+__FBSDID("$FreeBSD");
 
 /* This is the tree-walking code for POSIX systems. */
 #if !defined(_WIN32) || defined(__CYGWIN__)
 
 #ifdef HAVE_SYS_TYPES_H
-/* Mac OSX requires sys/types.h before sys/acl.h. */
 #include <sys/types.h>
 #endif
-#ifdef HAVE_SYS_ACL_H
-#include <sys/acl.h>
-#endif
-#ifdef HAVE_DARWIN_ACL
-#include <membership.h>
-#include <grp.h>
-#include <pwd.h>
-#endif
 #ifdef HAVE_SYS_EXTATTR_H
 #include <sys/extattr.h>
 #endif
@@ -63,9 +54,6 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #ifdef HAVE_SYS_EA_H
 #include <sys/ea.h>
 #endif
-#ifdef HAVE_ACL_LIBACL_H
-#include <acl/libacl.h>
-#endif
 #ifdef HAVE_COPYFILE_H
 #include <copyfile.h>
 #endif
@@ -113,27 +101,6 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #define O_CLOEXEC	0
 #endif
 
-/*
- * Linux and FreeBSD plug this obvious hole in POSIX.1e in
- * different ways.
- */
-#if HAVE_ACL_GET_PERM
-#define	ACL_GET_PERM acl_get_perm
-#elif HAVE_ACL_GET_PERM_NP
-#define	ACL_GET_PERM acl_get_perm_np
-#endif
-
-/* NFSv4 platform ACL type */
-#if HAVE_SUN_ACL
-#define	ARCHIVE_PLATFORM_ACL_TYPE_NFS4	ACE_T
-#elif HAVE_DARWIN_ACL
-#define	ARCHIVE_PLATFORM_ACL_TYPE_NFS4	ACL_TYPE_EXTENDED
-#elif HAVE_ACL_TYPE_NFS4
-#define	ARCHIVE_PLATFORM_ACL_TYPE_NFS4	ACL_TYPE_NFS4
-#endif
-
-static int setup_acls(struct archive_read_disk *,
-    struct archive_entry *, int *fd);
 static int setup_mac_metadata(struct archive_read_disk *,
     struct archive_entry *, int *fd);
 static int setup_xattrs(struct archive_read_disk *,
@@ -145,6 +112,45 @@ static int setup_sparse_fiemap(struct archive_read_disk *,
     struct archive_entry *, int *fd);
 #endif
 
+#if !ARCHIVE_ACL_SUPPORT
+int
+archive_read_disk_entry_setup_acls(struct archive_read_disk *a,
+    struct archive_entry *entry, int *fd)
+{
+	(void)a;      /* UNUSED */
+	(void)entry;  /* UNUSED */
+	(void)fd;     /* UNUSED */
+	return (ARCHIVE_OK);
+}
+#endif
+
+/*
+ * Enter working directory and return working pathname of archive_entry.
+ * If a pointer to an integer is provided and its value is below zero
+ * open a file descriptor on this pahtname.
+ */
+const char *
+archive_read_disk_entry_setup_path(struct archive_read_disk *a,
+    struct archive_entry *entry, int *fd)
+{
+	const char *path;
+
+	path = archive_entry_sourcepath(entry);
+
+	if (path == NULL || (a->tree != NULL &&
+	    a->tree_enter_working_dir(a->tree) != 0))
+		path = archive_entry_pathname(entry);
+	if (path == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		   "Couldn't determine path");
+	} else if (fd != NULL && *fd < 0 && a->tree != NULL &&
+	    (a->follow_symlinks || archive_entry_filetype(entry) != AE_IFLNK)) {
+		*fd = a->open_on_current_dir(a->tree, path,
+		    O_RDONLY | O_NONBLOCK);
+	}
+	return (path);
+}
+
 int
 archive_read_disk_entry_from_file(struct archive *_a,
     struct archive_entry *entry,
@@ -279,7 +285,7 @@ archive_read_disk_entry_from_file(struct archive *_a,
 
 	r = 0;
 	if ((a->flags & ARCHIVE_READDISK_NO_ACL) == 0)
-		r = setup_acls(a, entry, &fd);
+		r = archive_read_disk_entry_setup_acls(a, entry, &fd);
 	if ((a->flags & ARCHIVE_READDISK_NO_XATTR) == 0) {
 		r1 = setup_xattrs(a, entry, &fd);
 		if (r1 < r)
@@ -328,19 +334,10 @@ setup_mac_metadata(struct archive_read_disk *a,
 	struct archive_string tempfile;
 
 	(void)fd; /* UNUSED */
-	name = archive_entry_sourcepath(entry);
+
+	name = archive_read_disk_entry_setup_path(a, entry, NULL);
 	if (name == NULL)
-		name = archive_entry_pathname(entry);
-	else if (a->tree != NULL && a->tree_enter_working_dir(a->tree) != 0) {
-		archive_set_error(&a->archive, errno,
-			    "Can't change dir to read extended attributes");
-			return (ARCHIVE_FAILED);
-	}
-	if (name == NULL) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Can't open file to read extended attributes: No name");
 		return (ARCHIVE_WARN);
-	}
 
 	/* Short-circuit if there's nothing to do. */
 	have_attrs = copyfile(name, NULL, 0, copyfile_flags | COPYFILE_CHECK);
@@ -426,996 +423,10 @@ setup_mac_metadata(struct archive_read_disk *a,
 }
 #endif
 
-#if HAVE_DARWIN_ACL
-static int translate_guid(struct archive *, acl_entry_t,
-    int *, int *, const char **);
-
-static void add_trivial_nfs4_acl(struct archive_entry *);
-#endif
-
-#if HAVE_SUN_ACL
-static int
-sun_acl_is_trivial(acl_t *, mode_t, int *trivialp);
-#endif
-
-#if HAVE_POSIX_ACL || HAVE_NFS4_ACL
-static int translate_acl(struct archive_read_disk *a,
-    struct archive_entry *entry,
-#if HAVE_SUN_ACL
-    acl_t *acl,
-#else
-    acl_t acl,
-#endif
-    int archive_entry_acl_type);
-
-static int
-setup_acls(struct archive_read_disk *a,
-    struct archive_entry *entry, int *fd)
-{
-	const char	*accpath;
-#if HAVE_SUN_ACL
-	acl_t		*acl;
-#else
-	acl_t		acl;
-#endif
-	int		r;
-
-	accpath = NULL;
-
-#if HAVE_SUN_ACL || HAVE_DARWIN_ACL || HAVE_ACL_GET_FD_NP
-	if (*fd < 0)
-#else
-	/* For default ACLs on Linux we need reachable accpath */
-	if (*fd < 0 || S_ISDIR(archive_entry_mode(entry)))
-#endif
-	{
-		accpath = archive_entry_sourcepath(entry);
-		if (accpath == NULL || (a->tree != NULL &&
-		    a->tree_enter_working_dir(a->tree) != 0))
-			accpath = archive_entry_pathname(entry);
-		if (accpath == NULL) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "Couldn't determine file path to read ACLs");
-			return (ARCHIVE_WARN);
-		}
-		if (a->tree != NULL &&
-#if !HAVE_SUN_ACL && !HAVE_DARWIN_ACL && !HAVE_ACL_GET_FD_NP
-		    *fd < 0 &&
-#endif
-		    (a->follow_symlinks ||
-		    archive_entry_filetype(entry) != AE_IFLNK)) {
-			*fd = a->open_on_current_dir(a->tree,
-			    accpath, O_RDONLY | O_NONBLOCK);
-		}
-	}
-
-	archive_entry_acl_clear(entry);
-
-	acl = NULL;
-
-#if HAVE_NFS4_ACL
-	/* Try NFSv4 ACL first. */
-	if (*fd >= 0)
-#if HAVE_SUN_ACL
-		/* Solaris reads both POSIX.1e and NFSv4 ACL here */
-		facl_get(*fd, 0, &acl);
-#elif HAVE_ACL_GET_FD_NP
-		acl = acl_get_fd_np(*fd, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
-#else
-		acl = acl_get_fd(*fd);
-#endif
-#if HAVE_ACL_GET_LINK_NP
-	else if (!a->follow_symlinks)
-		acl = acl_get_link_np(accpath, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
-#else
-	else if ((!a->follow_symlinks)
-	    && (archive_entry_filetype(entry) == AE_IFLNK))
-		/* We can't get the ACL of a symlink, so we assume it can't
-		   have one. */
-		acl = NULL;
-#endif
-	else
-#if HAVE_SUN_ACL
-		/* Solaris reads both POSIX.1e and NFSv4 ACLs here */
-		acl_get(accpath, 0, &acl);
-#else
-		acl = acl_get_file(accpath, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
-#endif
-
-
-#if HAVE_ACL_IS_TRIVIAL_NP || HAVE_SUN_ACL
-	/* Ignore "trivial" ACLs that just mirror the file mode. */
-	if (acl != NULL) {
-#if HAVE_SUN_ACL
-		if (sun_acl_is_trivial(acl, archive_entry_mode(entry),
-		    &r) == 0 && r == 1)
-#elif HAVE_ACL_IS_TRIVIAL_NP
-		if (acl_is_trivial_np(acl, &r) == 0 && r == 1)
-#endif
-		{
-			acl_free(acl);
-			acl = NULL;
-			/*
-			 * Simultaneous NFSv4 and POSIX.1e ACLs for the same
-			 * entry are not allowed, so we should return here
-			 */
-			return (ARCHIVE_OK);
-		}
-	}
-#endif	/* HAVE_ACL_IS_TRIVIAL_NP || HAVE_SUN_ACL */
-	if (acl != NULL) {
-		r = translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_NFS4);
-		acl_free(acl);
-		if (r != ARCHIVE_OK) {
-			archive_set_error(&a->archive, errno,
-			    "Couldn't translate "
-#if !HAVE_SUN_ACL
-			    "NFSv4 "
-#endif
-			    "ACLs");
-		}
-#if HAVE_DARWIN_ACL
-		/*
-		 * Because Mac OS doesn't support owner@, group@ and everyone@
-		 * ACLs we need to add NFSv4 ACLs mirroring the file mode to
-		 * the archive entry. Otherwise extraction on non-Mac platforms
-		 * would lead to an invalid file mode.
-		 */
-		if ((archive_entry_acl_types(entry) &
-		    ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0)
-			add_trivial_nfs4_acl(entry);
-#endif
-		return (r);
-	}
-#endif	/* HAVE_NFS4_ACL */
-
-#if HAVE_POSIX_ACL
-	/* This code path is skipped on MacOS and Solaris */
+#if ARCHIVE_XATTR_LINUX || ARCHIVE_XATTR_DARWIN || ARCHIVE_XATTR_AIX
 
-	/* Retrieve access ACL from file. */
-	if (*fd >= 0)
-		acl = acl_get_fd(*fd);
-#if HAVE_ACL_GET_LINK_NP
-	else if (!a->follow_symlinks)
-		acl = acl_get_link_np(accpath, ACL_TYPE_ACCESS);
-#else
-	else if ((!a->follow_symlinks)
-	    && (archive_entry_filetype(entry) == AE_IFLNK))
-		/* We can't get the ACL of a symlink, so we assume it can't
-		   have one. */
-		acl = NULL;
-#endif
-	else
-		acl = acl_get_file(accpath, ACL_TYPE_ACCESS);
-
-#if HAVE_ACL_IS_TRIVIAL_NP
-	/* Ignore "trivial" ACLs that just mirror the file mode. */
-	if (acl != NULL && acl_is_trivial_np(acl, &r) == 0) {
-		if (r) {
-			acl_free(acl);
-			acl = NULL;
-		}
-	}
-#endif
-
-	if (acl != NULL) {
-		r = translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
-		acl_free(acl);
-		acl = NULL;
-		if (r != ARCHIVE_OK) {
-			archive_set_error(&a->archive, errno,
-			    "Couldn't translate access ACLs");
-			return (r);
-		}
-	}
-
-	/* Only directories can have default ACLs. */
-	if (S_ISDIR(archive_entry_mode(entry))) {
-#if HAVE_ACL_GET_FD_NP
-		if (*fd >= 0)
-			acl = acl_get_fd_np(*fd, ACL_TYPE_DEFAULT);
-		else
-#endif
-		acl = acl_get_file(accpath, ACL_TYPE_DEFAULT);
-		if (acl != NULL) {
-			r = translate_acl(a, entry, acl,
-			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);
-			acl_free(acl);
-			if (r != ARCHIVE_OK) {
-				archive_set_error(&a->archive, errno,
-				    "Couldn't translate default ACLs");
-				return (r);
-			}
-		}
-	}
-#endif	/* HAVE_POSIX_ACL */
-	return (ARCHIVE_OK);
-}
-
-/*
- * Translate system ACL permissions into libarchive internal structure
- */
-static const struct {
-	const int archive_perm;
-	const int platform_perm;
-} acl_perm_map[] = {
-#if HAVE_SUN_ACL	/* Solaris NFSv4 ACL permissions */
-	{ARCHIVE_ENTRY_ACL_EXECUTE, ACE_EXECUTE},
-	{ARCHIVE_ENTRY_ACL_READ_DATA, ACE_READ_DATA},
-	{ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACE_LIST_DIRECTORY},
-	{ARCHIVE_ENTRY_ACL_WRITE_DATA, ACE_WRITE_DATA},
-	{ARCHIVE_ENTRY_ACL_ADD_FILE, ACE_ADD_FILE},
-	{ARCHIVE_ENTRY_ACL_APPEND_DATA, ACE_APPEND_DATA},
-	{ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACE_ADD_SUBDIRECTORY},
-	{ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACE_READ_NAMED_ATTRS},
-	{ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACE_WRITE_NAMED_ATTRS},
-	{ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACE_DELETE_CHILD},
-	{ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACE_READ_ATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACE_WRITE_ATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_DELETE, ACE_DELETE},
-	{ARCHIVE_ENTRY_ACL_READ_ACL, ACE_READ_ACL},
-	{ARCHIVE_ENTRY_ACL_WRITE_ACL, ACE_WRITE_ACL},
-	{ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACE_WRITE_OWNER},
-	{ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACE_SYNCHRONIZE}
-#elif HAVE_DARWIN_ACL	/* MacOS ACL permissions */
-	{ARCHIVE_ENTRY_ACL_READ_DATA, ACL_READ_DATA},
-	{ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACL_LIST_DIRECTORY},
-	{ARCHIVE_ENTRY_ACL_WRITE_DATA, ACL_WRITE_DATA},
-	{ARCHIVE_ENTRY_ACL_ADD_FILE, ACL_ADD_FILE},
-	{ARCHIVE_ENTRY_ACL_EXECUTE, ACL_EXECUTE},
-	{ARCHIVE_ENTRY_ACL_DELETE, ACL_DELETE},
-	{ARCHIVE_ENTRY_ACL_APPEND_DATA, ACL_APPEND_DATA},
-	{ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACL_ADD_SUBDIRECTORY},
-	{ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACL_DELETE_CHILD},
-	{ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACL_READ_ATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACL_WRITE_ATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACL_READ_EXTATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACL_WRITE_EXTATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_READ_ACL, ACL_READ_SECURITY},
-	{ARCHIVE_ENTRY_ACL_WRITE_ACL, ACL_WRITE_SECURITY},
-	{ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACL_CHANGE_OWNER},
-	{ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACL_SYNCHRONIZE}
-#else	/* POSIX.1e ACL permissions */
-	{ARCHIVE_ENTRY_ACL_EXECUTE, ACL_EXECUTE},
-	{ARCHIVE_ENTRY_ACL_WRITE, ACL_WRITE},
-	{ARCHIVE_ENTRY_ACL_READ, ACL_READ},
-#if HAVE_ACL_TYPE_NFS4	/* FreeBSD NFSv4 ACL permissions */
-	{ARCHIVE_ENTRY_ACL_READ_DATA, ACL_READ_DATA},
-	{ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACL_LIST_DIRECTORY},
-	{ARCHIVE_ENTRY_ACL_WRITE_DATA, ACL_WRITE_DATA},
-	{ARCHIVE_ENTRY_ACL_ADD_FILE, ACL_ADD_FILE},
-	{ARCHIVE_ENTRY_ACL_APPEND_DATA, ACL_APPEND_DATA},
-	{ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACL_ADD_SUBDIRECTORY},
-	{ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACL_READ_NAMED_ATTRS},
-	{ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACL_WRITE_NAMED_ATTRS},
-	{ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACL_DELETE_CHILD},
-	{ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACL_READ_ATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACL_WRITE_ATTRIBUTES},
-	{ARCHIVE_ENTRY_ACL_DELETE, ACL_DELETE},
-	{ARCHIVE_ENTRY_ACL_READ_ACL, ACL_READ_ACL},
-	{ARCHIVE_ENTRY_ACL_WRITE_ACL, ACL_WRITE_ACL},
-	{ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACL_WRITE_OWNER},
-	{ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACL_SYNCHRONIZE}
-#endif
-#endif	/* !HAVE_SUN_ACL && !HAVE_DARWIN_ACL */
-};
-
-#if HAVE_NFS4_ACL
-/*
- * Translate system NFSv4 inheritance flags into libarchive internal structure
- */
-static const struct {
-	const int archive_inherit;
-	const int platform_inherit;
-} acl_inherit_map[] = {
-#if HAVE_SUN_ACL	/* Solaris ACL inheritance flags */
-	{ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACE_FILE_INHERIT_ACE},
-	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACE_DIRECTORY_INHERIT_ACE},
-	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACE_NO_PROPAGATE_INHERIT_ACE},
-	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACE_INHERIT_ONLY_ACE},
-	{ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS, ACE_SUCCESSFUL_ACCESS_ACE_FLAG},
-	{ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS, ACE_FAILED_ACCESS_ACE_FLAG},
-	{ARCHIVE_ENTRY_ACL_ENTRY_INHERITED, ACE_INHERITED_ACE}
-#elif HAVE_DARWIN_ACL	/* MacOS NFSv4 inheritance flags */
-	{ARCHIVE_ENTRY_ACL_ENTRY_INHERITED, ACL_ENTRY_INHERITED},
-	{ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_FILE_INHERIT},
-	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACL_ENTRY_DIRECTORY_INHERIT},
-	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACL_ENTRY_LIMIT_INHERIT},
-	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACL_ENTRY_ONLY_INHERIT}
-#else	/* FreeBSD NFSv4 ACL inheritance flags */
-	{ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_FILE_INHERIT},
-	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACL_ENTRY_DIRECTORY_INHERIT},
-	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACL_ENTRY_NO_PROPAGATE_INHERIT},
-	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACL_ENTRY_INHERIT_ONLY},
-	{ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS, ACL_ENTRY_SUCCESSFUL_ACCESS},
-	{ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS, ACL_ENTRY_FAILED_ACCESS},
-	{ARCHIVE_ENTRY_ACL_ENTRY_INHERITED, ACL_ENTRY_INHERITED}
-#endif	/* !HAVE_SUN_ACL && !HAVE_DARWIN_ACL */
-};
-#endif	/* HAVE_NFS4_ACL */
-
-#if HAVE_DARWIN_ACL
-static int translate_guid(struct archive *a, acl_entry_t acl_entry,
-    int *ae_id, int *ae_tag, const char **ae_name)
-{
-	void *q;
-	uid_t ugid;
-	int r, idtype;
-	struct passwd *pwd;
-	struct group *grp;
-
-	q = acl_get_qualifier(acl_entry);
-	if (q == NULL)
-		return (1);
-	r = mbr_uuid_to_id((const unsigned char *)q, &ugid, &idtype);
-	if (r != 0) {
-		acl_free(q);
-		return (1);
-	}
-	if (idtype == ID_TYPE_UID) {
-		*ae_tag = ARCHIVE_ENTRY_ACL_USER;
-		pwd = getpwuuid(q);
-		if (pwd == NULL) {
-			*ae_id = ugid;
-			*ae_name = NULL;
-		} else {
-			*ae_id = pwd->pw_uid;
-			*ae_name = archive_read_disk_uname(a, *ae_id);
-		}
-	} else if (idtype == ID_TYPE_GID) {
-		*ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
-		grp = getgruuid(q);
-		if (grp == NULL) {
-			*ae_id = ugid;
-			*ae_name = NULL;
-		} else {
-			*ae_id = grp->gr_gid;
-			*ae_name = archive_read_disk_gname(a, *ae_id);
-		}
-	} else
-		r = 1;
-
-	acl_free(q);
-	return (r);
-}
-
-/*
- * Add trivial NFSv4 ACL entries from mode
- */
-static void
-add_trivial_nfs4_acl(struct archive_entry *entry)
-{
-	mode_t mode;
-	int i;
-	const int rperm = ARCHIVE_ENTRY_ACL_READ_DATA;
-	const int wperm = ARCHIVE_ENTRY_ACL_WRITE_DATA |
-	    ARCHIVE_ENTRY_ACL_APPEND_DATA;
-	const int eperm = ARCHIVE_ENTRY_ACL_EXECUTE;
-	const int pubset = ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES |
-	    ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS |
-	    ARCHIVE_ENTRY_ACL_READ_ACL |
-	    ARCHIVE_ENTRY_ACL_SYNCHRONIZE;
-	const int ownset = pubset | ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES |
-	    ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS |
-	    ARCHIVE_ENTRY_ACL_WRITE_ACL |
-	    ARCHIVE_ENTRY_ACL_WRITE_OWNER;
-
-	struct {
-	    const int type;
-	    const int tag;
-	    int permset;
-	} tacl_entry[] = {
-	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_USER_OBJ, 0},
-	    {ARCHIVE_ENTRY_ACL_TYPE_DENY, ARCHIVE_ENTRY_ACL_USER_OBJ, 0},
-	    {ARCHIVE_ENTRY_ACL_TYPE_DENY, ARCHIVE_ENTRY_ACL_GROUP_OBJ, 0},
-	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_USER_OBJ, ownset},
-	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_GROUP_OBJ, pubset},
-	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_EVERYONE, pubset}
-	};
-
-	mode = archive_entry_mode(entry);
-
-	/* Permissions for everyone@ */
-	if (mode & 0004)
-		tacl_entry[5].permset |= rperm;
-	if (mode & 0002)
-		tacl_entry[5].permset |= wperm;
-	if (mode & 0001)
-		tacl_entry[5].permset |= eperm;
-
-	/* Permissions for group@ */
-	if (mode & 0040)
-		tacl_entry[4].permset |= rperm;
-	else if (mode & 0004)
-		tacl_entry[2].permset |= rperm;
-	if (mode & 0020)
-		tacl_entry[4].permset |= wperm;
-	else if (mode & 0002)
-		tacl_entry[2].permset |= wperm;
-	if (mode & 0010)
-		tacl_entry[4].permset |= eperm;
-	else if (mode & 0001)
-		tacl_entry[2].permset |= eperm;
-
-	/* Permissions for owner@ */
-	if (mode & 0400) {
-		tacl_entry[3].permset |= rperm;
-		if (!(mode & 0040) && (mode & 0004))
-			tacl_entry[0].permset |= rperm;
-	} else if ((mode & 0040) || (mode & 0004))
-		tacl_entry[1].permset |= rperm;
-	if (mode & 0200) {
-		tacl_entry[3].permset |= wperm;
-		if (!(mode & 0020) && (mode & 0002))
-			tacl_entry[0].permset |= wperm;
-	} else if ((mode & 0020) || (mode & 0002))
-		tacl_entry[1].permset |= wperm;
-	if (mode & 0100) {
-		tacl_entry[3].permset |= eperm;
-		if (!(mode & 0010) && (mode & 0001))
-			tacl_entry[0].permset |= eperm;
-	} else if ((mode & 0010) || (mode & 0001))
-		tacl_entry[1].permset |= eperm;
-
-	for (i = 0; i < 6; i++) {
-		if (tacl_entry[i].permset != 0) {
-			archive_entry_acl_add_entry(entry,
-			    tacl_entry[i].type, tacl_entry[i].permset,
-			    tacl_entry[i].tag, -1, NULL);
-		}
-	}
-
-	return;
-}
-#elif HAVE_SUN_ACL
-/*
- * Check if acl is trivial
- * This is a FreeBSD acl_is_trivial_np() implementation for Solaris
- */
-static int
-sun_acl_is_trivial(acl_t *acl, mode_t mode, int *trivialp)
-{
-	int i, p;
-	const uint32_t rperm = ACE_READ_DATA;
-	const uint32_t wperm = ACE_WRITE_DATA | ACE_APPEND_DATA;
-	const uint32_t eperm = ACE_EXECUTE;
-	const uint32_t pubset = ACE_READ_ATTRIBUTES | ACE_READ_NAMED_ATTRS |
-	    ACE_READ_ACL | ACE_SYNCHRONIZE;
-	const uint32_t ownset = pubset | ACE_WRITE_ATTRIBUTES |
-	    ACE_WRITE_NAMED_ATTRS | ACE_WRITE_ACL | ACE_WRITE_OWNER;
-
-	ace_t *ace;
-	ace_t tace[6];
-
-	if (acl == NULL || trivialp == NULL)
-		return (-1);
-
-	*trivialp = 0;
-
-	/* ACL_IS_TRIVIAL flag must be set for both POSIX.1e and NFSv4 ACLs */
-	if ((acl->acl_flags & ACL_IS_TRIVIAL) == 0)
-		return (0);
-
-	/*
-	 * POSIX.1e ACLs marked with ACL_IS_TRIVIAL are compatible with
-	 * FreeBSD acl_is_trivial_np(). On Solaris they have 4 entries,
-	 * including mask.
-	 */
-	if (acl->acl_type == ACLENT_T) {
-		if (acl->acl_cnt == 4)
-			*trivialp = 1;
-		return (0);
-	}
-
-	if (acl->acl_type != ACE_T || acl->acl_entry_size != sizeof(ace_t))
-		return (-1);
-
-	/*
-	 * Continue with checking NFSv4 ACLs
-	 *
-	 * Create list of trivial ace's to be compared
-	 */
-
-	/* owner@ allow pre */
-	tace[0].a_flags = ACE_OWNER;
-	tace[0].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
-	tace[0].a_access_mask = 0;
-
-	/* owner@ deny */
-	tace[1].a_flags = ACE_OWNER;
-	tace[1].a_type = ACE_ACCESS_DENIED_ACE_TYPE;
-	tace[1].a_access_mask = 0;
-
-	/* group@ deny */
-	tace[2].a_flags = ACE_GROUP | ACE_IDENTIFIER_GROUP;
-	tace[2].a_type = ACE_ACCESS_DENIED_ACE_TYPE;
-	tace[2].a_access_mask = 0;
-
-	/* owner@ allow */
-	tace[3].a_flags = ACE_OWNER;
-	tace[3].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
-	tace[3].a_access_mask = ownset;
-
-	/* group@ allow */
-	tace[4].a_flags = ACE_GROUP | ACE_IDENTIFIER_GROUP;
-	tace[4].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
-	tace[4].a_access_mask = pubset;
-
-	/* everyone@ allow */
-	tace[5].a_flags = ACE_EVERYONE;
-	tace[5].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
-	tace[5].a_access_mask = pubset;
-
-	/* Permissions for everyone@ */
-	if (mode & 0004)
-		tace[5].a_access_mask |= rperm;
-	if (mode & 0002)
-		tace[5].a_access_mask |= wperm;
-	if (mode & 0001)
-		tace[5].a_access_mask |= eperm;
-
-	/* Permissions for group@ */
-	if (mode & 0040)
-		tace[4].a_access_mask |= rperm;
-	else if (mode & 0004)
-		tace[2].a_access_mask |= rperm;
-	if (mode & 0020)
-		tace[4].a_access_mask |= wperm;
-	else if (mode & 0002)
-		tace[2].a_access_mask |= wperm;
-	if (mode & 0010)
-		tace[4].a_access_mask |= eperm;
-	else if (mode & 0001)
-		tace[2].a_access_mask |= eperm;
-
-	/* Permissions for owner@ */
-	if (mode & 0400) {
-		tace[3].a_access_mask |= rperm;
-		if (!(mode & 0040) && (mode & 0004))
-			tace[0].a_access_mask |= rperm;
-	} else if ((mode & 0040) || (mode & 0004))
-		tace[1].a_access_mask |= rperm;
-	if (mode & 0200) {
-		tace[3].a_access_mask |= wperm;
-		if (!(mode & 0020) && (mode & 0002))
-			tace[0].a_access_mask |= wperm;
-	} else if ((mode & 0020) || (mode & 0002))
-		tace[1].a_access_mask |= wperm;
-	if (mode & 0100) {
-		tace[3].a_access_mask |= eperm;
-		if (!(mode & 0010) && (mode & 0001))
-			tace[0].a_access_mask |= eperm;
-	} else if ((mode & 0010) || (mode & 0001))
-		tace[1].a_access_mask |= eperm;
-
-	/* Check if the acl count matches */
-	p = 3;
-	for (i = 0; i < 3; i++) {
-		if (tace[i].a_access_mask != 0)
-			p++;
-	}
-	if (acl->acl_cnt != p)
-		return (0);
-
-	p = 0;
-	for (i = 0; i < 6; i++) {
-		if (tace[i].a_access_mask != 0) {
-			ace = &((ace_t *)acl->acl_aclp)[p];
-			/*
-			 * Illumos added ACE_DELETE_CHILD to write perms for
-			 * directories. We have to check against that, too.
-			 */
-			if (ace->a_flags != tace[i].a_flags ||
-			    ace->a_type != tace[i].a_type ||
-			    (ace->a_access_mask != tace[i].a_access_mask &&
-			    ((acl->acl_flags & ACL_IS_DIR) == 0 ||
-			    (tace[i].a_access_mask & wperm) == 0 ||
-			    ace->a_access_mask !=
-			    (tace[i].a_access_mask | ACE_DELETE_CHILD))))
-				return (0);
-			p++;
-		}
-	}
-
-	*trivialp = 1;
-	return (0);
-}
-#endif	/* HAVE_SUN_ACL */
-
-#if HAVE_SUN_ACL
 /*
- * Translate Solaris POSIX.1e and NFSv4 ACLs into libarchive internal ACL
- */
-static int
-translate_acl(struct archive_read_disk *a,
-    struct archive_entry *entry, acl_t *acl, int default_entry_acl_type)
-{
-	int e, i;
-	int ae_id, ae_tag, ae_perm;
-	int entry_acl_type;
-	const char *ae_name;
-	aclent_t *aclent;
-	ace_t *ace;
-
-	(void)default_entry_acl_type;
-
-	if (acl->acl_cnt <= 0)
-		return (ARCHIVE_OK);
-
-	for (e = 0; e < acl->acl_cnt; e++) {
-		ae_name = NULL;
-		ae_tag = 0;
-		ae_perm = 0;
-
-		if (acl->acl_type == ACE_T) {
-			ace = &((ace_t *)acl->acl_aclp)[e];
-			ae_id = ace->a_who;
-
-			switch(ace->a_type) {
-			case ACE_ACCESS_ALLOWED_ACE_TYPE:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
-				break;
-			case ACE_ACCESS_DENIED_ACE_TYPE:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
-				break;
-			case ACE_SYSTEM_AUDIT_ACE_TYPE:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
-				break;
-			case ACE_SYSTEM_ALARM_ACE_TYPE:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
-				break;
-			default:
-				/* Unknown entry type, skip */
-				continue;
-			}
-
-			if ((ace->a_flags & ACE_OWNER) != 0)
-				ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
-			else if ((ace->a_flags & ACE_GROUP) != 0)
-				ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
-			else if ((ace->a_flags & ACE_EVERYONE) != 0)
-				ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
-			else if ((ace->a_flags & ACE_IDENTIFIER_GROUP) != 0) {
-				ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
-				ae_name = archive_read_disk_gname(&a->archive,
-				    ae_id);
-			} else {
-				ae_tag = ARCHIVE_ENTRY_ACL_USER;
-				ae_name = archive_read_disk_uname(&a->archive,
-				    ae_id);
-			}
-
-			for (i = 0; i < (int)(sizeof(acl_inherit_map) /
-			    sizeof(acl_inherit_map[0])); ++i) {
-				if ((ace->a_flags &
-				    acl_inherit_map[i].platform_inherit) != 0)
-					ae_perm |=
-					    acl_inherit_map[i].archive_inherit;
-			}
-
-			for (i = 0; i < (int)(sizeof(acl_perm_map) /
-			    sizeof(acl_perm_map[0])); ++i) {
-				if ((ace->a_access_mask &
-				    acl_perm_map[i].platform_perm) != 0)
-					ae_perm |=
-					    acl_perm_map[i].archive_perm;
-			}
-		} else {
-			aclent = &((aclent_t *)acl->acl_aclp)[e];
-			if ((aclent->a_type & ACL_DEFAULT) != 0)
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DEFAULT;
-			else
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
-			ae_id = aclent->a_id;
-
-			switch(aclent->a_type) {
-			case DEF_USER:
-			case USER:
-				ae_name = archive_read_disk_uname(&a->archive,
-				    ae_id);
-				ae_tag = ARCHIVE_ENTRY_ACL_USER;
-				break;
-			case DEF_GROUP:
-			case GROUP:
-				ae_name = archive_read_disk_gname(&a->archive,
-				    ae_id);
-				ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
-				break;
-			case DEF_CLASS_OBJ:
-			case CLASS_OBJ:
-				ae_tag = ARCHIVE_ENTRY_ACL_MASK;
-				break;
-			case DEF_USER_OBJ:
-			case USER_OBJ:
-				ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
-				break;
-			case DEF_GROUP_OBJ:
-			case GROUP_OBJ:
-				ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
-				break;
-			case DEF_OTHER_OBJ:
-			case OTHER_OBJ:
-				ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
-				break;
-			default:
-				/* Unknown tag type, skip */
-				continue;
-			}
-
-			if ((aclent->a_perm & 1) != 0)
-				ae_perm |= ARCHIVE_ENTRY_ACL_EXECUTE;
-			if ((aclent->a_perm & 2) != 0)
-				ae_perm |= ARCHIVE_ENTRY_ACL_WRITE;
-			if ((aclent->a_perm & 4) != 0)
-				ae_perm |= ARCHIVE_ENTRY_ACL_READ;
-		} /* default_entry_acl_type != ARCHIVE_ENTRY_ACL_TYPE_NFS4 */
-
-		archive_entry_acl_add_entry(entry, entry_acl_type,
-		    ae_perm, ae_tag, ae_id, ae_name);
-	}
-	return (ARCHIVE_OK);
-}
-#else	/* !HAVE_SUN_ACL */
-/*
- * Translate POSIX.1e (Linux), FreeBSD (both POSIX.1e and NFSv4) and
- * MacOS (NFSv4 only) ACLs into libarchive internal structure
- */
-static int
-translate_acl(struct archive_read_disk *a,
-    struct archive_entry *entry, acl_t acl, int default_entry_acl_type)
-{
-	acl_tag_t	 acl_tag;
-#if HAVE_ACL_TYPE_NFS4
-	acl_entry_type_t acl_type;
-	int brand;
-#endif
-#if HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL
-	acl_flagset_t	 acl_flagset;
-#endif
-	acl_entry_t	 acl_entry;
-	acl_permset_t	 acl_permset;
-	int		 i, entry_acl_type;
-	int		 r, s, ae_id, ae_tag, ae_perm;
-#if !HAVE_DARWIN_ACL
-	void		*q;
-#endif
-	const char	*ae_name;
-
-#if HAVE_ACL_TYPE_NFS4
-	// FreeBSD "brands" ACLs as POSIX.1e or NFSv4
-	// Make sure the "brand" on this ACL is consistent
-	// with the default_entry_acl_type bits provided.
-	if (acl_get_brand_np(acl, &brand) != 0) {
-		archive_set_error(&a->archive, errno,
-		    "Failed to read ACL brand");
-		return (ARCHIVE_WARN);
-	}
-	switch (brand) {
-	case ACL_BRAND_POSIX:
-		switch (default_entry_acl_type) {
-		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
-		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
-			break;
-		default:
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "Invalid ACL entry type for POSIX.1e ACL");
-			return (ARCHIVE_WARN);
-		}
-		break;
-	case ACL_BRAND_NFS4:
-		if (default_entry_acl_type & ~ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "Invalid ACL entry type for NFSv4 ACL");
-			return (ARCHIVE_WARN);
-		}
-		break;
-	default:
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Unknown ACL brand");
-		return (ARCHIVE_WARN);
-	}
-#endif
-
-	s = acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_entry);
-	if (s == -1) {
-		archive_set_error(&a->archive, errno,
-		    "Failed to get first ACL entry");
-		return (ARCHIVE_WARN);
-	}
-
-#if HAVE_DARWIN_ACL
-	while (s == 0)
-#else	/* FreeBSD, Linux */
-	while (s == 1)
-#endif
-	{
-		ae_id = -1;
-		ae_name = NULL;
-		ae_perm = 0;
-
-		if (acl_get_tag_type(acl_entry, &acl_tag) != 0) {
-			archive_set_error(&a->archive, errno,
-			    "Failed to get ACL tag type");
-			return (ARCHIVE_WARN);
-		}
-		switch (acl_tag) {
-#if !HAVE_DARWIN_ACL	/* FreeBSD, Linux */
-		case ACL_USER:
-			q = acl_get_qualifier(acl_entry);
-			if (q != NULL) {
-				ae_id = (int)*(uid_t *)q;
-				acl_free(q);
-				ae_name = archive_read_disk_uname(&a->archive,
-				    ae_id);
-			}
-			ae_tag = ARCHIVE_ENTRY_ACL_USER;
-			break;
-		case ACL_GROUP:
-			q = acl_get_qualifier(acl_entry);
-			if (q != NULL) {
-				ae_id = (int)*(gid_t *)q;
-				acl_free(q);
-				ae_name = archive_read_disk_gname(&a->archive,
-				    ae_id);
-			}
-			ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
-			break;
-		case ACL_MASK:
-			ae_tag = ARCHIVE_ENTRY_ACL_MASK;
-			break;
-		case ACL_USER_OBJ:
-			ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
-			break;
-		case ACL_GROUP_OBJ:
-			ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
-			break;
-		case ACL_OTHER:
-			ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
-			break;
-#if HAVE_ACL_TYPE_NFS4
-		case ACL_EVERYONE:
-			ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
-			break;
-#endif
-#else	/* HAVE_DARWIN_ACL */
-		case ACL_EXTENDED_ALLOW:
-			entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
-			r = translate_guid(&a->archive, acl_entry, &ae_id,
-			    &ae_tag, &ae_name);
-			break;
-		case ACL_EXTENDED_DENY:
-			entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
-			r = translate_guid(&a->archive, acl_entry, &ae_id,
-			    &ae_tag, &ae_name);
-			break;
-#endif	/* HAVE_DARWIN_ACL */
-		default:
-			/* Skip types that libarchive can't support. */
-			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
-			continue;
-		}
-
-#if HAVE_DARWIN_ACL
-		/* Skip if translate_guid() above failed */
-		if (r != 0) {
-			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
-			continue;
-		}
-#endif
-
-#if !HAVE_DARWIN_ACL
-		// XXX acl_type maps to allow/deny/audit/YYYY bits
-		entry_acl_type = default_entry_acl_type;
-#endif
-#if HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL
-		if (default_entry_acl_type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
-#if HAVE_ACL_TYPE_NFS4
-			/*
-			 * acl_get_entry_type_np() fails with non-NFSv4 ACLs
-			 */
-			if (acl_get_entry_type_np(acl_entry, &acl_type) != 0) {
-				archive_set_error(&a->archive, errno, "Failed "
-				    "to get ACL type from a NFSv4 ACL entry");
-				return (ARCHIVE_WARN);
-			}
-			switch (acl_type) {
-			case ACL_ENTRY_TYPE_ALLOW:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
-				break;
-			case ACL_ENTRY_TYPE_DENY:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
-				break;
-			case ACL_ENTRY_TYPE_AUDIT:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_AUDIT;
-				break;
-			case ACL_ENTRY_TYPE_ALARM:
-				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
-				break;
-			default:
-				archive_set_error(&a->archive, errno,
-				    "Invalid NFSv4 ACL entry type");
-				return (ARCHIVE_WARN);
-			}
-#endif	/* HAVE_ACL_TYPE_NFS4 */
-
-			/*
-			 * Libarchive stores "flag" (NFSv4 inheritance bits)
-			 * in the ae_perm bitmap.
-			 *
-			 * acl_get_flagset_np() fails with non-NFSv4 ACLs
-			 */
-			if (acl_get_flagset_np(acl_entry, &acl_flagset) != 0) {
-				archive_set_error(&a->archive, errno,
-				    "Failed to get flagset from a NFSv4 ACL entry");
-				return (ARCHIVE_WARN);
-			}
-			for (i = 0; i < (int)(sizeof(acl_inherit_map) / sizeof(acl_inherit_map[0])); ++i) {
-				r = acl_get_flag_np(acl_flagset,
-				    acl_inherit_map[i].platform_inherit);
-				if (r == -1) {
-					archive_set_error(&a->archive, errno,
-					    "Failed to check flag in a NFSv4 "
-					    "ACL flagset");
-					return (ARCHIVE_WARN);
-				} else if (r)
-					ae_perm |= acl_inherit_map[i].archive_inherit;
-			}
-		}
-#endif	/* HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL */
-
-		if (acl_get_permset(acl_entry, &acl_permset) != 0) {
-			archive_set_error(&a->archive, errno,
-			    "Failed to get ACL permission set");
-			return (ARCHIVE_WARN);
-		}
-		for (i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
-			/*
-			 * acl_get_perm() is spelled differently on different
-			 * platforms; see above.
-			 */
-			r = ACL_GET_PERM(acl_permset, acl_perm_map[i].platform_perm);
-			if (r == -1) {
-				archive_set_error(&a->archive, errno,
-				    "Failed to check permission in an ACL permission set");
-				return (ARCHIVE_WARN);
-			} else if (r)
-				ae_perm |= acl_perm_map[i].archive_perm;
-		}
-
-		archive_entry_acl_add_entry(entry, entry_acl_type,
-					    ae_perm, ae_tag,
-					    ae_id, ae_name);
-
-		s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
-#if !HAVE_DARWIN_ACL
-		if (s == -1) {
-			archive_set_error(&a->archive, errno,
-			    "Failed to get next ACL entry");
-			return (ARCHIVE_WARN);
-		}
-#endif
-	}
-	return (ARCHIVE_OK);
-}
-#endif	/* !HAVE_SUN_ACL */
-#else	/* !HAVE_POSIX_ACL && !HAVE_NFS4_ACL */
-static int
-setup_acls(struct archive_read_disk *a,
-    struct archive_entry *entry, int *fd)
-{
-	(void)a;      /* UNUSED */
-	(void)entry;  /* UNUSED */
-	(void)fd;     /* UNUSED */
-	return (ARCHIVE_OK);
-}
-#endif	/* !HAVE_POSIX_ACL && !HAVE_NFS4_ACL */
-
-#if (HAVE_FGETXATTR && HAVE_FLISTXATTR && HAVE_LISTXATTR && \
-    HAVE_LLISTXATTR && HAVE_GETXATTR && HAVE_LGETXATTR) || \
-    (HAVE_FGETEA && HAVE_FLISTEA && HAVE_LISTEA)
-
-/*
- * Linux and AIX extended attribute support.
+ * Linux, Darwin and AIX extended attribute support.
  *
  * TODO:  By using a stack-allocated buffer for the first
  * call to getxattr(), we might be able to avoid the second
@@ -1433,21 +444,32 @@ setup_xattr(struct archive_read_disk *a,
 	ssize_t size;
 	void *value = NULL;
 
-#if HAVE_FGETXATTR
-	if (fd >= 0)
+
+	if (fd >= 0) {
+#if ARCHIVE_XATTR_LINUX
 		size = fgetxattr(fd, name, NULL, 0);
-	else if (!a->follow_symlinks)
-		size = lgetxattr(accpath, name, NULL, 0);
-	else
-		size = getxattr(accpath, name, NULL, 0);
-#elif HAVE_FGETEA
-	if (fd >= 0)
+#elif ARCHIVE_XATTR_DARWIN
+		size = fgetxattr(fd, name, NULL, 0, 0, 0);
+#elif ARCHIVE_XATTR_AIX
 		size = fgetea(fd, name, NULL, 0);
-	else if (!a->follow_symlinks)
+#endif
+	} else if (!a->follow_symlinks) {
+#if ARCHIVE_XATTR_LINUX
+		size = lgetxattr(accpath, name, NULL, 0);
+#elif ARCHIVE_XATTR_DARWIN
+		size = getxattr(accpath, name, NULL, 0, 0, XATTR_NOFOLLOW);
+#elif ARCHIVE_XATTR_AIX
 		size = lgetea(accpath, name, NULL, 0);
-	else
+#endif
+	} else {
+#if ARCHIVE_XATTR_LINUX
+		size = getxattr(accpath, name, NULL, 0);
+#elif ARCHIVE_XATTR_DARWIN
+		size = getxattr(accpath, name, NULL, 0, 0, 0);
+#elif ARCHIVE_XATTR_AIX
 		size = getea(accpath, name, NULL, 0);
 #endif
+	}
 
 	if (size == -1) {
 		archive_set_error(&a->archive, errno,
@@ -1460,21 +482,32 @@ setup_xattr(struct archive_read_disk *a,
 		return (ARCHIVE_FATAL);
 	}
 
-#if HAVE_FGETXATTR
-	if (fd >= 0)
+
+	if (fd >= 0) {
+#if ARCHIVE_XATTR_LINUX
 		size = fgetxattr(fd, name, value, size);
-	else if (!a->follow_symlinks)
-		size = lgetxattr(accpath, name, value, size);
-	else
-		size = getxattr(accpath, name, value, size);
-#elif HAVE_FGETEA
-	if (fd >= 0)
+#elif ARCHIVE_XATTR_DARWIN
+		size = fgetxattr(fd, name, value, size, 0, 0);
+#elif ARCHIVE_XATTR_AIX
 		size = fgetea(fd, name, value, size);
-	else if (!a->follow_symlinks)
+#endif
+	} else if (!a->follow_symlinks) {
+#if ARCHIVE_XATTR_LINUX
+		size = lgetxattr(accpath, name, value, size);
+#elif ARCHIVE_XATTR_DARWIN
+		size = getxattr(accpath, name, value, size, 0, XATTR_NOFOLLOW);
+#elif ARCHIVE_XATTR_AIX
 		size = lgetea(accpath, name, value, size);
-	else
+#endif
+	} else {
+#if ARCHIVE_XATTR_LINUX
+		size = getxattr(accpath, name, value, size);
+#elif ARCHIVE_XATTR_DARWIN
+		size = getxattr(accpath, name, value, size, 0, 0);
+#elif ARCHIVE_XATTR_AIX
 		size = getea(accpath, name, value, size);
 #endif
+	}
 
 	if (size == -1) {
 		archive_set_error(&a->archive, errno,
@@ -1499,38 +532,36 @@ setup_xattrs(struct archive_read_disk *a,
 	path = NULL;
 
 	if (*fd < 0) {
-		path = archive_entry_sourcepath(entry);
-		if (path == NULL || (a->tree != NULL &&
-		    a->tree_enter_working_dir(a->tree) != 0))
-			path = archive_entry_pathname(entry);
-		if (path == NULL) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "Couldn't determine file path to read "
-			    "extended attributes");
+		path = archive_read_disk_entry_setup_path(a, entry, fd);
+		if (path == NULL)
 			return (ARCHIVE_WARN);
-		}
-		if (a->tree != NULL && (a->follow_symlinks ||
-		    archive_entry_filetype(entry) != AE_IFLNK)) {
-			*fd = a->open_on_current_dir(a->tree,
-			    path, O_RDONLY | O_NONBLOCK);
-		}
 	}
 
-#if HAVE_FLISTXATTR
-	if (*fd >= 0)
+	if (*fd >= 0) {
+#if ARCHIVE_XATTR_LINUX
 		list_size = flistxattr(*fd, NULL, 0);
-	else if (!a->follow_symlinks)
-		list_size = llistxattr(path, NULL, 0);
-	else
-		list_size = listxattr(path, NULL, 0);
-#elif HAVE_FLISTEA
-	if (*fd >= 0)
+#elif ARCHIVE_XATTR_DARWIN
+		list_size = flistxattr(*fd, NULL, 0, 0);
+#elif ARCHIVE_XATTR_AIX
 		list_size = flistea(*fd, NULL, 0);
-	else if (!a->follow_symlinks)
+#endif
+	} else if (!a->follow_symlinks) {
+#if ARCHIVE_XATTR_LINUX
+		list_size = llistxattr(path, NULL, 0);
+#elif ARCHIVE_XATTR_DARWIN
+		list_size = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
+#elif ARCHIVE_XATTR_AIX
 		list_size = llistea(path, NULL, 0);
-	else
+#endif
+	} else {
+#if ARCHIVE_XATTR_LINUX
+		list_size = listxattr(path, NULL, 0);
+#elif ARCHIVE_XATTR_DARWIN
+		list_size = listxattr(path, NULL, 0, 0);
+#elif ARCHIVE_XATTR_AIX
 		list_size = listea(path, NULL, 0);
 #endif
+	}
 
 	if (list_size == -1) {
 		if (errno == ENOTSUP || errno == ENOSYS)
@@ -1548,21 +579,31 @@ setup_xattrs(struct archive_read_disk *a,
 		return (ARCHIVE_FATAL);
 	}
 
-#if HAVE_FLISTXATTR
-	if (*fd >= 0)
+	if (*fd >= 0) {
+#if ARCHIVE_XATTR_LINUX
 		list_size = flistxattr(*fd, list, list_size);
-	else if (!a->follow_symlinks)
-		list_size = llistxattr(path, list, list_size);
-	else
-		list_size = listxattr(path, list, list_size);
-#elif HAVE_FLISTEA
-	if (*fd >= 0)
+#elif ARCHIVE_XATTR_DARWIN
+		list_size = flistxattr(*fd, list, list_size, 0);
+#elif ARCHIVE_XATTR_AIX
 		list_size = flistea(*fd, list, list_size);
-	else if (!a->follow_symlinks)
+#endif
+	} else if (!a->follow_symlinks) {
+#if ARCHIVE_XATTR_LINUX
+		list_size = llistxattr(path, list, list_size);
+#elif ARCHIVE_XATTR_DARWIN
+		list_size = listxattr(path, list, list_size, XATTR_NOFOLLOW);
+#elif ARCHIVE_XATTR_AIX
 		list_size = llistea(path, list, list_size);
-	else
+#endif
+	} else {
+#if ARCHIVE_XATTR_LINUX
+		list_size = listxattr(path, list, list_size);
+#elif ARCHIVE_XATTR_DARWIN
+		list_size = listxattr(path, list, list_size, 0);
+#elif ARCHIVE_XATTR_AIX
 		list_size = listea(path, list, list_size);
 #endif
+	}
 
 	if (list_size == -1) {
 		archive_set_error(&a->archive, errno,
@@ -1572,18 +613,29 @@ setup_xattrs(struct archive_read_disk *a,
 	}
 
 	for (p = list; (p - list) < list_size; p += strlen(p) + 1) {
-		if (strncmp(p, "system.", 7) == 0 ||
-				strncmp(p, "xfsroot.", 8) == 0)
+#if ARCHIVE_XATTR_LINUX
+		/* Linux: skip POSIX.1e ACL extended attributes */
+		if (strncmp(p, "system.", 7) == 0 &&
+		   (strcmp(p + 7, "posix_acl_access") == 0 ||
+		    strcmp(p + 7, "posix_acl_default") == 0))
+			continue;
+		if (strncmp(p, "trusted.SGI_", 12) == 0 &&
+		   (strcmp(p + 12, "ACL_DEFAULT") == 0 ||
+		    strcmp(p + 12, "ACL_FILE") == 0))
+			continue;
+
+		/* Linux: xfsroot namespace is obsolete and unsupported */
+		if (strncmp(p, "xfsroot.", 8) == 0)
 			continue;
+#endif
 		setup_xattr(a, entry, p, *fd, path);
 	}
 
 	free(list);
 	return (ARCHIVE_OK);
 }
 
-#elif HAVE_EXTATTR_GET_FILE && HAVE_EXTATTR_LIST_FILE && \
-    HAVE_DECL_EXTATTR_NAMESPACE_USER
+#elif ARCHIVE_XATTR_FREEBSD
 
 /*
  * FreeBSD extattr interface.
@@ -1658,21 +710,9 @@ setup_xattrs(struct archive_read_disk *a,
 	path = NULL;
 
 	if (*fd < 0) {
-		path = archive_entry_sourcepath(entry);
-		if (path == NULL || (a->tree != NULL &&
-		    a->tree_enter_working_dir(a->tree) != 0))
-			path = archive_entry_pathname(entry);
-		if (path == NULL) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "Couldn't determine file path to read "
-			    "extended attributes");
+		path = archive_read_disk_entry_setup_path(a, entry, fd);
+		if (path == NULL)
 			return (ARCHIVE_WARN);
-		}
-		if (a->tree != NULL && (a->follow_symlinks ||
-		    archive_entry_filetype(entry) != AE_IFLNK)) {
-			*fd = a->open_on_current_dir(a->tree,
-			    path, O_RDONLY | O_NONBLOCK);
-		}
 	}
 
 	if (*fd >= 0)
@@ -1773,18 +813,18 @@ setup_sparse_fiemap(struct archive_read_disk *a,
 	int64_t size;
 	int count, do_fiemap, iters;
 	int exit_sts = ARCHIVE_OK;
+	const char *path;
 
 	if (archive_entry_filetype(entry) != AE_IFREG
 	    || archive_entry_size(entry) <= 0
 	    || archive_entry_hardlink(entry) != NULL)
 		return (ARCHIVE_OK);
 
 	if (*fd < 0) {
-		const char *path;
-
-		path = archive_entry_sourcepath(entry);
+		path = archive_read_disk_entry_setup_path(a, entry, NULL);
 		if (path == NULL)
-			path = archive_entry_pathname(entry);
+			return (ARCHIVE_FAILED);
+
 		if (a->tree != NULL)
 			*fd = a->open_on_current_dir(a->tree, path,
 				O_RDONLY | O_NONBLOCK | O_CLOEXEC);
@@ -1880,27 +920,18 @@ setup_sparse(struct archive_read_disk *a,
 	off_t off_s, off_e;
 	int exit_sts = ARCHIVE_OK;
 	int check_fully_sparse = 0;
+	const char *path;
 
 	if (archive_entry_filetype(entry) != AE_IFREG
 	    || archive_entry_size(entry) <= 0
 	    || archive_entry_hardlink(entry) != NULL)
 		return (ARCHIVE_OK);
 
 	/* Does filesystem support the reporting of hole ? */
-	if (*fd < 0 && a->tree != NULL) {
-		const char *path;
-
-		path = archive_entry_sourcepath(entry);
-		if (path == NULL)
-			path = archive_entry_pathname(entry);
-		*fd = a->open_on_current_dir(a->tree, path,
-				O_RDONLY | O_NONBLOCK);
-		if (*fd < 0) {
-			archive_set_error(&a->archive, errno,
-			    "Can't open `%s'", path);
-			return (ARCHIVE_FAILED);
-		}
-	}
+	if (*fd < 0)
+		path = archive_read_disk_entry_setup_path(a, entry, fd);
+	else
+		path = NULL;
 
 	if (*fd >= 0) {
 #ifdef _PC_MIN_HOLE_SIZE
@@ -1911,12 +942,8 @@ setup_sparse(struct archive_read_disk *a,
 		if (initial_off != 0)
 			lseek(*fd, 0, SEEK_SET);
 	} else {
-		const char *path;
-
-		path = archive_entry_sourcepath(entry);
 		if (path == NULL)
-			path = archive_entry_pathname(entry);
-			
+			return (ARCHIVE_FAILED);
 #ifdef _PC_MIN_HOLE_SIZE
 		if (pathconf(path, _PC_MIN_HOLE_SIZE) <= 0)
 			return (ARCHIVE_OK);