@@ -39,9 +39,9 @@ __FBSDID("$FreeBSD$");
 #ifdef HAVE_SYS_EXTATTR_H
 #include <sys/extattr.h>
 #endif
-#if defined(HAVE_SYS_XATTR_H)
+#if HAVE_SYS_XATTR_H
 #include <sys/xattr.h>
-#elif defined(HAVE_ATTR_XATTR_H)
+#elif HAVE_ATTR_XATTR_H
 #include <attr/xattr.h>
 #endif
 #ifdef HAVE_SYS_EA_H
@@ -575,10 +575,55 @@ _archive_write_disk_header(struct archive *_a, struct archive_entry *entry)
 	if (a->flags & ARCHIVE_EXTRACT_TIME)
 		a->todo |= TODO_TIMES;
 	if (a->flags & ARCHIVE_EXTRACT_ACL) {
+#if ARCHIVE_ACL_DARWIN
+		/*
+		 * On MacOS, platform ACLs get stored in mac_metadata, too.
+		 * If we intend to extract mac_metadata and it is present
+		 * we skip extracting libarchive NFSv4 ACLs.
+		 */
+		size_t metadata_size;
+
+		if ((a->flags & ARCHIVE_EXTRACT_MAC_METADATA) == 0 ||
+		    archive_entry_mac_metadata(a->entry,
+		    &metadata_size) == NULL || metadata_size == 0)
+#endif
+#if ARCHIVE_ACL_LIBRICHACL
+		/*
+		 * RichACLs are stored in an extended attribute.
+		 * If we intend to extract extended attributes and have this
+		 * attribute we skip extracting libarchive NFSv4 ACLs.
+		 */
+		short extract_acls = 1;
+		if (a->flags & ARCHIVE_EXTRACT_XATTR && (
+		    archive_entry_acl_types(a->entry) &
+		    ARCHIVE_ENTRY_ACL_TYPE_NFS4)) {
+			const char *attr_name;
+			const void *attr_value;
+			size_t attr_size;
+			int i = archive_entry_xattr_reset(a->entry);
+			while (i--) {
+				archive_entry_xattr_next(a->entry, &attr_name,
+				    &attr_value, &attr_size);
+				if (attr_name != NULL && attr_value != NULL &&
+				    attr_size > 0 && strcmp(attr_name,
+				    "trusted.richacl") == 0) {
+					extract_acls = 0;
+					break;
+				}
+			}
+		}
+		if (extract_acls)
+#endif
+#if ARCHIVE_ACL_DARWIN || ARCHIVE_ACL_LIBRICHACL
+		{
+#endif
 		if (archive_entry_filetype(a->entry) == AE_IFDIR)
 			a->deferred |= TODO_ACLS;
 		else
 			a->todo |= TODO_ACLS;
+#if ARCHIVE_ACL_DARWIN || ARCHIVE_ACL_LIBRICHACL
+		}
+#endif
 	}
 	if (a->flags & ARCHIVE_EXTRACT_MAC_METADATA) {
 		if (archive_entry_filetype(a->entry) == AE_IFDIR)
@@ -619,8 +664,21 @@ _archive_write_disk_header(struct archive *_a, struct archive_entry *entry)
 	}
 #endif
 
-	if (a->flags & ARCHIVE_EXTRACT_XATTR)
+	if (a->flags & ARCHIVE_EXTRACT_XATTR) {
+#if ARCHIVE_XATTR_DARWIN
+		/*
+		 * On MacOS, extended attributes get stored in mac_metadata,
+		 * too. If we intend to extract mac_metadata and it is present
+		 * we skip extracting extended attributes.
+		 */
+		size_t metadata_size;
+
+		if ((a->flags & ARCHIVE_EXTRACT_MAC_METADATA) == 0 ||
+		    archive_entry_mac_metadata(a->entry,
+		    &metadata_size) == NULL || metadata_size == 0)
+#endif
 		a->todo |= TODO_XATTR;
+	}
 	if (a->flags & ARCHIVE_EXTRACT_FFLAGS)
 		a->todo |= TODO_FFLAGS;
 	if (a->flags & ARCHIVE_EXTRACT_SECURE_SYMLINKS) {
@@ -1703,25 +1761,11 @@ _archive_write_disk_finish_entry(struct archive *_a)
 	 */
 	if (a->todo & TODO_ACLS) {
 		int r2;
-#ifdef HAVE_DARWIN_ACL
-		/*
-		 * On Mac OS, platform ACLs are stored also in mac_metadata by
-		 * the operating system. If mac_metadata is present it takes
-		 * precedence and we skip extracting libarchive NFSv4 ACLs
-		 */
-		const void *metadata;
-		size_t metadata_size;
-		metadata = archive_entry_mac_metadata(a->entry, &metadata_size);
-		if ((a->todo & TODO_MAC_METADATA) == 0 ||
-		    metadata == NULL || metadata_size == 0) {
-#endif
 		r2 = archive_write_disk_set_acls(&a->archive, a->fd,
 		    archive_entry_pathname(a->entry),
-		    archive_entry_acl(a->entry));
+		    archive_entry_acl(a->entry),
+		    archive_entry_mode(a->entry));
 		if (r2 < ret) ret = r2;
-#ifdef HAVE_DARWIN_ACL
-		}
-#endif
 	}
 
 finish_metadata:
@@ -2293,13 +2337,8 @@ _archive_write_disk_close(struct archive *_a)
 		if (p->fixup & TODO_MODE_BASE)
 			chmod(p->name, p->mode);
 		if (p->fixup & TODO_ACLS)
-#ifdef HAVE_DARWIN_ACL
-			if ((p->fixup & TODO_MAC_METADATA) == 0 ||
-			    p->mac_metadata == NULL ||
-			    p->mac_metadata_size == 0)
-#endif
-				archive_write_disk_set_acls(&a->archive,
-				    -1, p->name, &p->acl);
+			archive_write_disk_set_acls(&a->archive, -1, p->name,
+			    &p->acl, p->mode);
 		if (p->fixup & TODO_FFLAGS)
 			set_fflags_platform(a, -1, p->name,
 			    p->mode, p->fflags_set, 0);
@@ -2467,7 +2506,7 @@ fsobj_error(int *a_eno, struct archive_string *a_estr,
 	if (a_eno)
 		*a_eno = err;
 	if (a_estr)
-		archive_string_sprintf(a_estr, errstr, path);
+		archive_string_sprintf(a_estr, "%s%s", errstr, path);
 }
 
 /*
@@ -2573,7 +2612,7 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 				 * with the deep-directory editing.
 				 */
 				fsobj_error(a_eno, a_estr, errno,
-				    "Could not stat %s", path);
+				    "Could not stat ", path);
 				res = ARCHIVE_FAILED;
 				break;
 			}
@@ -2582,7 +2621,7 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 				if (chdir(head) != 0) {
 					tail[0] = c;
 					fsobj_error(a_eno, a_estr, errno,
-					    "Could not chdir %s", path);
+					    "Could not chdir ", path);
 					res = (ARCHIVE_FATAL);
 					break;
 				}
@@ -2599,7 +2638,7 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 				if (unlink(head)) {
 					tail[0] = c;
 					fsobj_error(a_eno, a_estr, errno,
-					    "Could not remove symlink %s",
+					    "Could not remove symlink ",
 					    path);
 					res = ARCHIVE_FAILED;
 					break;
@@ -2618,7 +2657,7 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 				/*
 				if (!S_ISLNK(path)) {
 					fsobj_error(a_eno, a_estr, 0,
-					    "Removing symlink %s", path);
+					    "Removing symlink ", path);
 				}
 				*/
 				/* Symlink gone.  No more problem! */
@@ -2630,7 +2669,7 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 					tail[0] = c;
 					fsobj_error(a_eno, a_estr, 0,
 					    "Cannot remove intervening "
-					    "symlink %s", path);
+					    "symlink ", path);
 					res = ARCHIVE_FAILED;
 					break;
 				}
@@ -2652,7 +2691,7 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 					} else {
 						fsobj_error(a_eno, a_estr,
 						    errno,
-						    "Could not stat %s", path);
+						    "Could not stat ", path);
 						res = (ARCHIVE_FAILED);
 						break;
 					}
@@ -2661,7 +2700,7 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 						tail[0] = c;
 						fsobj_error(a_eno, a_estr,
 						    errno,
-						    "Could not chdir %s", path);
+						    "Could not chdir ", path);
 						res = (ARCHIVE_FATAL);
 						break;
 					}
@@ -2674,14 +2713,14 @@ check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
 					tail[0] = c;
 					fsobj_error(a_eno, a_estr, 0,
 					    "Cannot extract through "
-					    "symlink %s", path);
+					    "symlink ", path);
 					res = ARCHIVE_FAILED;
 					break;
 				}
 			} else {
 				tail[0] = c;
 				fsobj_error(a_eno, a_estr, 0,
-				    "Cannot extract through symlink %s", path);
+				    "Cannot extract through symlink ", path);
 				res = ARCHIVE_FAILED;
 				break;
 			}
@@ -4044,81 +4083,111 @@ fixup_appledouble(struct archive_write_disk *a, const char *pathname)
 }
 #endif
 
-#if HAVE_LSETXATTR || HAVE_LSETEA
+#if ARCHIVE_XATTR_LINUX || ARCHIVE_XATTR_DARWIN || ARCHIVE_XATTR_AIX
 /*
- * Restore extended attributes -  Linux and AIX implementations:
+ * Restore extended attributes -  Linux, Darwin and AIX implementations:
  * AIX' ea interface is syntaxwise identical to the Linux xattr interface.
  */
 static int
 set_xattrs(struct archive_write_disk *a)
 {
 	struct archive_entry *entry = a->entry;
-	static int warning_done = 0;
+	struct archive_string errlist;
 	int ret = ARCHIVE_OK;
 	int i = archive_entry_xattr_reset(entry);
+	short fail = 0;
+
+	archive_string_init(&errlist);
 
 	while (i--) {
 		const char *name;
 		const void *value;
 		size_t size;
+		int e;
+
 		archive_entry_xattr_next(entry, &name, &value, &size);
-		if (name != NULL &&
-				strncmp(name, "xfsroot.", 8) != 0 &&
-				strncmp(name, "system.", 7) != 0) {
-			int e;
-#if HAVE_FSETXATTR
-			if (a->fd >= 0)
-				e = fsetxattr(a->fd, name, value, size, 0);
-			else
-#elif HAVE_FSETEA
-			if (a->fd >= 0)
-				e = fsetea(a->fd, name, value, size, 0);
-			else
+
+		if (name == NULL)
+			continue;
+#if ARCHIVE_XATTR_LINUX
+		/* Linux: quietly skip POSIX.1e ACL extended attributes */
+		if (strncmp(name, "system.", 7) == 0 &&
+		   (strcmp(name + 7, "posix_acl_access") == 0 ||
+		    strcmp(name + 7, "posix_acl_default") == 0))
+			continue;
+		if (strncmp(name, "trusted.SGI_", 12) == 0 &&
+		   (strcmp(name + 12, "ACL_DEFAULT") == 0 ||
+		    strcmp(name + 12, "ACL_FILE") == 0))
+			continue;
+
+		/* Linux: xfsroot namespace is obsolete and unsupported */
+		if (strncmp(name, "xfsroot.", 8) == 0) {
+			fail = 1;
+			archive_strcat(&errlist, name);
+			archive_strappend_char(&errlist, ' ');
+			continue;
+		}
 #endif
-			{
-#if HAVE_LSETXATTR
-				e = lsetxattr(archive_entry_pathname(entry),
-				    name, value, size, 0);
-#elif HAVE_LSETEA
-				e = lsetea(archive_entry_pathname(entry),
-				    name, value, size, 0);
+
+		if (a->fd >= 0) {
+#if ARCHIVE_XATTR_LINUX
+			e = fsetxattr(a->fd, name, value, size, 0);
+#elif ARCHIVE_XATTR_DARWIN
+			e = fsetxattr(a->fd, name, value, size, 0, 0);
+#elif ARCHIVE_XATTR_AIX
+			e = fsetea(a->fd, name, value, size, 0);
 #endif
-			}
-			if (e == -1) {
-				if (errno == ENOTSUP || errno == ENOSYS) {
-					if (!warning_done) {
-						warning_done = 1;
-						archive_set_error(&a->archive,
-						    errno,
-						    "Cannot restore extended "
-						    "attributes on this file "
-						    "system");
-					}
-				} else
-					archive_set_error(&a->archive, errno,
-					    "Failed to set extended attribute");
-				ret = ARCHIVE_WARN;
-			}
 		} else {
-			archive_set_error(&a->archive,
-			    ARCHIVE_ERRNO_FILE_FORMAT,
-			    "Invalid extended attribute encountered");
+#if ARCHIVE_XATTR_LINUX
+			e = lsetxattr(archive_entry_pathname(entry),
+			    name, value, size, 0);
+#elif ARCHIVE_XATTR_DARWIN
+			e = setxattr(archive_entry_pathname(entry),
+			    name, value, size, 0, XATTR_NOFOLLOW);
+#elif ARCHIVE_XATTR_AIX
+			e = lsetea(archive_entry_pathname(entry),
+			    name, value, size, 0);
+#endif
+		}
+		if (e == -1) {
 			ret = ARCHIVE_WARN;
+			archive_strcat(&errlist, name);
+			archive_strappend_char(&errlist, ' ');
+			if (errno != ENOTSUP && errno != ENOSYS)
+				fail = 1;
 		}
 	}
+
+	if (ret == ARCHIVE_WARN) {
+		if (fail && errlist.length > 0) {
+			errlist.length--;
+			errlist.s[errlist.length] = '\0';
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Cannot restore extended attributes: %s",
+			    errlist.s);
+		} else
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Cannot restore extended "
+			    "attributes on this file system.");
+	}
+
+	archive_string_free(&errlist);
 	return (ret);
 }
-#elif HAVE_EXTATTR_SET_FILE && HAVE_DECL_EXTATTR_NAMESPACE_USER
+#elif ARCHIVE_XATTR_FREEBSD
 /*
  * Restore extended attributes -  FreeBSD implementation
  */
 static int
 set_xattrs(struct archive_write_disk *a)
 {
 	struct archive_entry *entry = a->entry;
-	static int warning_done = 0;
+	struct archive_string errlist;
 	int ret = ARCHIVE_OK;
 	int i = archive_entry_xattr_reset(entry);
+	short fail = 0;
+
+	archive_string_init(&errlist);
 
 	while (i--) {
 		const char *name;
@@ -4134,46 +4203,47 @@ set_xattrs(struct archive_write_disk *a)
 				name += 5;
 				namespace = EXTATTR_NAMESPACE_USER;
 			} else {
-				/* Warn about other extended attributes. */
-				archive_set_error(&a->archive,
-				    ARCHIVE_ERRNO_FILE_FORMAT,
-				    "Can't restore extended attribute ``%s''",
-				    name);
+				/* Other namespaces are unsupported */
+				archive_strcat(&errlist, name);
+				archive_strappend_char(&errlist, ' ');
+				fail = 1;
 				ret = ARCHIVE_WARN;
 				continue;
 			}
-			errno = 0;
-#if HAVE_EXTATTR_SET_FD
-			if (a->fd >= 0)
+
+			if (a->fd >= 0) {
 				e = extattr_set_fd(a->fd, namespace, name,
 				    value, size);
-			else
-#endif
-			/* TODO: should we use extattr_set_link() instead? */
-			{
-				e = extattr_set_file(
+			} else {
+				e = extattr_set_link(
 				    archive_entry_pathname(entry), namespace,
 				    name, value, size);
 			}
 			if (e != (int)size) {
-				if (errno == ENOTSUP || errno == ENOSYS) {
-					if (!warning_done) {
-						warning_done = 1;
-						archive_set_error(&a->archive,
-						    errno,
-						    "Cannot restore extended "
-						    "attributes on this file "
-						    "system");
-					}
-				} else {
-					archive_set_error(&a->archive, errno,
-					    "Failed to set extended attribute");
-				}
-
+				archive_strcat(&errlist, name);
+				archive_strappend_char(&errlist, ' ');
 				ret = ARCHIVE_WARN;
+				if (errno != ENOTSUP && errno != ENOSYS)
+					fail = 1;
 			}
 		}
 	}
+
+	if (ret == ARCHIVE_WARN) {
+		if (fail && errlist.length > 0) {
+			errlist.length--;
+			errlist.s[errlist.length] = '\0';
+
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Cannot restore extended attributes: %s",
+			    errlist.s);
+		} else
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Cannot restore extended "
+			    "attributes on this file system.");
+	}
+
+	archive_string_free(&errlist);
 	return (ret);
 }
 #else
@@ -4239,5 +4309,19 @@ older(struct stat *st, struct archive_entry *entry)
 	return (0);
 }
 
+#ifndef ARCHIVE_ACL_SUPPORT
+int
+archive_write_disk_set_acls(struct archive *a, int fd, const char *name,
+    struct archive_acl *abstract_acl, __LA_MODE_T mode)
+{
+	(void)a; /* UNUSED */
+	(void)fd; /* UNUSED */
+	(void)name; /* UNUSED */
+	(void)abstract_acl; /* UNUSED */
+	(void)mode; /* UNUSED */
+	return (ARCHIVE_OK);
+}
+#endif
+
 #endif /* !_WIN32 || __CYGWIN__ */
 