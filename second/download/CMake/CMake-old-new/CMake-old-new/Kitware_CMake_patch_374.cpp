@@ -60,11 +60,15 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_open_filename.c 201093 2009
 #endif
 
 #include "archive.h"
+#include "archive_private.h"
 #include "archive_string.h"
 
 #ifndef O_BINARY
 #define O_BINARY 0
 #endif
+#ifndef O_CLOEXEC
+#define O_CLOEXEC	0
+#endif
 
 struct read_file_data {
 	int	 fd;
@@ -79,9 +83,10 @@ struct read_file_data {
 	} filename; /* Must be last! */
 };
 
+static int	file_open(struct archive *, void *);
 static int	file_close(struct archive *, void *);
-static int	file_open_filename(struct archive *, enum fnt_e, const void *,
-		    size_t);
+static int file_close2(struct archive *, void *);
+static int file_switch(struct archive *, void *, void *);
 static ssize_t	file_read(struct archive *, void *, const void **buff);
 static int64_t	file_seek(struct archive *, void *, int64_t request, int);
 static int64_t	file_skip(struct archive *, void *, int64_t request);
@@ -98,58 +103,120 @@ int
 archive_read_open_filename(struct archive *a, const char *filename,
     size_t block_size)
 {
-	enum fnt_e filename_type;
+	const char *filenames[2] = { filename, NULL };
+	return archive_read_open_filenames(a, filenames, block_size);
+}
+
+int
+archive_read_open_filenames(struct archive *a, const char **filenames,
+    size_t block_size)
+{
+	struct read_file_data *mine;
+	const char *filename = NULL;
+	if (filenames)
+		filename = *(filenames++);
+
+	archive_clear_error(a);
+	do
+	{
+		if (filename == NULL)
+			filename = "";
+		mine = (struct read_file_data *)calloc(1,
+			sizeof(*mine) + strlen(filename));
+		if (mine == NULL)
+			goto no_memory;
+		strcpy(mine->filename.m, filename);
+		mine->block_size = block_size;
+		mine->fd = -1;
+		mine->buffer = NULL;
+		mine->st_mode = mine->use_lseek = 0;
+		if (filename == NULL || filename[0] == '\0') {
+			mine->filename_type = FNT_STDIN;
+		} else
+			mine->filename_type = FNT_MBS;
+		if (archive_read_append_callback_data(a, mine) != (ARCHIVE_OK))
+			return (ARCHIVE_FATAL);
+		if (filenames == NULL)
+			break;
+		filename = *(filenames++);
+	} while (filename != NULL && filename[0] != '\0');
+	archive_read_set_open_callback(a, file_open);
+	archive_read_set_read_callback(a, file_read);
+	archive_read_set_skip_callback(a, file_skip);
+	archive_read_set_close_callback(a, file_close);
+	archive_read_set_switch_callback(a, file_switch);
+	archive_read_set_seek_callback(a, file_seek);
 
-	if (filename == NULL || filename[0] == '\0') {
-		filename_type = FNT_STDIN;
-	} else
-		filename_type = FNT_MBS;
-	return (file_open_filename(a, filename_type, filename, block_size));
+	return (archive_read_open1(a));
+no_memory:
+	archive_set_error(a, ENOMEM, "No memory");
+	return (ARCHIVE_FATAL);
 }
 
 int
 archive_read_open_filename_w(struct archive *a, const wchar_t *wfilename,
     size_t block_size)
 {
-	enum fnt_e filename_type;
+	struct read_file_data *mine = (struct read_file_data *)calloc(1,
+		sizeof(*mine) + wcslen(wfilename) * sizeof(wchar_t));
+	if (!mine)
+	{
+		archive_set_error(a, ENOMEM, "No memory");
+		return (ARCHIVE_FATAL);
+	}
+	mine->fd = -1;
+	mine->block_size = block_size;
 
 	if (wfilename == NULL || wfilename[0] == L'\0') {
-		filename_type = FNT_STDIN;
+		mine->filename_type = FNT_STDIN;
 	} else {
 #if defined(_WIN32) && !defined(__CYGWIN__)
-		filename_type = FNT_WCS;
+		mine->filename_type = FNT_WCS;
+		wcscpy(mine->filename.w, wfilename);
 #else
 		/*
 		 * POSIX system does not support a wchar_t interface for
 		 * open() system call, so we have to translate a whcar_t
 		 * filename to multi-byte one and use it.
 		 */
 		struct archive_string fn;
-		int r;
 
 		archive_string_init(&fn);
 		if (archive_string_append_from_wcs(&fn, wfilename,
 		    wcslen(wfilename)) != 0) {
-			archive_set_error(a, EINVAL,
-			    "Failed to convert a wide-character filename to"
-			    " a multi-byte filename");
+			if (errno == ENOMEM)
+				archive_set_error(a, errno,
+				    "Can't allocate memory");
+			else
+				archive_set_error(a, EINVAL,
+				    "Failed to convert a wide-character"
+				    " filename to a multi-byte filename");
 			archive_string_free(&fn);
+			free(mine);
 			return (ARCHIVE_FATAL);
 		}
-		r = file_open_filename(a, FNT_MBS, fn.s, block_size);
+		mine->filename_type = FNT_MBS;
+		strcpy(mine->filename.m, fn.s);
 		archive_string_free(&fn);
-		return (r);
 #endif
 	}
-	return (file_open_filename(a, filename_type, wfilename, block_size));
+	if (archive_read_append_callback_data(a, mine) != (ARCHIVE_OK))
+		return (ARCHIVE_FATAL);
+	archive_read_set_open_callback(a, file_open);
+	archive_read_set_read_callback(a, file_read);
+	archive_read_set_skip_callback(a, file_skip);
+	archive_read_set_close_callback(a, file_close);
+	archive_read_set_switch_callback(a, file_switch);
+	archive_read_set_seek_callback(a, file_seek);
+
+	return (archive_read_open1(a));
 }
 
 static int
-file_open_filename(struct archive *a, enum fnt_e filename_type,
-    const void *_filename, size_t block_size)
+file_open(struct archive *a, void *client_data)
 {
 	struct stat st;
-	struct read_file_data *mine;
+	struct read_file_data *mine = (struct read_file_data *)client_data;
 	void *buffer;
 	const char *filename = NULL;
 	const wchar_t *wfilename = NULL;
@@ -164,7 +231,7 @@ file_open_filename(struct archive *a, enum fnt_e filename_type,
 #endif
 
 	archive_clear_error(a);
-	if (filename_type == FNT_STDIN) {
+	if (mine->filename_type == FNT_STDIN) {
 		/* We used to delegate stdin support by
 		 * directly calling archive_read_open_fd(a,0,block_size)
 		 * here, but that doesn't (and shouldn't) handle the
@@ -179,17 +246,18 @@ file_open_filename(struct archive *a, enum fnt_e filename_type,
 		setmode(0, O_BINARY);
 #endif
 		filename = "";
-	} else if (filename_type == FNT_MBS) {
-		filename = (const char *)_filename;
-		fd = open(filename, O_RDONLY | O_BINARY);
+	} else if (mine->filename_type == FNT_MBS) {
+		filename = mine->filename.m;
+		fd = open(filename, O_RDONLY | O_BINARY | O_CLOEXEC);
+		__archive_ensure_cloexec_flag(fd);
 		if (fd < 0) {
 			archive_set_error(a, errno,
 			    "Failed to open '%s'", filename);
 			return (ARCHIVE_FATAL);
 		}
 	} else {
 #if defined(_WIN32) && !defined(__CYGWIN__)
-		wfilename = (const wchar_t *)_filename;
+		wfilename = mine->filename.w;
 		fd = _wopen(wfilename, O_RDONLY | O_BINARY);
 		if (fd < 0 && errno == ENOENT) {
 			wchar_t *fullpath;
@@ -211,7 +279,7 @@ file_open_filename(struct archive *a, enum fnt_e filename_type,
 #endif
 	}
 	if (fstat(fd, &st) != 0) {
-		if (filename_type == FNT_WCS)
+		if (mine->filename_type == FNT_WCS)
 			archive_set_error(a, errno, "Can't stat '%S'",
 			    wfilename);
 		else
@@ -276,50 +344,32 @@ file_open_filename(struct archive *a, enum fnt_e filename_type,
 #endif
 	/* TODO: Add an "is_tape_like" variable and appropriate tests. */
 
-	if (filename_type == FNT_WCS)
-		mine = (struct read_file_data *)calloc(1,
-		    sizeof(*mine) + wcslen(wfilename) * sizeof(wchar_t));
-	else
-		mine = (struct read_file_data *)calloc(1,
-		    sizeof(*mine) + strlen(filename));
 	/* Disk-like devices prefer power-of-two block sizes.  */
 	/* Use provided block_size as a guide so users have some control. */
 	if (is_disk_like) {
 		size_t new_block_size = 64 * 1024;
-		while (new_block_size < block_size
+		while (new_block_size < mine->block_size
 		    && new_block_size < 64 * 1024 * 1024)
 			new_block_size *= 2;
-		block_size = new_block_size;
+		mine->block_size = new_block_size;
 	}
-	buffer = malloc(block_size);
+	buffer = malloc(mine->block_size);
 	if (mine == NULL || buffer == NULL) {
 		archive_set_error(a, ENOMEM, "No memory");
 		free(mine);
 		free(buffer);
 		return (ARCHIVE_FATAL);
 	}
-	if (filename_type == FNT_WCS)
-		wcscpy(mine->filename.w, wfilename);
-	else
-		strcpy(mine->filename.m, filename);
-	mine->filename_type = filename_type;
-	mine->block_size = block_size;
 	mine->buffer = buffer;
 	mine->fd = fd;
 	/* Remember mode so close can decide whether to flush. */
 	mine->st_mode = st.st_mode;
 
 	/* Disk-like inputs can use lseek(). */
-	if (is_disk_like) {
-		archive_read_set_seek_callback(a, file_seek);
+	if (is_disk_like)
 		mine->use_lseek = 1;
-	}
 
-	archive_read_set_read_callback(a, file_read);
-	archive_read_set_skip_callback(a, file_skip);
-	archive_read_set_close_callback(a, file_close);
-	archive_read_set_callback_data(a, mine);
-	return (archive_read_open1(a));
+	return (ARCHIVE_OK);
 }
 
 static ssize_t
@@ -397,9 +447,7 @@ file_skip_lseek(struct archive *a, void *client_data, int64_t request)
 	/* TODO: Deal with case where off_t isn't 64 bits.
 	 * This shouldn't be a problem on Linux or other POSIX
 	 * systems, since the configuration logic for libarchive
-	 * tries to obtain a 64-bit off_t.  It's still an issue
-	 * on Windows, though, so it might suffice to just use
-	 * _lseeki64() on Windows.
+	 * tries to obtain a 64-bit off_t.
 	 */
 	if ((old_offset = lseek(mine->fd, 0, SEEK_CUR)) >= 0 &&
 	    (new_offset = lseek(mine->fd, request, SEEK_CUR)) >= 0)
@@ -450,7 +498,7 @@ static int64_t
 file_seek(struct archive *a, void *client_data, int64_t request, int whence)
 {
 	struct read_file_data *mine = (struct read_file_data *)client_data;
-	off_t r;
+	int64_t r;
 
 	/* We use off_t here because lseek() is declared that way. */
 	/* See above for notes about when off_t is less than 64 bits. */
@@ -471,7 +519,7 @@ file_seek(struct archive *a, void *client_data, int64_t request, int whence)
 }
 
 static int
-file_close(struct archive *a, void *client_data)
+file_close2(struct archive *a, void *client_data)
 {
 	struct read_file_data *mine = (struct read_file_data *)client_data;
 
@@ -504,6 +552,23 @@ file_close(struct archive *a, void *client_data)
 			close(mine->fd);
 	}
 	free(mine->buffer);
+	mine->buffer = NULL;
+	mine->fd = -1;
+	return (ARCHIVE_OK);
+}
+
+static int
+file_close(struct archive *a, void *client_data)
+{
+	struct read_file_data *mine = (struct read_file_data *)client_data;
+	file_close2(a, client_data);
 	free(mine);
 	return (ARCHIVE_OK);
 }
+
+static int
+file_switch(struct archive *a, void *client_data1, void *client_data2)
+{
+	file_close2(a, client_data1);
+	return file_open(a, client_data2);
+}