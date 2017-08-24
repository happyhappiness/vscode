@@ -1,6 +1,6 @@
 /*-
  * Copyright (c) 2003-2009 Tim Kientzle
- * Copyright (c) 2010,2011 Michihiro NAKAJIMA
+ * Copyright (c) 2010-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -52,6 +52,19 @@ __FBSDID("$FreeBSD$");
 #ifdef HAVE_LINUX_MAGIC_H
 #include <linux/magic.h>
 #endif
+#ifdef HAVE_LINUX_FS_H
+#include <linux/fs.h>
+#endif
+/*
+ * Some Linux distributions have both linux/ext2_fs.h and ext2fs/ext2_fs.h.
+ * As the include guards don't agree, the order of include is important.
+ */
+#ifdef HAVE_LINUX_EXT2_FS_H
+#include <linux/ext2_fs.h>      /* for Linux file flags */
+#endif
+#if defined(HAVE_EXT2FS_EXT2_FS_H) && !defined(__CYGWIN__)
+#include <ext2fs/ext2_fs.h>     /* Linux file flags, broken on Cygwin */
+#endif
 #ifdef HAVE_DIRECT_H
 #include <direct.h>
 #endif
@@ -76,6 +89,9 @@ __FBSDID("$FreeBSD$");
 #ifdef HAVE_UNISTD_H
 #include <unistd.h>
 #endif
+#ifdef HAVE_SYS_IOCTL_H
+#include <sys/ioctl.h>
+#endif
 
 #include "archive.h"
 #include "archive_string.h"
@@ -89,6 +105,9 @@ __FBSDID("$FreeBSD$");
 #ifndef O_BINARY
 #define O_BINARY	0
 #endif
+#ifndef O_CLOEXEC
+#define O_CLOEXEC	0
+#endif
 
 /*-
  * This is a new directory-walking system that addresses a number
@@ -222,6 +241,7 @@ struct tree {
 	char			 symlink_mode;
 	struct filesystem	*current_filesystem;
 	struct filesystem	*filesystem_table;
+	int			 initial_filesystem_id;
 	int			 current_filesystem_id;
 	int			 max_filesystem_id;
 	int			 allocated_filesytem;
@@ -240,6 +260,7 @@ struct tree {
 #define	onWorkingDir	64 /* We are on the working dir where we are
 			    * reading directory entry at this time. */
 #define	needsRestoreTimes 128
+#define	onInitialDir	256 /* We are on the initial dir. */
 
 static int
 tree_dir_next_posix(struct tree *t);
@@ -342,6 +363,8 @@ static const char *trivial_lookup_uname(void *, int64_t uid);
 static int	setup_sparse(struct archive_read_disk *, struct archive_entry *);
 static int	close_and_restore_time(int fd, struct tree *,
 		    struct restore_time *);
+static int	open_on_current_dir(struct tree *, const char *, int);
+static int	tree_dup(int);
 
 
 static struct archive_vtable *
@@ -430,16 +453,19 @@ archive_read_disk_new(void)
 {
 	struct archive_read_disk *a;
 
-	a = (struct archive_read_disk *)malloc(sizeof(*a));
+	a = (struct archive_read_disk *)calloc(1, sizeof(*a));
 	if (a == NULL)
 		return (NULL);
-	memset(a, 0, sizeof(*a));
 	a->archive.magic = ARCHIVE_READ_DISK_MAGIC;
 	a->archive.state = ARCHIVE_STATE_NEW;
 	a->archive.vtable = archive_read_disk_vtable();
 	a->lookup_uname = trivial_lookup_uname;
 	a->lookup_gname = trivial_lookup_gname;
-	a->entry_wd_fd = -1;
+	a->enable_copyfile = 1;
+	a->traverse_mount_points = 1;
+	a->open_on_current_dir = open_on_current_dir;
+	a->tree_current_dir_fd = tree_current_dir_fd;
+	a->tree_enter_working_dir = tree_enter_working_dir;
 	return (&a->archive);
 }
 
@@ -555,6 +581,37 @@ archive_read_disk_set_atime_restored(struct archive *_a)
 #endif
 }
 
+int
+archive_read_disk_set_behavior(struct archive *_a, int flags)
+{
+	struct archive_read_disk *a = (struct archive_read_disk *)_a;
+	int r = ARCHIVE_OK;
+
+	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
+	    ARCHIVE_STATE_ANY, "archive_read_disk_honor_nodump");
+
+	if (flags & ARCHIVE_READDISK_RESTORE_ATIME)
+		r = archive_read_disk_set_atime_restored(_a);
+	else {
+		a->restore_time = 0;
+		if (a->tree != NULL)
+			a->tree->flags &= ~needsRestoreTimes;
+	}
+	if (flags & ARCHIVE_READDISK_HONOR_NODUMP)
+		a->honor_nodump = 1;
+	else
+		a->honor_nodump = 0;
+	if (flags & ARCHIVE_READDISK_MAC_COPYFILE)
+		a->enable_copyfile = 1;
+	else
+		a->enable_copyfile = 0;
+	if (flags & ARCHIVE_READDISK_NO_TRAVERSE_MOUNTS)
+		a->traverse_mount_points = 0;
+	else
+		a->traverse_mount_points = 1;
+	return (r);
+}
+
 /*
  * Trivial implementations of gname/uname lookup functions.
  * These are normally overridden by the client, but these stub
@@ -664,7 +721,7 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 	 * Open the current file.
 	 */
 	if (t->entry_fd < 0) {
-		int flags = O_RDONLY | O_BINARY;
+		int flags = O_RDONLY | O_BINARY | O_CLOEXEC;
 
 		/*
 		 * Eliminate or reduce cache effects if we can.
@@ -685,13 +742,9 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 			flags |= O_NOATIME;
 		do {
 #endif
-#ifdef HAVE_OPENAT
-			t->entry_fd = openat(tree_current_dir_fd(t),
+			t->entry_fd = open_on_current_dir(t,
 			    tree_current_access_path(t), flags);
-#else
-			tree_enter_working_dir(t);
-			t->entry_fd = open(tree_current_access_path(t), flags);
-#endif
+			__archive_ensure_cloexec_flag(t->entry_fd);
 #if defined(O_NOATIME)
 			/*
 			 * When we did open the file with O_NOATIME flag,
@@ -733,7 +786,7 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 	t->entry_buff_size = t->current_filesystem->buff_size;
 
 	buffbytes = t->entry_buff_size;
-	if (buffbytes > t->current_sparse->length)
+	if ((int64_t)buffbytes > t->current_sparse->length)
 		buffbytes = t->current_sparse->length;
 
 	/*
@@ -802,29 +855,17 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 }
 
 static int
-_archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
+next_entry(struct archive_read_disk *a, struct tree *t,
+    struct archive_entry *entry)
 {
-	struct archive_read_disk *a = (struct archive_read_disk *)_a;
-	struct tree *t;
 	const struct stat *st; /* info to use for this entry */
 	const struct stat *lst;/* lstat() information */
-	int descend, fd = -1, r;
-
-	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
-	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
-	    "archive_read_next_header2");
+	const char *name;
+	int descend, r;
 
-	t = a->tree;
-	if (t->entry_fd >= 0) {
-		close_and_restore_time(t->entry_fd, t, &t->restore_time);
-		t->entry_fd = -1;
-	}
-#if !(defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR))
-	/* Restore working directory. */
-	tree_enter_working_dir(t);
-#endif
 	st = NULL;
 	lst = NULL;
+	t->descend = 0;
 	do {
 		switch (tree_next(t)) {
 		case TREE_ERROR_FATAL:
@@ -859,6 +900,38 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		}	
 	} while (lst == NULL);
 
+#ifdef __APPLE__
+	if (a->enable_copyfile) {
+		/* If we're using copyfile(), ignore "._XXX" files. */
+		const char *bname = strrchr(tree_current_path(t), '/');
+		if (bname == NULL)
+			bname = tree_current_path(t);
+		else
+			++bname;
+		if (bname[0] == '.' && bname[1] == '_')
+			return (ARCHIVE_RETRY);
+	}
+#endif
+
+	archive_entry_copy_pathname(entry, tree_current_path(t));
+	/*
+	 * Perform path matching.
+	 */
+	if (a->matching) {
+		r = archive_match_path_excluded(a->matching, entry);
+		if (r < 0) {
+			archive_set_error(&(a->archive), errno,
+			    "Faild : %s", archive_error_string(a->matching));
+			return (r);
+		}
+		if (r) {
+			if (a->excluded_cb_func)
+				a->excluded_cb_func(&(a->archive),
+				    a->excluded_cb_data, entry);
+			return (ARCHIVE_RETRY);
+		}
+	}
+
 	/*
 	 * Distinguish 'L'/'P'/'H' symlink following.
 	 */
@@ -897,53 +970,149 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		tree_enter_initial_dir(t);
 		return (ARCHIVE_FATAL);
 	}
+	if (t->initial_filesystem_id == -1)
+		t->initial_filesystem_id = t->current_filesystem_id;
+	if (!a->traverse_mount_points) {
+		if (t->initial_filesystem_id != t->current_filesystem_id)
+			return (ARCHIVE_RETRY);
+	}
 	t->descend = descend;
 
-	archive_entry_set_pathname(entry, tree_current_path(t));
-	archive_entry_copy_sourcepath(entry, tree_current_access_path(t));
+	/*
+	 * Honor nodump flag.
+	 * If the file is marked with nodump flag, do not return this entry.
+	 */
+	if (a->honor_nodump) {
+#if defined(HAVE_STRUCT_STAT_ST_FLAGS) && defined(UF_NODUMP)
+		if (st->st_flags & UF_NODUMP)
+			return (ARCHIVE_RETRY);
+#elif defined(EXT2_IOC_GETFLAGS) && defined(EXT2_NODUMP_FL) &&\
+      defined(HAVE_WORKING_EXT2_IOC_GETFLAGS)
+		if (S_ISREG(st->st_mode) || S_ISDIR(st->st_mode)) {
+			int stflags;
+
+			t->entry_fd = open_on_current_dir(t,
+			    tree_current_access_path(t),
+			    O_RDONLY | O_NONBLOCK | O_CLOEXEC);
+			__archive_ensure_cloexec_flag(t->entry_fd);
+			if (t->entry_fd >= 0) {
+				r = ioctl(t->entry_fd, EXT2_IOC_GETFLAGS,
+					&stflags);
+				if (r == 0 && (stflags & EXT2_NODUMP_FL) != 0)
+					return (ARCHIVE_RETRY);
+			}
+		}
+#endif
+	}
+
 	archive_entry_copy_stat(entry, st);
 
-	/* Save the times to be restored. */
+	/* Save the times to be restored. This must be in before
+	 * calling archive_read_disk_descend() or any chance of it,
+	 * especially, invokng a callback. */
 	t->restore_time.mtime = archive_entry_mtime(entry);
 	t->restore_time.mtime_nsec = archive_entry_mtime_nsec(entry);
 	t->restore_time.atime = archive_entry_atime(entry);
 	t->restore_time.atime_nsec = archive_entry_atime_nsec(entry);
 	t->restore_time.filetype = archive_entry_filetype(entry);
 	t->restore_time.noatime = t->current_filesystem->noatime;
 
-#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
 	/*
-	 * Open the current file to freely gather its metadata anywhere in
-	 * working directory.
-	 * Note: A symbolic link file cannot be opened with O_NOFOLLOW.
+	 * Perform time matching.
 	 */
-	if (a->follow_symlinks || archive_entry_filetype(entry) != AE_IFLNK)
-		fd = openat(tree_current_dir_fd(t), tree_current_access_path(t),
-		    O_RDONLY | O_NONBLOCK);
-	/* Restore working directory if openat() operation failed or
-	 * the file is a symbolic link. */
-	if (fd < 0)
-		tree_enter_working_dir(t);
+	if (a->matching) {
+		r = archive_match_time_excluded(a->matching, entry);
+		if (r < 0) {
+			archive_set_error(&(a->archive), errno,
+			    "Faild : %s", archive_error_string(a->matching));
+			return (r);
+		}
+		if (r) {
+			if (a->excluded_cb_func)
+				a->excluded_cb_func(&(a->archive),
+				    a->excluded_cb_data, entry);
+			return (ARCHIVE_RETRY);
+		}
+	}
 
-	/* The current directory fd is needed at
-	 * archive_read_disk_entry_from_file() function to read link data
-	 * with readlinkat(). */
-	a->entry_wd_fd = tree_current_dir_fd(t);
-#endif
+	/* Lookup uname/gname */
+	name = archive_read_disk_uname(&(a->archive), archive_entry_uid(entry));
+	if (name != NULL)
+		archive_entry_copy_uname(entry, name);
+	name = archive_read_disk_gname(&(a->archive), archive_entry_gid(entry));
+	if (name != NULL)
+		archive_entry_copy_gname(entry, name);
+
+	/*
+	 * Perform owner matching.
+	 */
+	if (a->matching) {
+		r = archive_match_owner_excluded(a->matching, entry);
+		if (r < 0) {
+			archive_set_error(&(a->archive), errno,
+			    "Faild : %s", archive_error_string(a->matching));
+			return (r);
+		}
+		if (r) {
+			if (a->excluded_cb_func)
+				a->excluded_cb_func(&(a->archive),
+				    a->excluded_cb_data, entry);
+			return (ARCHIVE_RETRY);
+		}
+	}
+
+	/*
+	 * Invoke a meta data filter callback.
+	 */
+	if (a->metadata_filter_func) {
+		if (!a->metadata_filter_func(&(a->archive),
+		    a->metadata_filter_data, entry))
+			return (ARCHIVE_RETRY);
+	}
 
 	/*
 	 * Populate the archive_entry with metadata from the disk.
 	 */
-	r = archive_read_disk_entry_from_file(&(a->archive), entry, fd, st);
+	archive_entry_copy_sourcepath(entry, tree_current_access_path(t));
+	r = archive_read_disk_entry_from_file(&(a->archive), entry,
+		t->entry_fd, st);
 
-	/* Close the file descriptor used for reding the current file
-	 * metadata at archive_read_disk_entry_from_file(). */
-	if (fd >= 0)
-		close(fd);
+	return (r);
+}
+
+static int
+_archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
+{
+	struct archive_read_disk *a = (struct archive_read_disk *)_a;
+	struct tree *t;
+	int r;
+
+	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
+	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
+	    "archive_read_next_header2");
+
+	t = a->tree;
+	if (t->entry_fd >= 0) {
+		close_and_restore_time(t->entry_fd, t, &t->restore_time);
+		t->entry_fd = -1;
+	}
+
+	for (;;) {
+		r = next_entry(a, t, entry);
+		if (t->entry_fd >= 0) {
+			close(t->entry_fd);
+			t->entry_fd = -1;
+		}
+
+		if (r == ARCHIVE_RETRY) {
+			archive_entry_clear(entry);
+			continue;
+		}
+		break;
+	}
 
 	/* Return to the initial directory. */
 	tree_enter_initial_dir(t);
-	archive_entry_copy_sourcepath(entry, tree_current_path(t));
 
 	/*
 	 * EOF and FATAL are persistent at this layer.  By
@@ -956,6 +1125,8 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		break;
 	case ARCHIVE_OK:
 	case ARCHIVE_WARN:
+		/* Overwrite the sourcepath based on the initial directory. */
+		archive_entry_copy_sourcepath(entry, tree_current_path(t));
 		t->entry_total = 0;
 		if (archive_entry_filetype(entry) == AE_IFREG) {
 			t->nlink = archive_entry_nlink(entry);
@@ -1018,6 +1189,48 @@ setup_sparse(struct archive_read_disk *a, struct archive_entry *entry)
 	return (ARCHIVE_OK);
 }
 
+int
+archive_read_disk_set_matching(struct archive *_a, struct archive *_ma,
+    void (*_excluded_func)(struct archive *, void *, struct archive_entry *),
+    void *_client_data)
+{
+	struct archive_read_disk *a = (struct archive_read_disk *)_a;
+	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
+	    ARCHIVE_STATE_ANY, "archive_read_disk_set_matching");
+	a->matching = _ma;
+	a->excluded_cb_func = _excluded_func;
+	a->excluded_cb_data = _client_data;
+	return (ARCHIVE_OK);
+}
+
+int
+archive_read_disk_set_metadata_filter_callback(struct archive *_a,
+    int (*_metadata_filter_func)(struct archive *, void *,
+    struct archive_entry *), void *_client_data)
+{
+	struct archive_read_disk *a = (struct archive_read_disk *)_a;
+
+	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_ANY,
+	    "archive_read_disk_set_metadata_filter_callback");
+
+	a->metadata_filter_func = _metadata_filter_func;
+	a->metadata_filter_data = _client_data;
+	return (ARCHIVE_OK);
+}
+
+int
+archive_read_disk_can_descend(struct archive *_a)
+{
+	struct archive_read_disk *a = (struct archive_read_disk *)_a;
+	struct tree *t = a->tree;
+
+	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
+	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
+	    "archive_read_disk_can_descend");
+
+	return (t->visit_type == TREE_REGULAR && t->descend);
+}
+
 /*
  * Called by the client to mark the directory just returned from
  * tree_next() as needing to be visited.
@@ -1028,14 +1241,12 @@ archive_read_disk_descend(struct archive *_a)
 	struct archive_read_disk *a = (struct archive_read_disk *)_a;
 	struct tree *t = a->tree;
 
-	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,
+	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
+	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
 	    "archive_read_disk_descend");
 
-	if (t->visit_type != TREE_REGULAR || !t->descend) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Ignored the request descending the current object");
-		return (ARCHIVE_WARN);
-	}
+	if (t->visit_type != TREE_REGULAR || !t->descend)
+		return (ARCHIVE_OK);
 
 	if (tree_current_is_physical_dir(t)) {
 		tree_push(t, t->basename, t->current_filesystem_id,
@@ -1079,8 +1290,12 @@ archive_read_disk_open_w(struct archive *_a, const wchar_t *pathname)
 	archive_string_init(&path);
 	if (archive_string_append_from_wcs(&path, pathname,
 	    wcslen(pathname)) != 0) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Can't convert a path to a char string");
+		if (errno == ENOMEM)
+			archive_set_error(&a->archive, ENOMEM,
+			    "Can't allocate memory");
+		else
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Can't convert a path to a char string");
 		a->archive.state = ARCHIVE_STATE_FATAL;
 		ret = ARCHIVE_FATAL;
 	} else
@@ -1151,15 +1366,17 @@ update_current_filesystem(struct archive_read_disk *a, int64_t dev)
 	fid = t->max_filesystem_id++;
 	if (t->max_filesystem_id > t->allocated_filesytem) {
 		size_t s;
+		void *p;
 
 		s = t->max_filesystem_id * 2;
-		t->filesystem_table = realloc(t->filesystem_table,
-		    s * sizeof(*t->filesystem_table));
-		if (t->filesystem_table == NULL) {
+		p = realloc(t->filesystem_table,
+		        s * sizeof(*t->filesystem_table));
+		if (p == NULL) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "Can't allocate tar data");
 			return (ARCHIVE_FATAL);
 		}
+		t->filesystem_table = (struct filesystem *)p;
 		t->allocated_filesytem = s;
 	}
 	t->current_filesystem_id = fid;
@@ -1268,13 +1485,14 @@ setup_current_filesystem(struct archive_read_disk *a)
 	t->current_filesystem->synthetic = -1;
 	t->current_filesystem->remote = -1;
 	if (tree_current_is_symblic_link_target(t)) {
-#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
+#if defined(HAVE_OPENAT)
 		/*
 		 * Get file system statistics on any directory
 		 * where current is.
 		 */
 		int fd = openat(tree_current_dir_fd(t),
-		    tree_current_access_path(t), O_RDONLY);
+		    tree_current_access_path(t), O_RDONLY | O_CLOEXEC);
+		__archive_ensure_cloexec_flag(fd);
 		if (fd < 0) {
 			archive_set_error(&a->archive, errno,
 			    "openat failed");
@@ -1285,6 +1503,10 @@ setup_current_filesystem(struct archive_read_disk *a)
 			xr = get_xfer_size(t, fd, NULL);
 		close(fd);
 #else
+		if (tree_enter_working_dir(t) != 0) {
+			archive_set_error(&a->archive, errno, "fchdir failed");
+			return (ARCHIVE_FAILED);
+		}
 		r = statfs(tree_current_access_path(t), &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, -1, tree_current_access_path(t));
@@ -1334,9 +1556,13 @@ setup_current_filesystem(struct archive_read_disk *a)
 	t->current_filesystem->name_max = sfs.f_namemax;
 #else
 	/* Mac OS X does not have f_namemax in struct statfs. */
-	if (tree_current_is_symblic_link_target(t))
+	if (tree_current_is_symblic_link_target(t)) {
+		if (tree_enter_working_dir(t) != 0) {
+			archive_set_error(&a->archive, errno, "fchdir failed");
+			return (ARCHIVE_FAILED);
+		}
 		nm = pathconf(tree_current_access_path(t), _PC_NAME_MAX);
-	else
+	} else
 		nm = fpathconf(tree_current_dir_fd(t), _PC_NAME_MAX);
 	if (nm == -1)
 		t->current_filesystem->name_max = NAME_MAX;
@@ -1360,6 +1586,10 @@ setup_current_filesystem(struct archive_read_disk *a)
 	int r, xr = 0;
 
 	t->current_filesystem->synthetic = -1;
+	if (tree_enter_working_dir(t) != 0) {
+		archive_set_error(&a->archive, errno, "fchdir failed");
+		return (ARCHIVE_FAILED);
+	}
 	if (tree_current_is_symblic_link_target(t)) {
 		r = statvfs(tree_current_access_path(t), &sfs);
 		if (r == 0)
@@ -1434,13 +1664,14 @@ setup_current_filesystem(struct archive_read_disk *a)
 	int r, vr = 0, xr = 0;
 
 	if (tree_current_is_symblic_link_target(t)) {
-#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
+#if defined(HAVE_OPENAT)
 		/*
 		 * Get file system statistics on any directory
 		 * where current is.
 		 */
 		int fd = openat(tree_current_dir_fd(t),
-		    tree_current_access_path(t), O_RDONLY);
+		    tree_current_access_path(t), O_RDONLY | O_CLOEXEC);
+		__archive_ensure_cloexec_flag(fd);
 		if (fd < 0) {
 			archive_set_error(&a->archive, errno,
 			    "openat failed");
@@ -1452,6 +1683,10 @@ setup_current_filesystem(struct archive_read_disk *a)
 			xr = get_xfer_size(t, fd, NULL);
 		close(fd);
 #else
+		if (tree_enter_working_dir(t) != 0) {
+			archive_set_error(&a->archive, errno, "fchdir failed");
+			return (ARCHIVE_FAILED);
+		}
 		vr = statvfs(tree_current_access_path(t), &svfs);
 		r = statfs(tree_current_access_path(t), &sfs);
 		if (r == 0)
@@ -1463,9 +1698,11 @@ setup_current_filesystem(struct archive_read_disk *a)
 		r = fstatfs(tree_current_dir_fd(t), &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
-#elif defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
-#error "Unexpected case. Please tell us about this error."
 #else
+		if (tree_enter_working_dir(t) != 0) {
+			archive_set_error(&a->archive, errno, "fchdir failed");
+			return (ARCHIVE_FAILED);
+		}
 		vr = statvfs(".", &svfs);
 		r = statfs(".", &sfs);
 		if (r == 0)
@@ -1536,13 +1773,14 @@ setup_current_filesystem(struct archive_read_disk *a)
 	t->current_filesystem->synthetic = -1;/* Not supported */
 	t->current_filesystem->remote = -1;/* Not supported */
 	if (tree_current_is_symblic_link_target(t)) {
-#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
+#if defined(HAVE_OPENAT)
 		/*
 		 * Get file system statistics on any directory
 		 * where current is.
 		 */
 		int fd = openat(tree_current_dir_fd(t),
-		    tree_current_access_path(t), O_RDONLY);
+		    tree_current_access_path(t), O_RDONLY | O_CLOEXEC);
+		__archive_ensure_cloexec_flag(fd);
 		if (fd < 0) {
 			archive_set_error(&a->archive, errno,
 			    "openat failed");
@@ -1553,6 +1791,10 @@ setup_current_filesystem(struct archive_read_disk *a)
 			xr = get_xfer_size(t, fd, NULL);
 		close(fd);
 #else
+		if (tree_enter_working_dir(t) != 0) {
+			archive_set_error(&a->archive, errno, "fchdir failed");
+			return (ARCHIVE_FAILED);
+		}
 		r = statvfs(tree_current_access_path(t), &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, -1, tree_current_access_path(t));
@@ -1562,9 +1804,11 @@ setup_current_filesystem(struct archive_read_disk *a)
 		r = fstatvfs(tree_current_dir_fd(t), &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
-#elif defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
-#error "Unexpected case. Please tell us about this error."
 #else
+		if (tree_enter_working_dir(t) != 0) {
+			archive_set_error(&a->archive, errno, "fchdir failed");
+			return (ARCHIVE_FAILED);
+		}
 		r = statvfs(".", &sfs);
 		if (r == 0)
 			xr = get_xfer_size(t, -1, ".");
@@ -1622,9 +1866,13 @@ setup_current_filesystem(struct archive_read_disk *a)
 #if defined(HAVE_READDIR_R)
 	/* Set maximum filename length. */
 #  if defined(_PC_NAME_MAX)
-	if (tree_current_is_symblic_link_target(t))
+	if (tree_current_is_symblic_link_target(t)) {
+		if (tree_enter_working_dir(t) != 0) {
+			archive_set_error(&a->archive, errno, "fchdir failed");
+			return (ARCHIVE_FAILED);
+		}
 		nm = pathconf(tree_current_access_path(t), _PC_NAME_MAX);
-	else
+	} else
 		nm = fpathconf(tree_current_dir_fd(t), _PC_NAME_MAX);
 	if (nm == -1)
 #  endif /* _PC_NAME_MAX */
@@ -1653,7 +1901,8 @@ static int
 close_and_restore_time(int fd, struct tree *t, struct restore_time *rt)
 {
 #ifndef HAVE_UTIMES
-	(void)a; /* UNUSED */
+	(void)t; /* UNUSED */
+	(void)rt; /* UNUSED */
 	return (close(fd));
 #else
 #if defined(HAVE_FUTIMENS) && !defined(__CYGWIN__)
@@ -1704,6 +1953,40 @@ close_and_restore_time(int fd, struct tree *t, struct restore_time *rt)
 	return (0);
 }
 
+static int
+open_on_current_dir(struct tree *t, const char *path, int flags)
+{
+#ifdef HAVE_OPENAT
+	return (openat(tree_current_dir_fd(t), path, flags));
+#else
+	if (tree_enter_working_dir(t) != 0)
+		return (-1);
+	return (open(path, flags));
+#endif
+}
+
+static int
+tree_dup(int fd)
+{
+	int new_fd;
+#ifdef F_DUPFD_CLOEXEC
+	static volatile int can_dupfd_cloexec = 1;
+
+	if (can_dupfd_cloexec) {
+		new_fd = fcntl(fd, F_DUPFD_CLOEXEC);
+		if (new_fd != -1)
+			return (new_fd);
+		/* Linux 2.6.18 - 2.6.23 declare F_DUPFD_CLOEXEC,
+		 * but it cannot be used. So we have to try dup(). */
+		/* We won't try F_DUPFD_CLOEXEC. */
+		can_dupfd_cloexec = 0;
+	}
+#endif /* F_DUPFD_CLOEXEC */
+	new_fd = dup(fd);
+	__archive_ensure_cloexec_flag(new_fd);
+	return (new_fd);
+}
+
 /*
  * Add a directory path to the current stack.
  */
@@ -1785,6 +2068,7 @@ static struct tree *
 tree_reopen(struct tree *t, const char *path, int restore_time)
 {
 	t->flags = (restore_time)?needsRestoreTimes:0;
+	t->flags |= onInitialDir;
 	t->visit_type = 0;
 	t->tree_errno = 0;
 	t->dirname_length = 0;
@@ -1797,25 +2081,30 @@ tree_reopen(struct tree *t, const char *path, int restore_time)
 	t->entry_fd = -1;
 	t->entry_eof = 0;
 	t->entry_remaining_bytes = 0;
+	t->initial_filesystem_id = -1;
 
 	/* First item is set up a lot like a symlink traversal. */
 	tree_push(t, path, 0, 0, 0, NULL);
 	t->stack->flags = needsFirstVisit;
 	t->maxOpenCount = t->openCount = 1;
-	t->initial_dir_fd = open(".", O_RDONLY);
-	t->working_dir_fd = dup(t->initial_dir_fd);
+	t->initial_dir_fd = open(".", O_RDONLY | O_CLOEXEC);
+	__archive_ensure_cloexec_flag(t->initial_dir_fd);
+	t->working_dir_fd = tree_dup(t->initial_dir_fd);
 	return (t);
 }
 
 static int
 tree_descent(struct tree *t)
 {
-	int r = 0;
+	int flag, new_fd, r = 0;
 
-#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
-	int new_fd;
 	t->dirname_length = archive_strlen(&t->path);
-	new_fd = openat(t->working_dir_fd, t->stack->name.s, O_RDONLY);
+	flag = O_RDONLY | O_CLOEXEC;
+#if defined(O_DIRECTORY)
+	flag |= O_DIRECTORY;
+#endif
+	new_fd = open_on_current_dir(t, t->stack->name.s, flag);
+	__archive_ensure_cloexec_flag(new_fd);
 	if (new_fd < 0) {
 		t->tree_errno = errno;
 		r = TREE_ERROR_DIR;
@@ -1829,30 +2118,10 @@ tree_descent(struct tree *t)
 				t->maxOpenCount = t->openCount;
 		} else
 			close(t->working_dir_fd);
+		/* Renew the current working directory. */
 		t->working_dir_fd = new_fd;
+		t->flags &= ~onWorkingDir;
 	}
-#else
-	/* If it is a link, set up fd for the ascent. */
-	if (t->stack->flags & isDirLink)
-		t->stack->symlink_parent_fd = t->working_dir_fd;
-	else {
-		close(t->working_dir_fd);
-		t->openCount--;
-	}
-	t->working_dir_fd = -1;
-	t->dirname_length = archive_strlen(&t->path);
-	if (chdir(t->stack->name.s) != 0)
-	{
-		t->tree_errno = errno;
-		r = TREE_ERROR_DIR;
-	} else {
-		t->depth++;
-		t->working_dir_fd = open(".", O_RDONLY);
-		t->openCount++;
-		if (t->openCount > t->maxOpenCount)
-			t->maxOpenCount = t->openCount;
-	}
-#endif
 	return (r);
 }
 
@@ -1863,37 +2132,23 @@ static int
 tree_ascend(struct tree *t)
 {
 	struct tree_entry *te;
-	int r = 0, prev_dir_fd;
+	int new_fd, r = 0, prev_dir_fd;
 
 	te = t->stack;
 	prev_dir_fd = t->working_dir_fd;
-#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
 	if (te->flags & isDirLink)
-		t->working_dir_fd = te->symlink_parent_fd;
+		new_fd = te->symlink_parent_fd;
 	else {
-		int new_fd = openat(t->working_dir_fd, "..", O_RDONLY);
-		if (new_fd < 0) {
-			t->tree_errno = errno;
-			r = TREE_ERROR_FATAL;
-		} else
-			t->working_dir_fd = new_fd;
+		new_fd = open_on_current_dir(t, "..", O_RDONLY | O_CLOEXEC);
+		__archive_ensure_cloexec_flag(new_fd);
 	}
-#else
-	if (te->flags & isDirLink) {
-		if (fchdir(te->symlink_parent_fd) != 0) {
-			t->tree_errno = errno;
-			r = TREE_ERROR_FATAL;
-		} else
-			t->working_dir_fd = te->symlink_parent_fd;
+	if (new_fd < 0) {
+		t->tree_errno = errno;
+		r = TREE_ERROR_FATAL;
 	} else {
-		if (chdir("..") != 0) {
-			t->tree_errno = errno;
-			r = TREE_ERROR_FATAL;
-		} else
-			t->working_dir_fd = open(".", O_RDONLY);
-	}
-#endif
-	if (r == 0) {
+		/* Renew the current working directory. */
+		t->working_dir_fd = new_fd;
+		t->flags &= ~onWorkingDir;
 		/* Current directory has been changed, we should
 		 * close an fd of previous working directory. */
 		close_and_restore_time(prev_dir_fd, t, &te->restore_time);
@@ -1914,10 +2169,12 @@ tree_enter_initial_dir(struct tree *t)
 {
 	int r = 0;
 
-	if (t->flags & onWorkingDir) {
+	if ((t->flags & onInitialDir) == 0) {
 		r = fchdir(t->initial_dir_fd);
-		if (r == 0)
+		if (r == 0) {
 			t->flags &= ~onWorkingDir;
+			t->flags |= onInitialDir;
+		}
 	}
 	return (r);
 }
@@ -1937,8 +2194,10 @@ tree_enter_working_dir(struct tree *t)
 	 */
 	if (t->depth > 0 && (t->flags & onWorkingDir) == 0) {
 		r = fchdir(t->working_dir_fd);
-		if (r == 0)
+		if (r == 0) {
+			t->flags &= ~onInitialDir;
 			t->flags |= onWorkingDir;
+		}
 	}
 	return (r);
 }
@@ -2045,10 +2304,16 @@ tree_dir_next_posix(struct tree *t)
 #endif
 
 #if defined(HAVE_FDOPENDIR)
-		if ((t->d = fdopendir(dup(t->working_dir_fd))) == NULL) {
-#else
-		if ((t->d = opendir(".")) == NULL) {
+		t->d = fdopendir(tree_dup(t->working_dir_fd));
+#else /* HAVE_FDOPENDIR */
+		if (tree_enter_working_dir(t) == 0) {
+			t->d = opendir(".");
+#if HAVE_DIRFD || defined(dirfd)
+			__archive_ensure_cloexec_flag(dirfd(t->d));
 #endif
+		}
+#endif /* HAVE_FDOPENDIR */
+		if (t->d == NULL) {
 			r = tree_ascend(t); /* Undo "chdir" */
 			tree_pop(t);
 			t->tree_errno = errno;
@@ -2075,11 +2340,21 @@ tree_dir_next_posix(struct tree *t)
 #endif /* HAVE_READDIR_R */
 	}
 	for (;;) {
+		errno = 0;
 #if defined(HAVE_READDIR_R)
 		r = readdir_r(t->d, t->dirent, &t->de);
+#ifdef _AIX
+		/* Note: According to the man page, return value 9 indicates
+		 * that the readdir_r was not successful and the error code
+		 * is set to the global errno variable. And then if the end
+		 * of directory entries was reached, the return value is 9
+		 * and the third parameter is set to NULL and errno is
+		 * unchanged. */
+		if (r == 9)
+			r = errno;
+#endif /* _AIX */
 		if (r != 0 || t->de == NULL) {
 #else
-		errno = 0;
 		t->de = readdir(t->d);
 		if (t->de == NULL) {
 			r = errno;
@@ -2118,6 +2393,8 @@ tree_current_stat(struct tree *t)
 		if (fstatat(tree_current_dir_fd(t),
 		    tree_current_access_path(t), &t->st, 0) != 0)
 #else
+		if (tree_enter_working_dir(t) != 0)
+			return NULL;
 		if (stat(tree_current_access_path(t), &t->st) != 0)
 #endif
 			return NULL;
@@ -2138,6 +2415,8 @@ tree_current_lstat(struct tree *t)
 		    tree_current_access_path(t), &t->lst,
 		    AT_SYMLINK_NOFOLLOW) != 0)
 #else
+		if (tree_enter_working_dir(t) != 0)
+			return NULL;
 		if (lstat(tree_current_access_path(t), &t->lst) != 0)
 #endif
 			return NULL;
@@ -2159,11 +2438,14 @@ tree_current_is_dir(struct tree *t)
 	 */
 	if (t->flags & hasLstat) {
 		/* If lstat() says it's a dir, it must be a dir. */
-		if (S_ISDIR(tree_current_lstat(t)->st_mode))
+		st = tree_current_lstat(t);
+		if (st == NULL)
+			return 0;
+		if (S_ISDIR(st->st_mode))
 			return 1;
 		/* Not a dir; might be a link to a dir. */
 		/* If it's not a link, then it's not a link to a dir. */
-		if (!S_ISLNK(tree_current_lstat(t)->st_mode))
+		if (!S_ISLNK(st->st_mode))
 			return 0;
 		/*
 		 * It's a link, but we don't know what it's a link to,
@@ -2193,9 +2475,13 @@ tree_current_is_physical_dir(struct tree *t)
 	 * If stat() says it isn't a dir, then it's not a dir.
 	 * If stat() data is cached, this check is free, so do it first.
 	 */
-	if ((t->flags & hasStat)
-	    && (!S_ISDIR(tree_current_stat(t)->st_mode)))
-		return 0;
+	if (t->flags & hasStat) {
+		st = tree_current_stat(t);
+		if (st == NULL)
+			return (0);
+		if (!S_ISDIR(st->st_mode))
+			return (0);
+	}
 
 	/*
 	 * Either stat() said it was a dir (in which case, we have
@@ -2221,7 +2507,8 @@ tree_target_is_same_as_parent(struct tree *t, const struct stat *st)
 	struct tree_entry *te;
 
 	for (te = t->current->parent; te != NULL; te = te->parent) {
-		if (te->dev == st->st_dev && te->ino == st->st_ino)
+		if (te->dev == (int64_t)st->st_dev &&
+		    te->ino == (int64_t)st->st_ino)
 			return (1);
 	}
 	return (0);
@@ -2238,7 +2525,8 @@ tree_current_is_symblic_link_target(struct tree *t)
 
 	lst = tree_current_lstat(t);
 	st = tree_current_stat(t);
-	return (st != NULL && st->st_dev == t->current_filesystem->dev &&
+	return (st != NULL && lst != NULL &&
+	    (int64_t)st->st_dev == t->current_filesystem->dev &&
 	    st->st_dev != lst->st_dev);
 }
 