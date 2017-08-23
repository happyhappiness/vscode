@@ -1,6 +1,7 @@
 /*-
  * Copyright (c) 2003-2009 Tim Kientzle
  * Copyright (c) 2010-2012 Michihiro NAKAJIMA
+ * Copyright (c) 2016 Martin Matuska
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -37,6 +38,11 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #ifdef HAVE_SYS_ACL_H
 #include <sys/acl.h>
 #endif
+#ifdef HAVE_DARWIN_ACL
+#include <membership.h>
+#include <grp.h>
+#include <pwd.h>
+#endif
 #ifdef HAVE_SYS_EXTATTR_H
 #include <sys/extattr.h>
 #endif
@@ -117,6 +123,15 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_disk_entry_from_file.c 2010
 #define	ACL_GET_PERM acl_get_perm_np
 #endif
 
+/* NFSv4 platform ACL type */
+#if HAVE_SUN_ACL
+#define	ARCHIVE_PLATFORM_ACL_TYPE_NFS4	ACE_T
+#elif HAVE_DARWIN_ACL
+#define	ARCHIVE_PLATFORM_ACL_TYPE_NFS4	ACL_TYPE_EXTENDED
+#elif HAVE_ACL_TYPE_NFS4
+#define	ARCHIVE_PLATFORM_ACL_TYPE_NFS4	ACL_TYPE_NFS4
+#endif
+
 static int setup_acls(struct archive_read_disk *,
     struct archive_entry *, int *fd);
 static int setup_mac_metadata(struct archive_read_disk *,
@@ -125,6 +140,10 @@ static int setup_xattrs(struct archive_read_disk *,
     struct archive_entry *, int *fd);
 static int setup_sparse(struct archive_read_disk *,
     struct archive_entry *, int *fd);
+#if defined(HAVE_LINUX_FIEMAP_H)
+static int setup_sparse_fiemap(struct archive_read_disk *,
+    struct archive_entry *, int *fd);
+#endif
 
 int
 archive_read_disk_entry_from_file(struct archive *_a,
@@ -302,20 +321,17 @@ setup_mac_metadata(struct archive_read_disk *a,
 	name = archive_entry_sourcepath(entry);
 	if (name == NULL)
 		name = archive_entry_pathname(entry);
+	else if (a->tree != NULL && a->tree_enter_working_dir(a->tree) != 0) {
+		archive_set_error(&a->archive, errno,
+			    "Can't change dir to read extended attributes");
+			return (ARCHIVE_FAILED);
+	}
 	if (name == NULL) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Can't open file to read extended attributes: No name");
 		return (ARCHIVE_WARN);
 	}
 
-	if (a->tree != NULL) {
-		if (a->tree_enter_working_dir(a->tree) != 0) {
-			archive_set_error(&a->archive, errno,
-				    "Couldn't change dir");
-				return (ARCHIVE_FAILED);
-		}
-	}
-
 	/* Short-circuit if there's nothing to do. */
 	have_attrs = copyfile(name, NULL, 0, copyfile_flags | COPYFILE_CHECK);
 	if (have_attrs == -1) {
@@ -400,34 +416,87 @@ setup_mac_metadata(struct archive_read_disk *a,
 }
 #endif
 
+#if HAVE_DARWIN_ACL
+static int translate_guid(struct archive *, acl_entry_t,
+    int *, int *, const char **);
+
+static void add_trivial_nfs4_acl(struct archive_entry *);
+#endif
+
+#if HAVE_SUN_ACL
+static int
+sun_acl_is_trivial(acl_t *, mode_t, int *trivialp);
+#endif
 
-#ifdef HAVE_POSIX_ACL
+#if HAVE_POSIX_ACL || HAVE_NFS4_ACL
 static int translate_acl(struct archive_read_disk *a,
-    struct archive_entry *entry, acl_t acl, int archive_entry_acl_type);
+    struct archive_entry *entry,
+#if HAVE_SUN_ACL
+    acl_t *acl,
+#else
+    acl_t acl,
+#endif
+    int archive_entry_acl_type);
 
 static int
 setup_acls(struct archive_read_disk *a,
     struct archive_entry *entry, int *fd)
 {
 	const char	*accpath;
-	acl_t		 acl;
-#if HAVE_ACL_IS_TRIVIAL_NP
-	int		r;
+#if HAVE_SUN_ACL
+	acl_t		*acl;
+#else
+	acl_t		acl;
 #endif
+	int		r;
 
-	accpath = archive_entry_sourcepath(entry);
-	if (accpath == NULL)
-		accpath = archive_entry_pathname(entry);
+	accpath = NULL;
+
+#if HAVE_SUN_ACL || HAVE_DARWIN_ACL || HAVE_ACL_GET_FD_NP
+	if (*fd < 0)
+#else
+	/* For default ACLs on Linux we need reachable accpath */
+	if (*fd < 0 || S_ISDIR(archive_entry_mode(entry)))
+#endif
+	{
+		accpath = archive_entry_sourcepath(entry);
+		if (accpath == NULL || (a->tree != NULL &&
+		    a->tree_enter_working_dir(a->tree) != 0))
+			accpath = archive_entry_pathname(entry);
+		if (accpath == NULL) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Couldn't determine file path to read ACLs");
+			return (ARCHIVE_WARN);
+		}
+		if (a->tree != NULL &&
+#if !HAVE_SUN_ACL && !HAVE_DARWIN_ACL && !HAVE_ACL_GET_FD_NP
+		    *fd < 0 &&
+#endif
+		    (a->follow_symlinks ||
+		    archive_entry_filetype(entry) != AE_IFLNK)) {
+			*fd = a->open_on_current_dir(a->tree,
+			    accpath, O_RDONLY | O_NONBLOCK);
+		}
+	}
 
 	archive_entry_acl_clear(entry);
 
-#ifdef ACL_TYPE_NFS4
-	/* Try NFS4 ACL first. */
+	acl = NULL;
+
+#if HAVE_NFS4_ACL
+	/* Try NFSv4 ACL first. */
 	if (*fd >= 0)
+#if HAVE_SUN_ACL
+		/* Solaris reads both POSIX.1e and NFSv4 ACL here */
+		facl_get(*fd, 0, &acl);
+#elif HAVE_ACL_GET_FD_NP
+		acl = acl_get_fd_np(*fd, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
+#else
 		acl = acl_get_fd(*fd);
+#endif
 #if HAVE_ACL_GET_LINK_NP
 	else if (!a->follow_symlinks)
-		acl = acl_get_link_np(accpath, ACL_TYPE_NFS4);
+		acl = acl_get_link_np(accpath, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
 #else
 	else if ((!a->follow_symlinks)
 	    && (archive_entry_filetype(entry) == AE_IFLNK))
@@ -436,21 +505,62 @@ setup_acls(struct archive_read_disk *a,
 		acl = NULL;
 #endif
 	else
-		acl = acl_get_file(accpath, ACL_TYPE_NFS4);
-#if HAVE_ACL_IS_TRIVIAL_NP
+#if HAVE_SUN_ACL
+		/* Solaris reads both POSIX.1e and NFSv4 ACLs here */
+		acl_get(accpath, 0, &acl);
+#else
+		acl = acl_get_file(accpath, ARCHIVE_PLATFORM_ACL_TYPE_NFS4);
+#endif
+
+
+#if HAVE_ACL_IS_TRIVIAL_NP || HAVE_SUN_ACL
 	/* Ignore "trivial" ACLs that just mirror the file mode. */
-	acl_is_trivial_np(acl, &r);
-	if (r) {
-		acl_free(acl);
-		acl = NULL;
-	}
+	if (acl != NULL) {
+#if HAVE_SUN_ACL
+		if (sun_acl_is_trivial(acl, archive_entry_mode(entry),
+		    &r) == 0 && r == 1)
+#elif HAVE_ACL_IS_TRIVIAL_NP
+		if (acl_is_trivial_np(acl, &r) == 0 && r == 1)
 #endif
+		{
+			acl_free(acl);
+			acl = NULL;
+			/*
+			 * Simultaneous NFSv4 and POSIX.1e ACLs for the same
+			 * entry are not allowed, so we should return here
+			 */
+			return (ARCHIVE_OK);
+		}
+	}
+#endif	/* HAVE_ACL_IS_TRIVIAL_NP || HAVE_SUN_ACL */
 	if (acl != NULL) {
-		translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_NFS4);
+		r = translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_NFS4);
 		acl_free(acl);
-		return (ARCHIVE_OK);
-	}
+		if (r != ARCHIVE_OK) {
+			archive_set_error(&a->archive, errno,
+			    "Couldn't translate "
+#if !HAVE_SUN_ACL
+			    "NFSv4 "
+#endif
+			    "ACLs");
+		}
+#if HAVE_DARWIN_ACL
+		/*
+		 * Because Mac OS doesn't support owner@, group@ and everyone@
+		 * ACLs we need to add NFSv4 ACLs mirroring the file mode to
+		 * the archive entry. Otherwise extraction on non-Mac platforms
+		 * would lead to an invalid file mode.
+		 */
+		if ((archive_entry_acl_types(entry) &
+		    ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0)
+			add_trivial_nfs4_acl(entry);
 #endif
+		return (r);
+	}
+#endif	/* HAVE_NFS4_ACL */
+
+#if HAVE_POSIX_ACL
+	/* This code path is skipped on MacOS and Solaris */
 
 	/* Retrieve access ACL from file. */
 	if (*fd >= 0)
@@ -467,129 +577,677 @@ setup_acls(struct archive_read_disk *a,
 #endif
 	else
 		acl = acl_get_file(accpath, ACL_TYPE_ACCESS);
+
+#if HAVE_ACL_IS_TRIVIAL_NP
+	/* Ignore "trivial" ACLs that just mirror the file mode. */
+	if (acl != NULL && acl_is_trivial_np(acl, &r) == 0) {
+		if (r) {
+			acl_free(acl);
+			acl = NULL;
+		}
+	}
+#endif
+
 	if (acl != NULL) {
-		translate_acl(a, entry, acl,
-		    ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
+		r = translate_acl(a, entry, acl, ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
 		acl_free(acl);
+		acl = NULL;
+		if (r != ARCHIVE_OK) {
+			archive_set_error(&a->archive, errno,
+			    "Couldn't translate access ACLs");
+			return (r);
+		}
 	}
 
 	/* Only directories can have default ACLs. */
 	if (S_ISDIR(archive_entry_mode(entry))) {
+#if HAVE_ACL_GET_FD_NP
+		if (*fd >= 0)
+			acl = acl_get_fd_np(*fd, ACL_TYPE_DEFAULT);
+		else
+#endif
 		acl = acl_get_file(accpath, ACL_TYPE_DEFAULT);
 		if (acl != NULL) {
-			translate_acl(a, entry, acl,
+			r = translate_acl(a, entry, acl,
 			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT);
 			acl_free(acl);
+			if (r != ARCHIVE_OK) {
+				archive_set_error(&a->archive, errno,
+				    "Couldn't translate default ACLs");
+				return (r);
+			}
 		}
 	}
+#endif	/* HAVE_POSIX_ACL */
 	return (ARCHIVE_OK);
 }
 
 /*
- * Translate system ACL into libarchive internal structure.
+ * Translate system ACL permissions into libarchive internal structure
  */
-
-static struct {
-        int archive_perm;
-        int platform_perm;
+static const struct {
+	const int archive_perm;
+	const int platform_perm;
 } acl_perm_map[] = {
-        {ARCHIVE_ENTRY_ACL_EXECUTE, ACL_EXECUTE},
-        {ARCHIVE_ENTRY_ACL_WRITE, ACL_WRITE},
-        {ARCHIVE_ENTRY_ACL_READ, ACL_READ},
-#ifdef ACL_TYPE_NFS4
-        {ARCHIVE_ENTRY_ACL_READ_DATA, ACL_READ_DATA},
-        {ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACL_LIST_DIRECTORY},
-        {ARCHIVE_ENTRY_ACL_WRITE_DATA, ACL_WRITE_DATA},
-        {ARCHIVE_ENTRY_ACL_ADD_FILE, ACL_ADD_FILE},
-        {ARCHIVE_ENTRY_ACL_APPEND_DATA, ACL_APPEND_DATA},
-        {ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACL_ADD_SUBDIRECTORY},
-        {ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACL_READ_NAMED_ATTRS},
-        {ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACL_WRITE_NAMED_ATTRS},
-        {ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACL_DELETE_CHILD},
-        {ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACL_READ_ATTRIBUTES},
-        {ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACL_WRITE_ATTRIBUTES},
-        {ARCHIVE_ENTRY_ACL_DELETE, ACL_DELETE},
-        {ARCHIVE_ENTRY_ACL_READ_ACL, ACL_READ_ACL},
-        {ARCHIVE_ENTRY_ACL_WRITE_ACL, ACL_WRITE_ACL},
-        {ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACL_WRITE_OWNER},
-        {ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACL_SYNCHRONIZE}
+#if HAVE_SUN_ACL	/* Solaris NFSv4 ACL permissions */
+	{ARCHIVE_ENTRY_ACL_EXECUTE, ACE_EXECUTE},
+	{ARCHIVE_ENTRY_ACL_READ_DATA, ACE_READ_DATA},
+	{ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACE_LIST_DIRECTORY},
+	{ARCHIVE_ENTRY_ACL_WRITE_DATA, ACE_WRITE_DATA},
+	{ARCHIVE_ENTRY_ACL_ADD_FILE, ACE_ADD_FILE},
+	{ARCHIVE_ENTRY_ACL_APPEND_DATA, ACE_APPEND_DATA},
+	{ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACE_ADD_SUBDIRECTORY},
+	{ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACE_READ_NAMED_ATTRS},
+	{ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACE_WRITE_NAMED_ATTRS},
+	{ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACE_DELETE_CHILD},
+	{ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACE_READ_ATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACE_WRITE_ATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_DELETE, ACE_DELETE},
+	{ARCHIVE_ENTRY_ACL_READ_ACL, ACE_READ_ACL},
+	{ARCHIVE_ENTRY_ACL_WRITE_ACL, ACE_WRITE_ACL},
+	{ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACE_WRITE_OWNER},
+	{ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACE_SYNCHRONIZE}
+#elif HAVE_DARWIN_ACL	/* MacOS ACL permissions */
+	{ARCHIVE_ENTRY_ACL_READ_DATA, ACL_READ_DATA},
+	{ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACL_LIST_DIRECTORY},
+	{ARCHIVE_ENTRY_ACL_WRITE_DATA, ACL_WRITE_DATA},
+	{ARCHIVE_ENTRY_ACL_ADD_FILE, ACL_ADD_FILE},
+	{ARCHIVE_ENTRY_ACL_EXECUTE, ACL_EXECUTE},
+	{ARCHIVE_ENTRY_ACL_DELETE, ACL_DELETE},
+	{ARCHIVE_ENTRY_ACL_APPEND_DATA, ACL_APPEND_DATA},
+	{ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACL_ADD_SUBDIRECTORY},
+	{ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACL_DELETE_CHILD},
+	{ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACL_READ_ATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACL_WRITE_ATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACL_READ_EXTATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACL_WRITE_EXTATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_READ_ACL, ACL_READ_SECURITY},
+	{ARCHIVE_ENTRY_ACL_WRITE_ACL, ACL_WRITE_SECURITY},
+	{ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACL_CHANGE_OWNER},
+	{ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACL_SYNCHRONIZE}
+#else	/* POSIX.1e ACL permissions */
+	{ARCHIVE_ENTRY_ACL_EXECUTE, ACL_EXECUTE},
+	{ARCHIVE_ENTRY_ACL_WRITE, ACL_WRITE},
+	{ARCHIVE_ENTRY_ACL_READ, ACL_READ},
+#if HAVE_ACL_TYPE_NFS4	/* FreeBSD NFSv4 ACL permissions */
+	{ARCHIVE_ENTRY_ACL_READ_DATA, ACL_READ_DATA},
+	{ARCHIVE_ENTRY_ACL_LIST_DIRECTORY, ACL_LIST_DIRECTORY},
+	{ARCHIVE_ENTRY_ACL_WRITE_DATA, ACL_WRITE_DATA},
+	{ARCHIVE_ENTRY_ACL_ADD_FILE, ACL_ADD_FILE},
+	{ARCHIVE_ENTRY_ACL_APPEND_DATA, ACL_APPEND_DATA},
+	{ARCHIVE_ENTRY_ACL_ADD_SUBDIRECTORY, ACL_ADD_SUBDIRECTORY},
+	{ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS, ACL_READ_NAMED_ATTRS},
+	{ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS, ACL_WRITE_NAMED_ATTRS},
+	{ARCHIVE_ENTRY_ACL_DELETE_CHILD, ACL_DELETE_CHILD},
+	{ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES, ACL_READ_ATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES, ACL_WRITE_ATTRIBUTES},
+	{ARCHIVE_ENTRY_ACL_DELETE, ACL_DELETE},
+	{ARCHIVE_ENTRY_ACL_READ_ACL, ACL_READ_ACL},
+	{ARCHIVE_ENTRY_ACL_WRITE_ACL, ACL_WRITE_ACL},
+	{ARCHIVE_ENTRY_ACL_WRITE_OWNER, ACL_WRITE_OWNER},
+	{ARCHIVE_ENTRY_ACL_SYNCHRONIZE, ACL_SYNCHRONIZE}
 #endif
+#endif	/* !HAVE_SUN_ACL && !HAVE_DARWIN_ACL */
 };
 
-#ifdef ACL_TYPE_NFS4
-static struct {
-        int archive_inherit;
-        int platform_inherit;
+#if HAVE_NFS4_ACL
+/*
+ * Translate system NFSv4 inheritance flags into libarchive internal structure
+ */
+static const struct {
+	const int archive_inherit;
+	const int platform_inherit;
 } acl_inherit_map[] = {
-        {ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_FILE_INHERIT},
+#if HAVE_SUN_ACL	/* Solaris ACL inheritance flags */
+	{ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACE_FILE_INHERIT_ACE},
+	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACE_DIRECTORY_INHERIT_ACE},
+	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACE_NO_PROPAGATE_INHERIT_ACE},
+	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACE_INHERIT_ONLY_ACE},
+	{ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS, ACE_SUCCESSFUL_ACCESS_ACE_FLAG},
+	{ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS, ACE_FAILED_ACCESS_ACE_FLAG},
+	{ARCHIVE_ENTRY_ACL_ENTRY_INHERITED, ACE_INHERITED_ACE}
+#elif HAVE_DARWIN_ACL	/* MacOS NFSv4 inheritance flags */
+	{ARCHIVE_ENTRY_ACL_ENTRY_INHERITED, ACL_ENTRY_INHERITED},
+	{ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_FILE_INHERIT},
+	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACL_ENTRY_DIRECTORY_INHERIT},
+	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACL_ENTRY_LIMIT_INHERIT},
+	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACL_ENTRY_ONLY_INHERIT}
+#else	/* FreeBSD NFSv4 ACL inheritance flags */
+	{ARCHIVE_ENTRY_ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_FILE_INHERIT},
 	{ARCHIVE_ENTRY_ACL_ENTRY_DIRECTORY_INHERIT, ACL_ENTRY_DIRECTORY_INHERIT},
 	{ARCHIVE_ENTRY_ACL_ENTRY_NO_PROPAGATE_INHERIT, ACL_ENTRY_NO_PROPAGATE_INHERIT},
-	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACL_ENTRY_INHERIT_ONLY}
+	{ARCHIVE_ENTRY_ACL_ENTRY_INHERIT_ONLY, ACL_ENTRY_INHERIT_ONLY},
+	{ARCHIVE_ENTRY_ACL_ENTRY_SUCCESSFUL_ACCESS, ACL_ENTRY_SUCCESSFUL_ACCESS},
+	{ARCHIVE_ENTRY_ACL_ENTRY_FAILED_ACCESS, ACL_ENTRY_FAILED_ACCESS},
+	{ARCHIVE_ENTRY_ACL_ENTRY_INHERITED, ACL_ENTRY_INHERITED}
+#endif	/* !HAVE_SUN_ACL && !HAVE_DARWIN_ACL */
 };
-#endif
+#endif	/* HAVE_NFS4_ACL */
+
+#if HAVE_DARWIN_ACL
+static int translate_guid(struct archive *a, acl_entry_t acl_entry,
+    int *ae_id, int *ae_tag, const char **ae_name)
+{
+	void *q;
+	uid_t ugid;
+	int r, idtype;
+	struct passwd *pwd;
+	struct group *grp;
+
+	q = acl_get_qualifier(acl_entry);
+	if (q == NULL)
+		return (1);
+	r = mbr_uuid_to_id((const unsigned char *)q, &ugid, &idtype);
+	if (r != 0) {
+		acl_free(q);
+		return (1);
+	}
+	if (idtype == ID_TYPE_UID) {
+		*ae_tag = ARCHIVE_ENTRY_ACL_USER;
+		pwd = getpwuuid(q);
+		if (pwd == NULL) {
+			*ae_id = ugid;
+			*ae_name = NULL;
+		} else {
+			*ae_id = pwd->pw_uid;
+			*ae_name = archive_read_disk_uname(a, *ae_id);
+		}
+	} else if (idtype == ID_TYPE_GID) {
+		*ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
+		grp = getgruuid(q);
+		if (grp == NULL) {
+			*ae_id = ugid;
+			*ae_name = NULL;
+		} else {
+			*ae_id = grp->gr_gid;
+			*ae_name = archive_read_disk_gname(a, *ae_id);
+		}
+	} else
+		r = 1;
+
+	acl_free(q);
+	return (r);
+}
+
+/*
+ * Add trivial NFSv4 ACL entries from mode
+ */
+static void
+add_trivial_nfs4_acl(struct archive_entry *entry)
+{
+	mode_t mode;
+	int i;
+	const int rperm = ARCHIVE_ENTRY_ACL_READ_DATA;
+	const int wperm = ARCHIVE_ENTRY_ACL_WRITE_DATA |
+	    ARCHIVE_ENTRY_ACL_APPEND_DATA;
+	const int eperm = ARCHIVE_ENTRY_ACL_EXECUTE;
+	const int pubset = ARCHIVE_ENTRY_ACL_READ_ATTRIBUTES |
+	    ARCHIVE_ENTRY_ACL_READ_NAMED_ATTRS |
+	    ARCHIVE_ENTRY_ACL_READ_ACL |
+	    ARCHIVE_ENTRY_ACL_SYNCHRONIZE;
+	const int ownset = pubset | ARCHIVE_ENTRY_ACL_WRITE_ATTRIBUTES |
+	    ARCHIVE_ENTRY_ACL_WRITE_NAMED_ATTRS |
+	    ARCHIVE_ENTRY_ACL_WRITE_ACL |
+	    ARCHIVE_ENTRY_ACL_WRITE_OWNER;
+
+	struct {
+	    const int type;
+	    const int tag;
+	    int permset;
+	} tacl_entry[] = {
+	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_USER_OBJ, 0},
+	    {ARCHIVE_ENTRY_ACL_TYPE_DENY, ARCHIVE_ENTRY_ACL_USER_OBJ, 0},
+	    {ARCHIVE_ENTRY_ACL_TYPE_DENY, ARCHIVE_ENTRY_ACL_GROUP_OBJ, 0},
+	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_USER_OBJ, ownset},
+	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_GROUP_OBJ, pubset},
+	    {ARCHIVE_ENTRY_ACL_TYPE_ALLOW, ARCHIVE_ENTRY_ACL_EVERYONE, pubset}
+	};
+
+	mode = archive_entry_mode(entry);
+
+	/* Permissions for everyone@ */
+	if (mode & 0004)
+		tacl_entry[5].permset |= rperm;
+	if (mode & 0002)
+		tacl_entry[5].permset |= wperm;
+	if (mode & 0001)
+		tacl_entry[5].permset |= eperm;
+
+	/* Permissions for group@ */
+	if (mode & 0040)
+		tacl_entry[4].permset |= rperm;
+	else if (mode & 0004)
+		tacl_entry[2].permset |= rperm;
+	if (mode & 0020)
+		tacl_entry[4].permset |= wperm;
+	else if (mode & 0002)
+		tacl_entry[2].permset |= wperm;
+	if (mode & 0010)
+		tacl_entry[4].permset |= eperm;
+	else if (mode & 0001)
+		tacl_entry[2].permset |= eperm;
+
+	/* Permissions for owner@ */
+	if (mode & 0400) {
+		tacl_entry[3].permset |= rperm;
+		if (!(mode & 0040) && (mode & 0004))
+			tacl_entry[0].permset |= rperm;
+	} else if ((mode & 0040) || (mode & 0004))
+		tacl_entry[1].permset |= rperm;
+	if (mode & 0200) {
+		tacl_entry[3].permset |= wperm;
+		if (!(mode & 0020) && (mode & 0002))
+			tacl_entry[0].permset |= wperm;
+	} else if ((mode & 0020) || (mode & 0002))
+		tacl_entry[1].permset |= wperm;
+	if (mode & 0100) {
+		tacl_entry[3].permset |= eperm;
+		if (!(mode & 0010) && (mode & 0001))
+			tacl_entry[0].permset |= eperm;
+	} else if ((mode & 0010) || (mode & 0001))
+		tacl_entry[1].permset |= eperm;
+
+	for (i = 0; i < 6; i++) {
+		if (tacl_entry[i].permset != 0) {
+			archive_entry_acl_add_entry(entry,
+			    tacl_entry[i].type, tacl_entry[i].permset,
+			    tacl_entry[i].tag, -1, NULL);
+		}
+	}
+
+	return;
+}
+#elif HAVE_SUN_ACL
+/*
+ * Check if acl is trivial
+ * This is a FreeBSD acl_is_trivial_np() implementation for Solaris
+ */
+static int
+sun_acl_is_trivial(acl_t *acl, mode_t mode, int *trivialp)
+{
+	int i, p;
+	const uint32_t rperm = ACE_READ_DATA;
+	const uint32_t wperm = ACE_WRITE_DATA | ACE_APPEND_DATA;
+	const uint32_t eperm = ACE_EXECUTE;
+	const uint32_t pubset = ACE_READ_ATTRIBUTES | ACE_READ_NAMED_ATTRS |
+	    ACE_READ_ACL | ACE_SYNCHRONIZE;
+	const uint32_t ownset = pubset | ACE_WRITE_ATTRIBUTES |
+	    ACE_WRITE_NAMED_ATTRS | ACE_WRITE_ACL | ACE_WRITE_OWNER;
+
+	ace_t *ace;
+	ace_t tace[6];
+
+	if (acl == NULL || trivialp == NULL)
+		return (-1);
+
+	*trivialp = 0;
+
+	/* ACL_IS_TRIVIAL flag must be set for both POSIX.1e and NFSv4 ACLs */
+	if ((acl->acl_flags & ACL_IS_TRIVIAL) == 0)
+		return (0);
+
+	/*
+	 * POSIX.1e ACLs marked with ACL_IS_TRIVIAL are compatible with
+	 * FreeBSD acl_is_trivial_np(). On Solaris they have 4 entries,
+	 * including mask.
+	 */
+	if (acl->acl_type == ACLENT_T) {
+		if (acl->acl_cnt == 4)
+			*trivialp = 1;
+		return (0);
+	}
+
+	if (acl->acl_type != ACE_T || acl->acl_entry_size != sizeof(ace_t))
+		return (-1);
+
+	/*
+	 * Continue with checking NFSv4 ACLs
+	 *
+	 * Create list of trivial ace's to be compared
+	 */
+
+	/* owner@ allow pre */
+	tace[0].a_flags = ACE_OWNER;
+	tace[0].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
+	tace[0].a_access_mask = 0;
+
+	/* owner@ deny */
+	tace[1].a_flags = ACE_OWNER;
+	tace[1].a_type = ACE_ACCESS_DENIED_ACE_TYPE;
+	tace[1].a_access_mask = 0;
+
+	/* group@ deny */
+	tace[2].a_flags = ACE_GROUP | ACE_IDENTIFIER_GROUP;
+	tace[2].a_type = ACE_ACCESS_DENIED_ACE_TYPE;
+	tace[2].a_access_mask = 0;
+
+	/* owner@ allow */
+	tace[3].a_flags = ACE_OWNER;
+	tace[3].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
+	tace[3].a_access_mask = ownset;
+
+	/* group@ allow */
+	tace[4].a_flags = ACE_GROUP | ACE_IDENTIFIER_GROUP;
+	tace[4].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
+	tace[4].a_access_mask = pubset;
+
+	/* everyone@ allow */
+	tace[5].a_flags = ACE_EVERYONE;
+	tace[5].a_type = ACE_ACCESS_ALLOWED_ACE_TYPE;
+	tace[5].a_access_mask = pubset;
+
+	/* Permissions for everyone@ */
+	if (mode & 0004)
+		tace[5].a_access_mask |= rperm;
+	if (mode & 0002)
+		tace[5].a_access_mask |= wperm;
+	if (mode & 0001)
+		tace[5].a_access_mask |= eperm;
+
+	/* Permissions for group@ */
+	if (mode & 0040)
+		tace[4].a_access_mask |= rperm;
+	else if (mode & 0004)
+		tace[2].a_access_mask |= rperm;
+	if (mode & 0020)
+		tace[4].a_access_mask |= wperm;
+	else if (mode & 0002)
+		tace[2].a_access_mask |= wperm;
+	if (mode & 0010)
+		tace[4].a_access_mask |= eperm;
+	else if (mode & 0001)
+		tace[2].a_access_mask |= eperm;
+
+	/* Permissions for owner@ */
+	if (mode & 0400) {
+		tace[3].a_access_mask |= rperm;
+		if (!(mode & 0040) && (mode & 0004))
+			tace[0].a_access_mask |= rperm;
+	} else if ((mode & 0040) || (mode & 0004))
+		tace[1].a_access_mask |= rperm;
+	if (mode & 0200) {
+		tace[3].a_access_mask |= wperm;
+		if (!(mode & 0020) && (mode & 0002))
+			tace[0].a_access_mask |= wperm;
+	} else if ((mode & 0020) || (mode & 0002))
+		tace[1].a_access_mask |= wperm;
+	if (mode & 0100) {
+		tace[3].a_access_mask |= eperm;
+		if (!(mode & 0010) && (mode & 0001))
+			tace[0].a_access_mask |= eperm;
+	} else if ((mode & 0010) || (mode & 0001))
+		tace[1].a_access_mask |= eperm;
+
+	/* Check if the acl count matches */
+	p = 3;
+	for (i = 0; i < 3; i++) {
+		if (tace[i].a_access_mask != 0)
+			p++;
+	}
+	if (acl->acl_cnt != p)
+		return (0);
+
+	p = 0;
+	for (i = 0; i < 6; i++) {
+		if (tace[i].a_access_mask != 0) {
+			ace = &((ace_t *)acl->acl_aclp)[p];
+			/*
+			 * Illumos added ACE_DELETE_CHILD to write perms for
+			 * directories. We have to check against that, too.
+			 */
+			if (ace->a_flags != tace[i].a_flags ||
+			    ace->a_type != tace[i].a_type ||
+			    (ace->a_access_mask != tace[i].a_access_mask &&
+			    ((acl->acl_flags & ACL_IS_DIR) == 0 ||
+			    (tace[i].a_access_mask & wperm) == 0 ||
+			    ace->a_access_mask !=
+			    (tace[i].a_access_mask | ACE_DELETE_CHILD))))
+				return (0);
+			p++;
+		}
+	}
+
+	*trivialp = 1;
+	return (0);
+}
+#endif	/* HAVE_SUN_ACL */
+
+#if HAVE_SUN_ACL
+/*
+ * Translate Solaris POSIX.1e and NFSv4 ACLs into libarchive internal ACL
+ */
+static int
+translate_acl(struct archive_read_disk *a,
+    struct archive_entry *entry, acl_t *acl, int default_entry_acl_type)
+{
+	int e, i;
+	int ae_id, ae_tag, ae_perm;
+	int entry_acl_type;
+	const char *ae_name;
+	aclent_t *aclent;
+	ace_t *ace;
+
+	(void)default_entry_acl_type;
+
+	if (acl->acl_cnt <= 0)
+		return (ARCHIVE_OK);
+
+	for (e = 0; e < acl->acl_cnt; e++) {
+		ae_name = NULL;
+		ae_tag = 0;
+		ae_perm = 0;
+
+		if (acl->acl_type == ACE_T) {
+			ace = &((ace_t *)acl->acl_aclp)[e];
+			ae_id = ace->a_who;
+
+			switch(ace->a_type) {
+			case ACE_ACCESS_ALLOWED_ACE_TYPE:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
+				break;
+			case ACE_ACCESS_DENIED_ACE_TYPE:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
+				break;
+			case ACE_SYSTEM_AUDIT_ACE_TYPE:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
+				break;
+			case ACE_SYSTEM_ALARM_ACE_TYPE:
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
+				break;
+			default:
+				/* Unknown entry type, skip */
+				continue;
+			}
+
+			if ((ace->a_flags & ACE_OWNER) != 0)
+				ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
+			else if ((ace->a_flags & ACE_GROUP) != 0)
+				ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
+			else if ((ace->a_flags & ACE_EVERYONE) != 0)
+				ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
+			else if ((ace->a_flags & ACE_IDENTIFIER_GROUP) != 0) {
+				ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
+				ae_name = archive_read_disk_gname(&a->archive,
+				    ae_id);
+			} else {
+				ae_tag = ARCHIVE_ENTRY_ACL_USER;
+				ae_name = archive_read_disk_uname(&a->archive,
+				    ae_id);
+			}
+
+			for (i = 0; i < (int)(sizeof(acl_inherit_map) /
+			    sizeof(acl_inherit_map[0])); ++i) {
+				if ((ace->a_flags &
+				    acl_inherit_map[i].platform_inherit) != 0)
+					ae_perm |=
+					    acl_inherit_map[i].archive_inherit;
+			}
+
+			for (i = 0; i < (int)(sizeof(acl_perm_map) /
+			    sizeof(acl_perm_map[0])); ++i) {
+				if ((ace->a_access_mask &
+				    acl_perm_map[i].platform_perm) != 0)
+					ae_perm |=
+					    acl_perm_map[i].archive_perm;
+			}
+		} else {
+			aclent = &((aclent_t *)acl->acl_aclp)[e];
+			if ((aclent->a_type & ACL_DEFAULT) != 0)
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DEFAULT;
+			else
+				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
+			ae_id = aclent->a_id;
+
+			switch(aclent->a_type) {
+			case DEF_USER:
+			case USER:
+				ae_name = archive_read_disk_uname(&a->archive,
+				    ae_id);
+				ae_tag = ARCHIVE_ENTRY_ACL_USER;
+				break;
+			case DEF_GROUP:
+			case GROUP:
+				ae_name = archive_read_disk_gname(&a->archive,
+				    ae_id);
+				ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
+				break;
+			case DEF_CLASS_OBJ:
+			case CLASS_OBJ:
+				ae_tag = ARCHIVE_ENTRY_ACL_MASK;
+				break;
+			case DEF_USER_OBJ:
+			case USER_OBJ:
+				ae_tag = ARCHIVE_ENTRY_ACL_USER_OBJ;
+				break;
+			case DEF_GROUP_OBJ:
+			case GROUP_OBJ:
+				ae_tag = ARCHIVE_ENTRY_ACL_GROUP_OBJ;
+				break;
+			case DEF_OTHER_OBJ:
+			case OTHER_OBJ:
+				ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
+				break;
+			default:
+				/* Unknown tag type, skip */
+				continue;
+			}
+
+			if ((aclent->a_perm & 1) != 0)
+				ae_perm |= ARCHIVE_ENTRY_ACL_EXECUTE;
+			if ((aclent->a_perm & 2) != 0)
+				ae_perm |= ARCHIVE_ENTRY_ACL_WRITE;
+			if ((aclent->a_perm & 4) != 0)
+				ae_perm |= ARCHIVE_ENTRY_ACL_READ;
+		} /* default_entry_acl_type != ARCHIVE_ENTRY_ACL_TYPE_NFS4 */
+
+		archive_entry_acl_add_entry(entry, entry_acl_type,
+		    ae_perm, ae_tag, ae_id, ae_name);
+	}
+	return (ARCHIVE_OK);
+}
+#else	/* !HAVE_SUN_ACL */
+/*
+ * Translate POSIX.1e (Linux), FreeBSD (both POSIX.1e and NFSv4) and
+ * MacOS (NFSv4 only) ACLs into libarchive internal structure
+ */
 static int
 translate_acl(struct archive_read_disk *a,
     struct archive_entry *entry, acl_t acl, int default_entry_acl_type)
 {
 	acl_tag_t	 acl_tag;
-#ifdef ACL_TYPE_NFS4
+#if HAVE_ACL_TYPE_NFS4
 	acl_entry_type_t acl_type;
+	int brand;
+#endif
+#if HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL
 	acl_flagset_t	 acl_flagset;
-	int brand, r;
 #endif
 	acl_entry_t	 acl_entry;
 	acl_permset_t	 acl_permset;
 	int		 i, entry_acl_type;
-	int		 s, ae_id, ae_tag, ae_perm;
+	int		 r, s, ae_id, ae_tag, ae_perm;
+#if !HAVE_DARWIN_ACL
+	void		*q;
+#endif
 	const char	*ae_name;
 
-
-#ifdef ACL_TYPE_NFS4
+#if HAVE_ACL_TYPE_NFS4
 	// FreeBSD "brands" ACLs as POSIX.1e or NFSv4
 	// Make sure the "brand" on this ACL is consistent
 	// with the default_entry_acl_type bits provided.
-	acl_get_brand_np(acl, &brand);
+	if (acl_get_brand_np(acl, &brand) != 0) {
+		archive_set_error(&a->archive, errno,
+		    "Failed to read ACL brand");
+		return (ARCHIVE_WARN);
+	}
 	switch (brand) {
 	case ACL_BRAND_POSIX:
 		switch (default_entry_acl_type) {
 		case ARCHIVE_ENTRY_ACL_TYPE_ACCESS:
 		case ARCHIVE_ENTRY_ACL_TYPE_DEFAULT:
 			break;
 		default:
-			// XXX set warning message?
-			return ARCHIVE_FAILED;
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Invalid ACL entry type for POSIX.1e ACL");
+			return (ARCHIVE_WARN);
 		}
 		break;
 	case ACL_BRAND_NFS4:
 		if (default_entry_acl_type & ~ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
-			// XXX set warning message?
-			return ARCHIVE_FAILED;
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Invalid ACL entry type for NFSv4 ACL");
+			return (ARCHIVE_WARN);
 		}
 		break;
 	default:
-		// XXX set warning message?
-		return ARCHIVE_FAILED;
-		break;
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Unknown ACL brand");
+		return (ARCHIVE_WARN);
 	}
 #endif
 
-
 	s = acl_get_entry(acl, ACL_FIRST_ENTRY, &acl_entry);
-	while (s == 1) {
+	if (s == -1) {
+		archive_set_error(&a->archive, errno,
+		    "Failed to get first ACL entry");
+		return (ARCHIVE_WARN);
+	}
+
+#if HAVE_DARWIN_ACL
+	while (s == 0)
+#else	/* FreeBSD, Linux */
+	while (s == 1)
+#endif
+	{
 		ae_id = -1;
 		ae_name = NULL;
 		ae_perm = 0;
 
-		acl_get_tag_type(acl_entry, &acl_tag);
+		if (acl_get_tag_type(acl_entry, &acl_tag) != 0) {
+			archive_set_error(&a->archive, errno,
+			    "Failed to get ACL tag type");
+			return (ARCHIVE_WARN);
+		}
 		switch (acl_tag) {
+#if !HAVE_DARWIN_ACL	/* FreeBSD, Linux */
 		case ACL_USER:
-			ae_id = (int)*(uid_t *)acl_get_qualifier(acl_entry);
-			ae_name = archive_read_disk_uname(&a->archive, ae_id);
+			q = acl_get_qualifier(acl_entry);
+			if (q != NULL) {
+				ae_id = (int)*(uid_t *)q;
+				acl_free(q);
+				ae_name = archive_read_disk_uname(&a->archive,
+				    ae_id);
+			}
 			ae_tag = ARCHIVE_ENTRY_ACL_USER;
 			break;
 		case ACL_GROUP:
-			ae_id = (int)*(gid_t *)acl_get_qualifier(acl_entry);
-			ae_name = archive_read_disk_gname(&a->archive, ae_id);
+			q = acl_get_qualifier(acl_entry);
+			if (q != NULL) {
+				ae_id = (int)*(gid_t *)q;
+				acl_free(q);
+				ae_name = archive_read_disk_gname(&a->archive,
+				    ae_id);
+			}
 			ae_tag = ARCHIVE_ENTRY_ACL_GROUP;
 			break;
 		case ACL_MASK:
@@ -604,24 +1262,52 @@ translate_acl(struct archive_read_disk *a,
 		case ACL_OTHER:
 			ae_tag = ARCHIVE_ENTRY_ACL_OTHER;
 			break;
-#ifdef ACL_TYPE_NFS4
+#if HAVE_ACL_TYPE_NFS4
 		case ACL_EVERYONE:
 			ae_tag = ARCHIVE_ENTRY_ACL_EVERYONE;
 			break;
 #endif
+#else	/* HAVE_DARWIN_ACL */
+		case ACL_EXTENDED_ALLOW:
+			entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
+			r = translate_guid(&a->archive, acl_entry, &ae_id,
+			    &ae_tag, &ae_name);
+			break;
+		case ACL_EXTENDED_DENY:
+			entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_DENY;
+			r = translate_guid(&a->archive, acl_entry, &ae_id,
+			    &ae_tag, &ae_name);
+			break;
+#endif	/* HAVE_DARWIN_ACL */
 		default:
 			/* Skip types that libarchive can't support. */
 			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
 			continue;
 		}
 
-		// XXX acl type maps to allow/deny/audit/YYYY bits
-		// XXX acl_get_entry_type_np on FreeBSD returns EINVAL for
-		// non-NFSv4 ACLs
+#if HAVE_DARWIN_ACL
+		/* Skip if translate_guid() above failed */
+		if (r != 0) {
+			s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
+			continue;
+		}
+#endif
+
+#if !HAVE_DARWIN_ACL
+		// XXX acl_type maps to allow/deny/audit/YYYY bits
 		entry_acl_type = default_entry_acl_type;
-#ifdef ACL_TYPE_NFS4
-		r = acl_get_entry_type_np(acl_entry, &acl_type);
-		if (r == 0) {
+#endif
+#if HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL
+		if (default_entry_acl_type & ARCHIVE_ENTRY_ACL_TYPE_NFS4) {
+#if HAVE_ACL_TYPE_NFS4
+			/*
+			 * acl_get_entry_type_np() fails with non-NFSv4 ACLs
+			 */
+			if (acl_get_entry_type_np(acl_entry, &acl_type) != 0) {
+				archive_set_error(&a->archive, errno, "Failed "
+				    "to get ACL type from a NFSv4 ACL entry");
+				return (ARCHIVE_WARN);
+			}
 			switch (acl_type) {
 			case ACL_ENTRY_TYPE_ALLOW:
 				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALLOW;
@@ -635,29 +1321,54 @@ translate_acl(struct archive_read_disk *a,
 			case ACL_ENTRY_TYPE_ALARM:
 				entry_acl_type = ARCHIVE_ENTRY_ACL_TYPE_ALARM;
 				break;
+			default:
+				archive_set_error(&a->archive, errno,
+				    "Invalid NFSv4 ACL entry type");
+				return (ARCHIVE_WARN);
 			}
-		}
-
-		/*
-		 * Libarchive stores "flag" (NFSv4 inheritance bits)
-		 * in the ae_perm bitmap.
-		 */
-		acl_get_flagset_np(acl_entry, &acl_flagset);
-                for (i = 0; i < (int)(sizeof(acl_inherit_map) / sizeof(acl_inherit_map[0])); ++i) {
-			if (acl_get_flag_np(acl_flagset,
-					    acl_inherit_map[i].platform_inherit))
-				ae_perm |= acl_inherit_map[i].archive_inherit;
+#endif	/* HAVE_ACL_TYPE_NFS4 */
 
-                }
-#endif
+			/*
+			 * Libarchive stores "flag" (NFSv4 inheritance bits)
+			 * in the ae_perm bitmap.
+			 *
+			 * acl_get_flagset_np() fails with non-NFSv4 ACLs
+			 */
+			if (acl_get_flagset_np(acl_entry, &acl_flagset) != 0) {
+				archive_set_error(&a->archive, errno,
+				    "Failed to get flagset from a NFSv4 ACL entry");
+				return (ARCHIVE_WARN);
+			}
+			for (i = 0; i < (int)(sizeof(acl_inherit_map) / sizeof(acl_inherit_map[0])); ++i) {
+				r = acl_get_flag_np(acl_flagset,
+				    acl_inherit_map[i].platform_inherit);
+				if (r == -1) {
+					archive_set_error(&a->archive, errno,
+					    "Failed to check flag in a NFSv4 "
+					    "ACL flagset");
+					return (ARCHIVE_WARN);
+				} else if (r)
+					ae_perm |= acl_inherit_map[i].archive_inherit;
+			}
+		}
+#endif	/* HAVE_ACL_TYPE_NFS4 || HAVE_DARWIN_ACL */
 
-		acl_get_permset(acl_entry, &acl_permset);
+		if (acl_get_permset(acl_entry, &acl_permset) != 0) {
+			archive_set_error(&a->archive, errno,
+			    "Failed to get ACL permission set");
+			return (ARCHIVE_WARN);
+		}
 		for (i = 0; i < (int)(sizeof(acl_perm_map) / sizeof(acl_perm_map[0])); ++i) {
 			/*
 			 * acl_get_perm() is spelled differently on different
 			 * platforms; see above.
 			 */
-			if (ACL_GET_PERM(acl_permset, acl_perm_map[i].platform_perm))
+			r = ACL_GET_PERM(acl_permset, acl_perm_map[i].platform_perm);
+			if (r == -1) {
+				archive_set_error(&a->archive, errno,
+				    "Failed to check permission in an ACL permission set");
+				return (ARCHIVE_WARN);
+			} else if (r)
 				ae_perm |= acl_perm_map[i].archive_perm;
 		}
 
@@ -666,10 +1377,18 @@ translate_acl(struct archive_read_disk *a,
 					    ae_id, ae_name);
 
 		s = acl_get_entry(acl, ACL_NEXT_ENTRY, &acl_entry);
+#if !HAVE_DARWIN_ACL
+		if (s == -1) {
+			archive_set_error(&a->archive, errno,
+			    "Failed to get next ACL entry");
+			return (ARCHIVE_WARN);
+		}
+#endif
 	}
 	return (ARCHIVE_OK);
 }
-#else
+#endif	/* !HAVE_SUN_ACL */
+#else	/* !HAVE_POSIX_ACL && !HAVE_NFS4_ACL */
 static int
 setup_acls(struct archive_read_disk *a,
     struct archive_entry *entry, int *fd)
@@ -679,7 +1398,7 @@ setup_acls(struct archive_read_disk *a,
 	(void)fd;     /* UNUSED */
 	return (ARCHIVE_OK);
 }
-#endif
+#endif	/* !HAVE_POSIX_ACL && !HAVE_NFS4_ACL */
 
 #if (HAVE_FGETXATTR && HAVE_FLISTXATTR && HAVE_LISTXATTR && \
     HAVE_LLISTXATTR && HAVE_GETXATTR && HAVE_LGETXATTR) || \
@@ -699,15 +1418,10 @@ setup_acls(struct archive_read_disk *a,
 
 static int
 setup_xattr(struct archive_read_disk *a,
-    struct archive_entry *entry, const char *name, int fd)
+    struct archive_entry *entry, const char *name, int fd, const char *accpath)
 {
 	ssize_t size;
 	void *value = NULL;
-	const char *accpath;
-
-	accpath = archive_entry_sourcepath(entry);
-	if (accpath == NULL)
-		accpath = archive_entry_pathname(entry);
 
 #if HAVE_FGETXATTR
 	if (fd >= 0)
@@ -772,21 +1486,23 @@ setup_xattrs(struct archive_read_disk *a,
 	const char *path;
 	ssize_t list_size;
 
-	path = archive_entry_sourcepath(entry);
-	if (path == NULL)
-		path = archive_entry_pathname(entry);
+	path = NULL;
 
-	if (*fd < 0 && a->tree != NULL) {
-		if (a->follow_symlinks ||
-		    archive_entry_filetype(entry) != AE_IFLNK)
-			*fd = a->open_on_current_dir(a->tree, path,
-				O_RDONLY | O_NONBLOCK);
-		if (*fd < 0) {
-			if (a->tree_enter_working_dir(a->tree) != 0) {
-				archive_set_error(&a->archive, errno,
-				    "Couldn't access %s", path);
-				return (ARCHIVE_FAILED);
-			}
+	if (*fd < 0) {
+		path = archive_entry_sourcepath(entry);
+		if (path == NULL || (a->tree != NULL &&
+		    a->tree_enter_working_dir(a->tree) != 0))
+			path = archive_entry_pathname(entry);
+		if (path == NULL) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Couldn't determine file path to read "
+			    "extended attributes");
+			return (ARCHIVE_WARN);
+		}
+		if (a->tree != NULL && (a->follow_symlinks ||
+		    archive_entry_filetype(entry) != AE_IFLNK)) {
+			*fd = a->open_on_current_dir(a->tree,
+			    path, O_RDONLY | O_NONBLOCK);
 		}
 	}
 
@@ -849,7 +1565,7 @@ setup_xattrs(struct archive_read_disk *a,
 		if (strncmp(p, "system.", 7) == 0 ||
 				strncmp(p, "xfsroot.", 8) == 0)
 			continue;
-		setup_xattr(a, entry, p, *fd);
+		setup_xattr(a, entry, p, *fd, path);
 	}
 
 	free(list);
@@ -870,19 +1586,16 @@ setup_xattrs(struct archive_read_disk *a,
  */
 static int
 setup_xattr(struct archive_read_disk *a, struct archive_entry *entry,
-    int namespace, const char *name, const char *fullname, int fd);
+    int namespace, const char *name, const char *fullname, int fd,
+    const char *path);
 
 static int
 setup_xattr(struct archive_read_disk *a, struct archive_entry *entry,
-    int namespace, const char *name, const char *fullname, int fd)
+    int namespace, const char *name, const char *fullname, int fd,
+    const char *accpath)
 {
 	ssize_t size;
 	void *value = NULL;
-	const char *accpath;
-
-	accpath = archive_entry_sourcepath(entry);
-	if (accpath == NULL)
-		accpath = archive_entry_pathname(entry);
 
 	if (fd >= 0)
 		size = extattr_get_fd(fd, namespace, name, NULL, 0);
@@ -932,21 +1645,23 @@ setup_xattrs(struct archive_read_disk *a,
 	const char *path;
 	int namespace = EXTATTR_NAMESPACE_USER;
 
-	path = archive_entry_sourcepath(entry);
-	if (path == NULL)
-		path = archive_entry_pathname(entry);
+	path = NULL;
 
-	if (*fd < 0 && a->tree != NULL) {
-		if (a->follow_symlinks ||
-		    archive_entry_filetype(entry) != AE_IFLNK)
-			*fd = a->open_on_current_dir(a->tree, path,
-				O_RDONLY | O_NONBLOCK);
-		if (*fd < 0) {
-			if (a->tree_enter_working_dir(a->tree) != 0) {
-				archive_set_error(&a->archive, errno,
-				    "Couldn't access %s", path);
-				return (ARCHIVE_FAILED);
-			}
+	if (*fd < 0) {
+		path = archive_entry_sourcepath(entry);
+		if (path == NULL || (a->tree != NULL &&
+		    a->tree_enter_working_dir(a->tree) != 0))
+			path = archive_entry_pathname(entry);
+		if (path == NULL) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Couldn't determine file path to read "
+			    "extended attributes");
+			return (ARCHIVE_WARN);
+		}
+		if (a->tree != NULL && (a->follow_symlinks ||
+		    archive_entry_filetype(entry) != AE_IFLNK)) {
+			*fd = a->open_on_current_dir(a->tree,
+			    path, O_RDONLY | O_NONBLOCK);
 		}
 	}
 
@@ -996,7 +1711,7 @@ setup_xattrs(struct archive_read_disk *a,
 		name = buff + strlen(buff);
 		memcpy(name, p + 1, len);
 		name[len] = '\0';
-		setup_xattr(a, entry, namespace, name, buff, *fd);
+		setup_xattr(a, entry, namespace, name, buff, *fd, path);
 		p += 1 + len;
 	}
 
@@ -1024,7 +1739,7 @@ setup_xattrs(struct archive_read_disk *a,
 #if defined(HAVE_LINUX_FIEMAP_H)
 
 /*
- * Linux sparse interface.
+ * Linux FIEMAP sparse interface.
  *
  * The FIEMAP ioctl returns an "extent" for each physical allocation
  * on disk.  We need to process those to generate a more compact list
@@ -1039,7 +1754,7 @@ setup_xattrs(struct archive_read_disk *a,
  */
 
 static int
-setup_sparse(struct archive_read_disk *a,
+setup_sparse_fiemap(struct archive_read_disk *a,
     struct archive_entry *entry, int *fd)
 {
 	char buff[4096];
@@ -1090,8 +1805,8 @@ setup_sparse(struct archive_read_disk *a,
 		if (r < 0) {
 			/* When something error happens, it is better we
 			 * should return ARCHIVE_OK because an earlier
-			 * version(<2.6.28) cannot perfom FS_IOC_FIEMAP. */
-			goto exit_setup_sparse;
+			 * version(<2.6.28) cannot perform FS_IOC_FIEMAP. */
+			goto exit_setup_sparse_fiemap;
 		}
 		if (fm->fm_mapped_extents == 0) {
 			if (iters == 0) {
@@ -1126,23 +1841,33 @@ setup_sparse(struct archive_read_disk *a,
 		} else
 			break;
 	}
-exit_setup_sparse:
+exit_setup_sparse_fiemap:
 	return (exit_sts);
 }
 
-#elif defined(SEEK_HOLE) && defined(SEEK_DATA) && defined(_PC_MIN_HOLE_SIZE)
+#if !defined(SEEK_HOLE) || !defined(SEEK_DATA)
+static int
+setup_sparse(struct archive_read_disk *a,
+    struct archive_entry *entry, int *fd)
+{
+	return setup_sparse_fiemap(a, entry, fd);
+}
+#endif
+#endif	/* defined(HAVE_LINUX_FIEMAP_H) */
+
+#if defined(SEEK_HOLE) && defined(SEEK_DATA)
 
 /*
- * FreeBSD and Solaris sparse interface.
+ * SEEK_HOLE sparse interface (FreeBSD, Linux, Solaris)
  */
 
 static int
 setup_sparse(struct archive_read_disk *a,
     struct archive_entry *entry, int *fd)
 {
 	int64_t size;
-	off_t initial_off; /* FreeBSD/Solaris only, so off_t okay here */
-	off_t off_s, off_e; /* FreeBSD/Solaris only, so off_t okay here */
+	off_t initial_off;
+	off_t off_s, off_e;
 	int exit_sts = ARCHIVE_OK;
 	int check_fully_sparse = 0;
 
@@ -1168,8 +1893,10 @@ setup_sparse(struct archive_read_disk *a,
 	}
 
 	if (*fd >= 0) {
+#ifdef _PC_MIN_HOLE_SIZE
 		if (fpathconf(*fd, _PC_MIN_HOLE_SIZE) <= 0)
 			return (ARCHIVE_OK);
+#endif
 		initial_off = lseek(*fd, 0, SEEK_CUR);
 		if (initial_off != 0)
 			lseek(*fd, 0, SEEK_SET);
@@ -1180,8 +1907,10 @@ setup_sparse(struct archive_read_disk *a,
 		if (path == NULL)
 			path = archive_entry_pathname(entry);
 			
+#ifdef _PC_MIN_HOLE_SIZE
 		if (pathconf(path, _PC_MIN_HOLE_SIZE) <= 0)
 			return (ARCHIVE_OK);
+#endif
 		*fd = open(path, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
 		if (*fd < 0) {
 			archive_set_error(&a->archive, errno,
@@ -1192,6 +1921,19 @@ setup_sparse(struct archive_read_disk *a,
 		initial_off = 0;
 	}
 
+#ifndef _PC_MIN_HOLE_SIZE
+	/* Check if the underlying filesystem supports seek hole */
+	off_s = lseek(*fd, 0, SEEK_HOLE);
+	if (off_s < 0)
+#if defined(HAVE_LINUX_FIEMAP_H)
+		return setup_sparse_fiemap(a, entry, fd);
+#else
+		goto exit_setup_sparse;
+#endif
+	else if (off_s > 0)
+		lseek(*fd, 0, SEEK_SET);
+#endif
+
 	off_s = 0;
 	size = archive_entry_size(entry);
 	while (off_s < size) {
@@ -1223,7 +1965,7 @@ setup_sparse(struct archive_read_disk *a,
 			goto exit_setup_sparse;
 		}
 		if (off_s == 0 && off_e == size)
-			break;/* This is not spase. */
+			break;/* This is not sparse. */
 		archive_entry_sparse_add_entry(entry, off_s,
 			off_e - off_s);
 		off_s = off_e;
@@ -1241,7 +1983,7 @@ setup_sparse(struct archive_read_disk *a,
 	return (exit_sts);
 }
 
-#else
+#elif !defined(HAVE_LINUX_FIEMAP_H)
 
 /*
  * Generic (stub) sparse support.