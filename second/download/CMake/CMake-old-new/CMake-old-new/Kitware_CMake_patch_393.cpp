@@ -1,6 +1,6 @@
 /*-
  * Copyright (c) 2003-2009 Tim Kientzle
- * Copyright (c) 2010-2011 Michihiro NAKAJIMA
+ * Copyright (c) 2010-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -29,48 +29,13 @@ __FBSDID("$FreeBSD$");
 
 #if defined(_WIN32) && !defined(__CYGWIN__)
 
-#ifdef HAVE_SYS_PARAM_H
-#include <sys/param.h>
-#endif
-#ifdef HAVE_SYS_MOUNT_H
-#include <sys/mount.h>
-#endif
-#ifdef HAVE_SYS_STAT_H
-#include <sys/stat.h>
-#endif
-#ifdef HAVE_SYS_STATVFS_H
-#include <sys/statvfs.h>
-#endif
-#ifdef HAVE_SYS_VFS_H
-#include <sys/vfs.h>
-#endif
-#ifdef HAVE_LINUX_MAGIC_H
-#include <linux/magic.h>
-#endif
-#ifdef HAVE_DIRECT_H
-#include <direct.h>
-#endif
-#ifdef HAVE_DIRENT_H
-#include <dirent.h>
-#endif
 #ifdef HAVE_ERRNO_H
 #include <errno.h>
 #endif
-#ifdef HAVE_FCNTL_H
-#include <fcntl.h>
-#endif
 #ifdef HAVE_STDLIB_H
 #include <stdlib.h>
 #endif
-#ifdef HAVE_STRING_H
-#include <string.h>
-#endif
-#ifdef HAVE_UNISTD_H
-#include <unistd.h>
-#endif
-#if defined(HAVE_WINIOCTL_H) && !defined(__CYGWIN__)
 #include <winioctl.h>
-#endif
 
 #include "archive.h"
 #include "archive_string.h"
@@ -86,21 +51,6 @@ __FBSDID("$FreeBSD$");
 #define	IO_REPARSE_TAG_SYMLINK 0xA000000CL
 #endif
 
-static BOOL SetFilePointerEx_perso(HANDLE hFile,
-                             LARGE_INTEGER liDistanceToMove,
-                             PLARGE_INTEGER lpNewFilePointer,
-                             DWORD dwMoveMethod)
-{
-	LARGE_INTEGER li;
-	li.QuadPart = liDistanceToMove.QuadPart;
-	li.LowPart = SetFilePointer(
-	    hFile, li.LowPart, &li.HighPart, dwMoveMethod);
-	if(lpNewFilePointer) {
-		lpNewFilePointer->QuadPart = li.QuadPart;
-	}
-	return li.LowPart != -1 || GetLastError() == NO_ERROR;
-}
-
 /*-
  * This is a new directory-walking system that addresses a number
  * of problems I've had with fts(3).  In particular, it has no
@@ -120,11 +70,6 @@ static BOOL SetFilePointerEx_perso(HANDLE hFile,
  * indicating how to get back to the parent (via chdir("..") for a
  * regular dir or via fchdir(2) for a symlink).
  */
-/*
- * TODO:
- *    1) Loop checking.
- *    3) Arbitrary logical traversals by closing/reopening intermediate fds.
- */
 
 struct restore_time {
 	const wchar_t		*full_path;
@@ -153,6 +98,7 @@ struct filesystem {
 	int64_t		dev;
 	int		synthetic;
 	int		remote;
+	DWORD		bytesPerSector;
 };
 
 /* Definitions for tree_entry.flags bitmap. */
@@ -170,14 +116,18 @@ struct filesystem {
  * "first visit" is just returned to the client.
  */
 
+#define MAX_OVERLAPPED	8
+#define BUFFER_SIZE	(1024 * 8)
+#define DIRECT_IO	0/* Disabled */
+#define ASYNC_IO	1/* Enabled */
+
 /*
  * Local data for this package.
  */
 struct tree {
 	struct tree_entry	*stack;
 	struct tree_entry	*current;
 	HANDLE d;
-#define	INVALID_DIR_HANDLE INVALID_HANDLE_VALUE
 	WIN32_FIND_DATAW	_findData;
 	WIN32_FIND_DATAW	*findData;
 	int			 flags;
@@ -215,6 +165,7 @@ struct tree {
 	char			 symlink_mode;
 	struct filesystem	*current_filesystem;
 	struct filesystem	*filesystem_table;
+	int			 initial_filesystem_id;
 	int			 current_filesystem_id;
 	int			 max_filesystem_id;
 	int			 allocated_filesytem;
@@ -223,8 +174,24 @@ struct tree {
 	int			 entry_eof;
 	int64_t			 entry_remaining_bytes;
 	int64_t			 entry_total;
-	unsigned char		*entry_buff;
-	size_t			 entry_buff_size;
+
+	int			 ol_idx_doing;
+	int			 ol_idx_done;
+	int			 ol_num_doing;
+	int			 ol_num_done;
+	int64_t			 ol_remaining_bytes;
+	int64_t			 ol_total;
+	struct la_overlapped {
+		OVERLAPPED	 ol;
+		struct archive * _a;
+		unsigned char	*buff;
+		size_t		 buff_size;
+		int64_t		 offset;
+		size_t		 bytes_expected;
+		size_t		 bytes_transferred;
+	}			 ol[MAX_OVERLAPPED];
+	int			 direct_io;
+	int			 async_io;
 };
 
 #define bhfi_dev(bhfi)	((bhfi)->dwVolumeSerialNumber)
@@ -242,13 +209,6 @@ struct tree {
 static int
 tree_dir_next_windows(struct tree *t, const wchar_t *pattern);
 
-#ifdef HAVE_DIRENT_D_NAMLEN
-/* BSD extension; avoids need for a strlen() call. */
-#define	D_NAMELEN(dp)	(dp)->d_namlen
-#else
-#define	D_NAMELEN(dp)	(strlen((dp)->d_name))
-#endif
-
 /* Initiate/terminate a tree traversal. */
 static struct tree *tree_open(const wchar_t *, int, int);
 static struct tree *tree_reopen(struct tree *, const wchar_t *, int);
@@ -435,7 +395,8 @@ archive_read_disk_new(void)
 	a->archive.vtable = archive_read_disk_vtable();
 	a->lookup_uname = trivial_lookup_uname;
 	a->lookup_gname = trivial_lookup_gname;
-	a->entry_wd_fd = -1;
+	a->enable_copyfile = 1;
+	a->traverse_mount_points = 1;
 	return (&a->archive);
 }
 
@@ -536,6 +497,37 @@ archive_read_disk_set_atime_restored(struct archive *_a)
 	return (ARCHIVE_OK);
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
@@ -557,113 +549,197 @@ trivial_lookup_uname(void *private_data, int64_t uid)
 	return (NULL);
 }
 
+static int64_t
+align_num_per_sector(struct tree *t, int64_t size)
+{
+	int64_t surplus;
+
+	size += t->current_filesystem->bytesPerSector -1;
+	surplus = size % t->current_filesystem->bytesPerSector;
+	size -= surplus;
+	return (size);
+}
+
 static int
-_archive_read_data_block(struct archive *_a, const void **buff,
-    size_t *size, int64_t *offset)
+start_next_async_read(struct archive_read_disk *a, struct tree *t)
 {
-	struct archive_read_disk *a = (struct archive_read_disk *)_a;
-	struct tree *t = a->tree;
-	int r;
-	int64_t bytes;
-	size_t buffbytes;
+	struct la_overlapped *olp;
+	DWORD buffbytes, rbytes;
 
-	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,
-	    "archive_read_data_block");
+	if (t->ol_remaining_bytes == 0)
+		return (ARCHIVE_EOF);
 
-	if (t->entry_eof || t->entry_remaining_bytes <= 0) {
-		r = ARCHIVE_EOF;
-		goto abort_read_data;
-	}
+	olp = &(t->ol[t->ol_idx_doing]);
+	t->ol_idx_doing = (t->ol_idx_doing + 1) % MAX_OVERLAPPED;
 
 	/* Allocate read buffer. */
-	if (t->entry_buff == NULL) {
-		t->entry_buff = malloc(1024 * 64);
-		if (t->entry_buff == NULL) {
+	if (olp->buff == NULL) {
+		void *p;
+		size_t s = (size_t)align_num_per_sector(t, BUFFER_SIZE);
+		p = VirtualAlloc(NULL, s, MEM_COMMIT, PAGE_READWRITE);
+		if (p == NULL) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "Couldn't allocate memory");
-			r = ARCHIVE_FATAL;
 			a->archive.state = ARCHIVE_STATE_FATAL;
-			goto abort_read_data;
+			return (ARCHIVE_FATAL);
 		}
-		t->entry_buff_size = 1024 * 64;
-	}
+		olp->buff = p;
+		olp->buff_size = s;
+		olp->_a = &a->archive;
+		olp->ol.hEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
+		if (olp->ol.hEvent == NULL) {
+			la_dosmaperr(GetLastError());
+			archive_set_error(&a->archive, errno,
+			    "CreateEvent failed");
+			a->archive.state = ARCHIVE_STATE_FATAL;
+			return (ARCHIVE_FATAL);
+		}
+	} else
+		ResetEvent(olp->ol.hEvent);
 
-	buffbytes = t->entry_buff_size;
+	buffbytes = (DWORD)olp->buff_size;
 	if (buffbytes > t->current_sparse->length)
-		buffbytes = t->current_sparse->length;
+		buffbytes = (DWORD)t->current_sparse->length;
 
-	/*
-	 * Skip hole.
-	 */
-	if (t->current_sparse->offset > t->entry_total) {
-		LARGE_INTEGER distance;
-		distance.QuadPart = t->current_sparse->offset;
-		if (!SetFilePointerEx_perso(t->entry_fh, distance, NULL, FILE_BEGIN)) {
-			DWORD lasterr;
-
-			lasterr = GetLastError();
-			if (lasterr == ERROR_ACCESS_DENIED)
-				errno = EBADF;
-			else
-				la_dosmaperr(lasterr);
-			archive_set_error(&a->archive, errno, "Seek error");
-			r = ARCHIVE_FATAL;
-			a->archive.state = ARCHIVE_STATE_FATAL;
-			goto abort_read_data;
-		}
-		bytes = t->current_sparse->offset - t->entry_total;
-		t->entry_remaining_bytes -= bytes;
-		t->entry_total += bytes;
+	/* Skip hole. */
+	if (t->current_sparse->offset > t->ol_total) {
+		t->ol_remaining_bytes -=
+			t->current_sparse->offset - t->ol_total;
+	}
+
+	olp->offset = t->current_sparse->offset;
+	olp->ol.Offset = (DWORD)(olp->offset & 0xffffffff);
+	olp->ol.OffsetHigh = (DWORD)(olp->offset >> 32);
+
+	if (t->ol_remaining_bytes > buffbytes) {
+		olp->bytes_expected = buffbytes;
+		t->ol_remaining_bytes -= buffbytes;
+	} else {
+		olp->bytes_expected = (size_t)t->ol_remaining_bytes;
+		t->ol_remaining_bytes = 0;
 	}
-	if (buffbytes > 0) {
-		DWORD bytes_read;
-		if (!ReadFile(t->entry_fh, t->entry_buff,
-		    (uint32_t)buffbytes, &bytes_read, NULL)) {
-			DWORD lasterr;
+	olp->bytes_transferred = 0;
+	t->current_sparse->offset += buffbytes;
+	t->current_sparse->length -= buffbytes;
+	t->ol_total = t->current_sparse->offset;
+	if (t->current_sparse->length == 0 && t->ol_remaining_bytes > 0)
+		t->current_sparse++;
 
-			lasterr = GetLastError();
+	if (!ReadFile(t->entry_fh, olp->buff, buffbytes, &rbytes, &(olp->ol))) {
+		DWORD lasterr;
+
+		lasterr = GetLastError();
+		if (lasterr == ERROR_HANDLE_EOF) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Reading file truncated");
+			a->archive.state = ARCHIVE_STATE_FATAL;
+			return (ARCHIVE_FATAL);
+		} else if (lasterr != ERROR_IO_PENDING) {
 			if (lasterr == ERROR_NO_DATA)
 				errno = EAGAIN;
 			else if (lasterr == ERROR_ACCESS_DENIED)
 				errno = EBADF;
 			else
 				la_dosmaperr(lasterr);
 			archive_set_error(&a->archive, errno, "Read error");
-			r = ARCHIVE_FATAL;
 			a->archive.state = ARCHIVE_STATE_FATAL;
-			goto abort_read_data;
+			return (ARCHIVE_FATAL);
 		}
-		bytes = bytes_read;
 	} else
-		bytes = 0;
-	if (bytes == 0) {
-		/* Get EOF */
-		t->entry_eof = 1;
+		olp->bytes_transferred = rbytes;
+	t->ol_num_doing++;
+
+	return (t->ol_remaining_bytes == 0)? ARCHIVE_EOF: ARCHIVE_OK;
+}
+
+static void
+cancel_async(struct tree *t)
+{
+	if (t->ol_num_doing != t->ol_num_done) {
+		CancelIo(t->entry_fh);
+		t->ol_num_doing = t->ol_num_done = 0;
+	}
+}
+
+static int
+_archive_read_data_block(struct archive *_a, const void **buff,
+    size_t *size, int64_t *offset)
+{
+	struct archive_read_disk *a = (struct archive_read_disk *)_a;
+	struct tree *t = a->tree;
+	struct la_overlapped *olp;
+	DWORD bytes_transferred;
+	int r = ARCHIVE_FATAL;
+
+	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC, ARCHIVE_STATE_DATA,
+	    "archive_read_data_block");
+
+	if (t->entry_eof || t->entry_remaining_bytes <= 0) {
 		r = ARCHIVE_EOF;
 		goto abort_read_data;
 	}
-	*buff = t->entry_buff;
-	*size = bytes;
-	*offset = t->entry_total;
-	t->entry_total += bytes;
-	t->entry_remaining_bytes -= bytes;
+
+	/*
+	 * Make a request to read the file in asynchronous.
+	 */
+	if (t->ol_num_doing == 0) {
+		do {
+			r = start_next_async_read(a, t);
+			if (r == ARCHIVE_FATAL)
+				goto abort_read_data;
+			if (!t->async_io)
+				break;
+		} while (r == ARCHIVE_OK && t->ol_num_doing < MAX_OVERLAPPED);
+	} else {
+		if (start_next_async_read(a, t) == ARCHIVE_FATAL)
+			goto abort_read_data;
+	}
+
+	olp = &(t->ol[t->ol_idx_done]);
+	t->ol_idx_done = (t->ol_idx_done + 1) % MAX_OVERLAPPED;
+	if (olp->bytes_transferred)
+		bytes_transferred = (DWORD)olp->bytes_transferred;
+	else if (!GetOverlappedResult(t->entry_fh, &(olp->ol),
+	    &bytes_transferred, TRUE)) {
+		la_dosmaperr(GetLastError());
+		archive_set_error(&a->archive, errno,
+		    "GetOverlappedResult failed");
+		a->archive.state = ARCHIVE_STATE_FATAL;
+		r = ARCHIVE_FATAL;
+		goto abort_read_data;
+	}
+	t->ol_num_done++;
+
+	if (bytes_transferred == 0 ||
+	    olp->bytes_expected != bytes_transferred) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Reading file truncated");
+		a->archive.state = ARCHIVE_STATE_FATAL;
+		r = ARCHIVE_FATAL;
+		goto abort_read_data;
+	}
+
+	*buff = olp->buff;
+	*size = bytes_transferred;
+	*offset = olp->offset;
+	if (olp->offset > t->entry_total)
+		t->entry_remaining_bytes -= olp->offset - t->entry_total;
+	t->entry_total = olp->offset + *size;
+	t->entry_remaining_bytes -= *size;
 	if (t->entry_remaining_bytes == 0) {
 		/* Close the current file descriptor */
 		close_and_restore_time(t->entry_fh, t, &t->restore_time);
 		t->entry_fh = INVALID_HANDLE_VALUE;
 		t->entry_eof = 1;
 	}
-	t->current_sparse->offset += bytes;
-	t->current_sparse->length -= bytes;
-	if (t->current_sparse->length == 0 && !t->entry_eof)
-		t->current_sparse++;
 	return (ARCHIVE_OK);
 
 abort_read_data:
 	*buff = NULL;
 	*size = 0;
 	*offset = t->entry_total;
 	if (t->entry_fh != INVALID_HANDLE_VALUE) {
+		cancel_async(t);
 		/* Close the current file descriptor */
 		close_and_restore_time(t->entry_fh, t, &t->restore_time);
 		t->entry_fh = INVALID_HANDLE_VALUE;
@@ -672,26 +748,17 @@ _archive_read_data_block(struct archive *_a, const void **buff,
 }
 
 static int
-_archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
+next_entry(struct archive_read_disk *a, struct tree *t,
+    struct archive_entry *entry)
 {
-	struct archive_read_disk *a = (struct archive_read_disk *)_a;
-	struct tree *t;
 	const BY_HANDLE_FILE_INFORMATION *st;
 	const BY_HANDLE_FILE_INFORMATION *lst;
 	const char*name;
 	int descend, r;
 
-	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
-	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
-	    "archive_read_next_header2");
-
-	t = a->tree;
-	if (t->entry_fh != INVALID_HANDLE_VALUE) {
-		close_and_restore_time(t->entry_fh, t, &t->restore_time);
-		t->entry_fh = INVALID_HANDLE_VALUE;
-	}
 	st = NULL;
 	lst = NULL;
+	t->descend = 0;
 	do {
 		switch (tree_next(t)) {
 		case TREE_ERROR_FATAL:
@@ -701,7 +768,7 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 			a->archive.state = ARCHIVE_STATE_FATAL;
 			return (ARCHIVE_FATAL);
 		case TREE_ERROR_DIR:
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			archive_set_error(&a->archive, t->tree_errno,
 			    "%ls: Couldn't visit directory",
 			    tree_current_path(t));
 			return (ARCHIVE_FAILED);
@@ -713,7 +780,7 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		case TREE_REGULAR:
 			lst = tree_current_lstat(t);
 			if (lst == NULL) {
-				archive_set_error(&a->archive, errno,
+				archive_set_error(&a->archive, t->tree_errno,
 				    "%ls: Cannot stat",
 				    tree_current_path(t));
 				return (ARCHIVE_FAILED);
@@ -722,6 +789,26 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		}	
 	} while (lst == NULL);
 
+	archive_entry_copy_pathname_w(entry, tree_current_path(t));
+
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
@@ -759,31 +846,90 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		a->archive.state = ARCHIVE_STATE_FATAL;
 		return (ARCHIVE_FATAL);
 	}
+	if (t->initial_filesystem_id == -1)
+		t->initial_filesystem_id = t->current_filesystem_id;
+	if (!a->traverse_mount_points) {
+		if (t->initial_filesystem_id != t->current_filesystem_id)
+			return (ARCHIVE_RETRY);
+	}
 	t->descend = descend;
 
-	archive_entry_copy_pathname_w(entry, tree_current_path(t));
-	archive_entry_copy_sourcepath_w(entry, tree_current_access_path(t));
 	tree_archive_entry_copy_bhfi(entry, t, st);
 
-	/* Save the times to be restored. */
+	/* Save the times to be restored. This must be in before
+	 * calling archive_read_disk_descend() or any chance of it,
+	 * especially, invokng a callback. */
 	t->restore_time.lastWriteTime = st->ftLastWriteTime;
 	t->restore_time.lastAccessTime = st->ftLastAccessTime;
 	t->restore_time.filetype = archive_entry_filetype(entry);
 
+	/*
+	 * Perform time matching.
+	 */
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
+
 	/* Lookup uname/gname */
-	name = archive_read_disk_uname(_a, archive_entry_uid(entry));
+	name = archive_read_disk_uname(&(a->archive), archive_entry_uid(entry));
 	if (name != NULL)
 		archive_entry_copy_uname(entry, name);
-	name = archive_read_disk_gname(_a, archive_entry_gid(entry));
+	name = archive_read_disk_gname(&(a->archive), archive_entry_gid(entry));
 	if (name != NULL)
 		archive_entry_copy_gname(entry, name);
 
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
+
+	archive_entry_copy_sourcepath_w(entry, tree_current_access_path(t));
+
 	r = ARCHIVE_OK;
 	if (archive_entry_filetype(entry) == AE_IFREG &&
 	    archive_entry_size(entry) > 0) {
+		DWORD flags = FILE_FLAG_BACKUP_SEMANTICS;
+		if (t->async_io)
+			flags |= FILE_FLAG_OVERLAPPED;
+		if (t->direct_io)
+			flags |= FILE_FLAG_NO_BUFFERING;
+		else
+			flags |= FILE_FLAG_SEQUENTIAL_SCAN;
 		t->entry_fh = CreateFileW(tree_current_access_path(t),
-		    GENERIC_READ, 0, NULL, OPEN_EXISTING,
-		    FILE_FLAG_SEQUENTIAL_SCAN, NULL);
+		    GENERIC_READ, 0, NULL, OPEN_EXISTING, flags, NULL);
 		if (t->entry_fh == INVALID_HANDLE_VALUE) {
 			archive_set_error(&a->archive, errno,
 			    "Couldn't open %ls", tree_current_path(a->tree));
@@ -795,6 +941,29 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 		    (st->dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE) != 0)
 			r = setup_sparse_from_disk(a, entry, t->entry_fh);
 	}
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
+	if (t->entry_fh != INVALID_HANDLE_VALUE) {
+		cancel_async(t);
+		close_and_restore_time(t->entry_fh, t, &t->restore_time);
+		t->entry_fh = INVALID_HANDLE_VALUE;
+	}
+
+	while ((r = next_entry(a, t, entry)) == ARCHIVE_RETRY)
+		archive_entry_clear(entry);
 
 	/*
 	 * EOF and FATAL are persistent at this layer.  By
@@ -818,6 +987,10 @@ _archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
 			t->entry_remaining_bytes = 0;
 			t->entry_eof = 1;
 		}
+		t->ol_idx_doing = t->ol_idx_done = 0;
+		t->ol_num_doing = t->ol_num_done = 0;
+		t->ol_remaining_bytes = t->entry_remaining_bytes;
+		t->ol_total = 0;
 		a->archive.state = ARCHIVE_STATE_DATA;
 		break;
 	case ARCHIVE_RETRY:
@@ -834,7 +1007,7 @@ static int
 setup_sparse(struct archive_read_disk *a, struct archive_entry *entry)
 {
 	struct tree *t = a->tree;
-	int64_t length, offset;
+	int64_t aligned, length, offset;
 	int i;
 
 	t->sparse_count = archive_entry_sparse_reset(entry);
@@ -851,23 +1024,101 @@ setup_sparse(struct archive_read_disk *a, struct archive_entry *entry)
 			return (ARCHIVE_FATAL);
 		}
 	}
+	/*
+	 * Get sparse list and make sure those offsets and lengths are
+	 * aligned by a sector size.
+	 */
 	for (i = 0; i < t->sparse_count; i++) {
 		archive_entry_sparse_next(entry, &offset, &length);
-		t->sparse_list[i].offset = offset;
-		t->sparse_list[i].length = length;
+		aligned = align_num_per_sector(t, offset);
+		if (aligned != offset) {
+			aligned -= t->current_filesystem->bytesPerSector;
+			length += offset - aligned;
+		}
+		t->sparse_list[i].offset = aligned;
+		aligned = align_num_per_sector(t, length);
+		t->sparse_list[i].length = aligned;
 	}
+
+	aligned = align_num_per_sector(t, archive_entry_size(entry));
 	if (i == 0) {
 		t->sparse_list[i].offset = 0;
-		t->sparse_list[i].length = archive_entry_size(entry);
+		t->sparse_list[i].length = aligned;
 	} else {
-		t->sparse_list[i].offset = archive_entry_size(entry);
+		int j, last = i;
+
+		t->sparse_list[i].offset = aligned;
 		t->sparse_list[i].length = 0;
+		for (i = 0; i < last; i++) {
+			if ((t->sparse_list[i].offset +
+			       t->sparse_list[i].length) <= 
+					t->sparse_list[i+1].offset)
+				continue;
+			/*
+			 * Now sparse_list[i+1] is overlapped by sparse_list[i].
+			 * Merge those two.
+			 */
+			length = t->sparse_list[i+1].offset -
+					t->sparse_list[i].offset;
+			t->sparse_list[i+1].offset = t->sparse_list[i].offset;
+			t->sparse_list[i+1].length += length;
+			/* Remove sparse_list[i]. */
+			for (j = i; j < last; j++) {
+				t->sparse_list[j].offset =
+				    t->sparse_list[j+1].offset;
+				t->sparse_list[j].length =
+				    t->sparse_list[j+1].length;
+			}
+			last--;
+		}
 	}
 	t->current_sparse = t->sparse_list;
 
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
@@ -878,14 +1129,12 @@ archive_read_disk_descend(struct archive *_a)
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
 		tree_push(t, t->basename, t->full_path.s,
@@ -920,8 +1169,12 @@ archive_read_disk_open(struct archive *_a, const char *pathname)
 	archive_string_init(&wpath);
 	if (archive_wstring_append_from_mbs(&wpath, pathname,
 	    strlen(pathname)) != 0) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Can't convert a path to a wchar_t string");
+		if (errno == ENOMEM)
+			archive_set_error(&a->archive, ENOMEM,
+			    "Can't allocate memory");
+		else
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Can't convert a path to a wchar_t string");
 		a->archive.state = ARCHIVE_STATE_FATAL;
 		ret = ARCHIVE_FATAL;
 	} else
@@ -955,7 +1208,7 @@ _archive_read_disk_open_w(struct archive *_a, const wchar_t *pathname)
 		a->tree = tree_open(pathname, a->symlink_mode, a->restore_time);
 	if (a->tree == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
-		    "Can't allocate direcotry traversal data");
+		    "Can't allocate directory traversal data");
 		a->archive.state = ARCHIVE_STATE_FATAL;
 		return (ARCHIVE_FATAL);
 	}
@@ -1004,16 +1257,18 @@ update_current_filesystem(struct archive_read_disk *a, int64_t dev)
 	fid = t->max_filesystem_id++;
 	if (t->max_filesystem_id > t->allocated_filesytem) {
 		size_t s;
+		void *p;
 
 		s = t->max_filesystem_id * 2;
-		t->filesystem_table = realloc(t->filesystem_table,
-		    s * sizeof(*t->filesystem_table));
-		if (t->filesystem_table == NULL) {
+		p = realloc(t->filesystem_table,
+			s * sizeof(*t->filesystem_table));
+		if (p == NULL) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "Can't allocate tar data");
 			return (ARCHIVE_FATAL);
 		}
-		t->allocated_filesytem = s;
+		t->filesystem_table = (struct filesystem *)p;
+		t->allocated_filesytem = (int)s;
 	}
 	t->current_filesystem_id = fid;
 	t->current_filesystem = &(t->filesystem_table[fid]);
@@ -1091,6 +1346,7 @@ setup_current_filesystem(struct archive_read_disk *a)
 	if (!GetVolumePathNameW(path, vol, sizeof(vol)/sizeof(vol[0]))) {
 		free(path);
 		t->current_filesystem->remote = -1;
+		t->current_filesystem->bytesPerSector = 0;
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                         "GetVolumePathName failed: %d", (int)GetLastError());
 		return (ARCHIVE_FAILED);
@@ -1109,6 +1365,14 @@ setup_current_filesystem(struct archive_read_disk *a)
 		break;
 	}
 
+	if (!GetDiskFreeSpaceW(vol, NULL,
+	    &(t->current_filesystem->bytesPerSector), NULL, NULL)) {
+		t->current_filesystem->bytesPerSector = 0;
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+                        "GetDiskFreeSpace failed: %d", (int)GetLastError());
+		return (ARCHIVE_FAILED);
+	}
+
 	return (ARCHIVE_OK);
 }
 
@@ -1249,13 +1513,14 @@ tree_reopen(struct tree *t, const wchar_t *path, int restore_time)
 	t->depth = 0;
 	t->descend = 0;
 	t->current = NULL;
-	t->d = INVALID_DIR_HANDLE;
+	t->d = INVALID_HANDLE_VALUE;
 	t->symlink_mode = t->initial_symlink_mode;
 	archive_string_empty(&(t->full_path));
 	archive_string_empty(&t->path);
 	t->entry_fh = INVALID_HANDLE_VALUE;
 	t->entry_eof = 0;
 	t->entry_remaining_bytes = 0;
+	t->initial_filesystem_id = -1;
 
 	/* Get wchar_t strings from char strings. */
 	archive_string_init(&ws);
@@ -1277,8 +1542,12 @@ tree_reopen(struct tree *t, const wchar_t *path, int restore_time)
 
 	/* First item is set up a lot like a symlink traversal. */
 	/* printf("Looking for wildcard in %s\n", path); */
-	/* TODO: wildcard detection here screws up on \\?\c:\ UNC names */
-	if (wcschr(base, L'*') || wcschr(base, L'?')) {
+	if ((base[0] == L'/' && base[1] == L'/' &&
+	     base[2] == L'?' && base[3] == L'/' &&
+	     (wcschr(base+4, L'*') || wcschr(base+4, L'?'))) ||
+	    (!(base[0] == L'/' && base[1] == L'/' &&
+	       base[2] == L'?' && base[3] == L'/') &&
+	       (wcschr(base, L'*') || wcschr(base, L'?')))) {
 		// It has a wildcard in it...
 		// Separate the last element.
 		p = wcsrchr(base, L'/');
@@ -1298,6 +1567,32 @@ tree_reopen(struct tree *t, const wchar_t *path, int restore_time)
 	tree_push(t, base, t->full_path.s, 0, 0, 0, NULL);
 	archive_wstring_free(&ws);
 	t->stack->flags = needsFirstVisit;
+	/*
+	 * Debug flag for Direct IO(No buffering) or Async IO.
+	 * Those dependant on environment variable switches
+	 * will be removed until next release.
+	 */
+	{
+		const char *e;
+		if ((e = getenv("LIBARCHIVE_DIRECT_IO")) != NULL) {
+			if (e[0] == '0')
+				t->direct_io = 0;
+			else
+				t->direct_io = 1;
+			fprintf(stderr, "LIBARCHIVE_DIRECT_IO=%s\n",
+				(t->direct_io)?"Enabled":"Disabled");
+		} else
+			t->direct_io = DIRECT_IO;
+		if ((e = getenv("LIBARCHIVE_ASYNC_IO")) != NULL) {
+			if (e[0] == '0')
+				t->async_io = 0;
+			else
+				t->async_io = 1;
+			fprintf(stderr, "LIBARCHIVE_ASYNC_IO=%s\n",
+			    (t->async_io)?"Enabled":"Disabled");
+		} else
+			t->async_io = ASYNC_IO;
+	}
 	return (t);
 failed:
 	archive_wstring_free(&ws);
@@ -1324,7 +1619,7 @@ tree_ascend(struct tree *t)
 
 	te = t->stack;
 	t->depth--;
-	close_and_restore_time(INVALID_DIR_HANDLE, t, &te->restore_time);
+	close_and_restore_time(INVALID_HANDLE_VALUE, t, &te->restore_time);
 	return (0);
 }
 
@@ -1364,7 +1659,7 @@ tree_next(struct tree *t)
 
 	while (t->stack != NULL) {
 		/* If there's an open dir, get the next entry from there. */
-		if (t->d != INVALID_DIR_HANDLE) {
+		if (t->d != INVALID_HANDLE_VALUE) {
 			r = tree_dir_next_windows(t, NULL);
 			if (r == 0)
 				continue;
@@ -1374,14 +1669,17 @@ tree_next(struct tree *t)
 		if (t->stack->flags & needsFirstVisit) {
 			wchar_t *d = t->stack->name.s;
 			t->stack->flags &= ~needsFirstVisit;
-			if (wcschr(d, L'*') || wcschr(d, L'?')) {
+			if (!(d[0] == L'/' && d[1] == L'/' &&
+			      d[2] == L'?' && d[3] == L'/') &&
+			    (wcschr(d, L'*') || wcschr(d, L'?'))) {
 				r = tree_dir_next_windows(t, d);
 				if (r == 0)
 					continue;
 				return (r);
 			} else {
 				HANDLE h = FindFirstFileW(d, &t->_findData);
-				if (h == INVALID_DIR_HANDLE) {
+				if (h == INVALID_HANDLE_VALUE) {
+					la_dosmaperr(GetLastError());
 					t->tree_errno = errno;
 					t->visit_type = TREE_ERROR_DIR;
 					return (t->visit_type);
@@ -1452,18 +1750,19 @@ tree_dir_next_windows(struct tree *t, const wchar_t *pattern)
 			archive_wstrcat(&pt, pattern);
 			t->d = FindFirstFileW(pt.s, &t->_findData);
 			archive_wstring_free(&pt);
-			if (t->d == INVALID_DIR_HANDLE) {
+			if (t->d == INVALID_HANDLE_VALUE) {
+				la_dosmaperr(GetLastError());
+				t->tree_errno = errno;
 				r = tree_ascend(t); /* Undo "chdir" */
 				tree_pop(t);
-				t->tree_errno = errno;
 				t->visit_type = r != 0 ? r : TREE_ERROR_DIR;
 				return (t->visit_type);
 			}
 			t->findData = &t->_findData;
 			pattern = NULL;
 		} else if (!FindNextFileW(t->d, &t->_findData)) {
 			FindClose(t->d);
-			t->d = INVALID_DIR_HANDLE;
+			t->d = INVALID_HANDLE_VALUE;
 			t->findData = NULL;
 			return (0);
 		}
@@ -1482,7 +1781,7 @@ tree_dir_next_windows(struct tree *t, const wchar_t *pattern)
 
 #define EPOC_TIME ARCHIVE_LITERAL_ULL(116444736000000000)
 static void
-fileTimeToUtc(const FILETIME *filetime, time_t *time, long *ns)
+fileTimeToUtc(const FILETIME *filetime, time_t *t, long *ns)
 {
 	ULARGE_INTEGER utc;
 
@@ -1491,11 +1790,11 @@ fileTimeToUtc(const FILETIME *filetime, time_t *time, long *ns)
 	if (utc.QuadPart >= EPOC_TIME) {
 		utc.QuadPart -= EPOC_TIME;
 		/* milli seconds base */
-		*time = (time_t)(utc.QuadPart / 10000000);
+		*t = (time_t)(utc.QuadPart / 10000000);
 		/* nano seconds base */
 		*ns = (long)(utc.QuadPart % 10000000) * 100;
 	} else {
-		*time = 0;
+		*t = 0;
 		*ns = 0;
 	}
 }
@@ -1589,8 +1888,11 @@ tree_current_file_information(struct tree *t, BY_HANDLE_FILE_INFORMATION *st,
 		flag |= FILE_FLAG_OPEN_REPARSE_POINT;
 	h = CreateFileW(tree_current_access_path(t), 0, 0, NULL,
 	    OPEN_EXISTING, flag, NULL);
-	if (h == INVALID_HANDLE_VALUE)
+	if (h == INVALID_HANDLE_VALUE) {
+		la_dosmaperr(GetLastError());
+		t->tree_errno = errno;
 		return (0);
+	}
 	r = GetFileInformationByHandle(h, st);
 	CloseHandle(h);
 	return (r);
@@ -1709,13 +2011,14 @@ tree_close(struct tree *t)
 	if (t == NULL)
 		return;
 	if (t->entry_fh != INVALID_HANDLE_VALUE) {
+		cancel_async(t);
 		close_and_restore_time(t->entry_fh, t, &t->restore_time);
 		t->entry_fh = INVALID_HANDLE_VALUE;
 	}
 	/* Close the handle of FindFirstFileW */
-	if (t->d != INVALID_DIR_HANDLE) {
+	if (t->d != INVALID_HANDLE_VALUE) {
 		FindClose(t->d);
-		t->d = INVALID_DIR_HANDLE;
+		t->d = INVALID_HANDLE_VALUE;
 		t->findData = NULL;
 	}
 	/* Release anything remaining in the stack. */
@@ -1729,13 +2032,19 @@ tree_close(struct tree *t)
 static void
 tree_free(struct tree *t)
 {
+	int i;
+
 	if (t == NULL)
 		return;
 	archive_wstring_free(&t->path);
 	archive_wstring_free(&t->full_path);
 	free(t->sparse_list);
 	free(t->filesystem_table);
-	free(t->entry_buff);
+	for (i = 0; i < MAX_OVERLAPPED; i++) {
+		if (t->ol[i].buff)
+			VirtualFree(t->ol[i].buff, 0, MEM_RELEASE);
+		CloseHandle(t->ol[i].ol.hEvent);
+	}
 	free(t);
 }
 
@@ -1775,7 +2084,8 @@ archive_read_disk_entry_from_file(struct archive *_a,
 			h = (HANDLE)_get_osfhandle(fd);
 			r = GetFileInformationByHandle(h, &bhfi);
 			if (r == 0) {
-				archive_set_error(&a->archive, GetLastError(),
+				la_dosmaperr(GetLastError());
+				archive_set_error(&a->archive, errno,
 				    "Can't GetFileInformationByHandle");
 				return (ARCHIVE_FAILED);
 			}
@@ -1785,8 +2095,9 @@ archive_read_disk_entry_from_file(struct archive *_a,
 			DWORD flag, desiredAccess;
 	
 			h = FindFirstFileW(path, &findData);
-			if (h == INVALID_DIR_HANDLE) {
-				archive_set_error(&a->archive, GetLastError(),
+			if (h == INVALID_HANDLE_VALUE) {
+				la_dosmaperr(GetLastError());
+				archive_set_error(&a->archive, errno,
 				    "Can't FindFirstFileW");
 				return (ARCHIVE_FAILED);
 			}
@@ -1807,15 +2118,15 @@ archive_read_disk_entry_from_file(struct archive *_a,
 			h = CreateFileW(path, desiredAccess, 0, NULL,
 			    OPEN_EXISTING, flag, NULL);
 			if (h == INVALID_HANDLE_VALUE) {
-				archive_set_error(&a->archive,
-				    GetLastError(),
+				la_dosmaperr(GetLastError());
+				archive_set_error(&a->archive, errno,
 				    "Can't CreateFileW");
 				return (ARCHIVE_FAILED);
 			}
 			r = GetFileInformationByHandle(h, &bhfi);
 			if (r == 0) {
-				archive_set_error(&a->archive,
-				    GetLastError(),
+				la_dosmaperr(GetLastError());
+				archive_set_error(&a->archive, errno,
 				    "Can't GetFileInformationByHandle");
 				CloseHandle(h);
 				return (ARCHIVE_FAILED);
@@ -1825,7 +2136,7 @@ archive_read_disk_entry_from_file(struct archive *_a,
 		fileAttributes = bhfi.dwFileAttributes;
 	} else {
 		archive_entry_copy_stat(entry, st);
-		h = INVALID_DIR_HANDLE;
+		h = INVALID_HANDLE_VALUE;
 	}
 
 	/* Lookup uname/gname */
@@ -1854,14 +2165,16 @@ archive_read_disk_entry_from_file(struct archive *_a,
 			h = CreateFileW(path, GENERIC_READ, 0, NULL,
 			    OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
 			if (h == INVALID_HANDLE_VALUE) {
-				archive_set_error(&a->archive, GetLastError(),
+				la_dosmaperr(GetLastError());
+				archive_set_error(&a->archive, errno,
 				    "Can't CreateFileW");
 				return (ARCHIVE_FAILED);
 			}
 		}
 		r = GetFileInformationByHandle(h, &bhfi);
 		if (r == 0) {
-			archive_set_error(&a->archive, GetLastError(),
+			la_dosmaperr(GetLastError());
+			archive_set_error(&a->archive, errno,
 			    "Can't GetFileInformationByHandle");
 			if (h != INVALID_HANDLE_VALUE && fd < 0)
 				CloseHandle(h);
@@ -1909,7 +2222,7 @@ setup_sparse_from_disk(struct archive_read_disk *a,
 	outranges_size = 2048;
 	outranges = (FILE_ALLOCATED_RANGE_BUFFER *)malloc(outranges_size);
 	if (outranges == NULL) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		archive_set_error(&a->archive, ENOMEM,
 			"Couldn't allocate memory");
 		exit_sts = ARCHIVE_FATAL;
 		goto exit_setup_sparse;
@@ -1923,15 +2236,14 @@ setup_sparse_from_disk(struct archive_read_disk *a,
 			ret = DeviceIoControl(handle,
 			    FSCTL_QUERY_ALLOCATED_RANGES,
 			    &range, sizeof(range), outranges,
-			    outranges_size, &retbytes, NULL);
+			    (DWORD)outranges_size, &retbytes, NULL);
 			if (ret == 0 && GetLastError() == ERROR_MORE_DATA) {
 				free(outranges);
 				outranges_size *= 2;
 				outranges = (FILE_ALLOCATED_RANGE_BUFFER *)
 				    malloc(outranges_size);
 				if (outranges == NULL) {
-					archive_set_error(&a->archive,
-					    ARCHIVE_ERRNO_MISC,
+					archive_set_error(&a->archive, ENOMEM,
 					    "Couldn't allocate memory");
 					exit_sts = ARCHIVE_FATAL;
 					goto exit_setup_sparse;
@@ -1968,7 +2280,8 @@ setup_sparse_from_disk(struct archive_read_disk *a,
 			}
 			break;
 		} else {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			la_dosmaperr(GetLastError());
+			archive_set_error(&a->archive, errno,
 			    "DeviceIoControl Failed: %lu", GetLastError());
 			exit_sts = ARCHIVE_FAILED;
 			goto exit_setup_sparse;