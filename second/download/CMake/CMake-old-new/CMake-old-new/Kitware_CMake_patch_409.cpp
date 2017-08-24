@@ -1,6 +1,6 @@
 /*-
  * Copyright (c) 2004 Tim Kientzle
- * Copyright (c) 2011 Michihiro NAKAJIMA
+ * Copyright (c) 2011-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -38,23 +38,26 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_read_support_format_zip.c 201102
 #endif
 
 #include "archive.h"
+#include "archive_endian.h"
 #include "archive_entry.h"
 #include "archive_entry_locale.h"
 #include "archive_private.h"
+#include "archive_rb.h"
 #include "archive_read_private.h"
-#include "archive_endian.h"
 
 #ifndef HAVE_ZLIB_H
 #include "archive_crc32.h"
 #endif
 
 struct zip_entry {
+	struct archive_rb_node	node;
 	int64_t			local_header_offset;
 	int64_t			compressed_size;
 	int64_t			uncompressed_size;
 	int64_t			gid;
 	int64_t			uid;
 	struct archive_entry	*entry;
+	struct archive_string	rsrcname;
 	time_t			mtime;
 	time_t			atime;
 	time_t			ctime;
@@ -67,15 +70,19 @@ struct zip_entry {
 
 struct zip {
 	/* Structural information about the archive. */
+	int64_t			end_of_central_directory_offset;
 	int64_t			central_directory_offset;
 	size_t			central_directory_size;
 	size_t			central_directory_entries;
 	char			have_central_directory;
+	int64_t			offset;
 
 	/* List of entries (seekable Zip only) */
 	size_t			entries_remaining;
 	struct zip_entry	*zip_entries;
 	struct zip_entry	*entry;
+	struct archive_rb_tree	tree;
+	struct archive_rb_tree	tree_rsrc;
 
 	size_t			unconsumed;
 
@@ -116,29 +123,36 @@ struct zip {
 #define ZIP_STRONG_ENCRYPTED	(1<<6)	
 #define ZIP_UTF8_NAME		(1<<11)	
 
-static int	archive_read_format_zip_streamable_bid(struct archive_read *, int);
-static int	archive_read_format_zip_seekable_bid(struct archive_read *, int);
+static int	archive_read_format_zip_streamable_bid(struct archive_read *,
+		    int);
+static int	archive_read_format_zip_seekable_bid(struct archive_read *,
+		    int);
 static int	archive_read_format_zip_options(struct archive_read *,
 		    const char *, const char *);
 static int	archive_read_format_zip_cleanup(struct archive_read *);
 static int	archive_read_format_zip_read_data(struct archive_read *,
 		    const void **, size_t *, int64_t *);
 static int	archive_read_format_zip_read_data_skip(struct archive_read *a);
-static int	archive_read_format_zip_seekable_read_header(struct archive_read *,
-		    struct archive_entry *);
-static int	archive_read_format_zip_streamable_read_header(struct archive_read *,
-		    struct archive_entry *);
+static int	archive_read_format_zip_seekable_read_header(
+		    struct archive_read *, struct archive_entry *);
+static int	archive_read_format_zip_streamable_read_header(
+		    struct archive_read *, struct archive_entry *);
+static ssize_t	zip_get_local_file_header_size(struct archive_read *, size_t);
 #ifdef HAVE_ZLIB_H
+static int	zip_deflate_init(struct archive_read *, struct zip *);
 static int	zip_read_data_deflate(struct archive_read *a, const void **buff,
 		    size_t *size, int64_t *offset);
 #endif
 static int	zip_read_data_none(struct archive_read *a, const void **buff,
 		    size_t *size, int64_t *offset);
 static int	zip_read_local_file_header(struct archive_read *a,
-    struct archive_entry *entry, struct zip *);
+		    struct archive_entry *entry, struct zip *);
 static time_t	zip_time(const char *);
 static const char *compression_name(int compression);
-static void process_extra(const char *, size_t, struct zip_entry *);
+static void	process_extra(const char *, size_t, struct zip_entry *);
+
+int	archive_read_support_format_zip_streamable(struct archive *);
+int	archive_read_support_format_zip_seekable(struct archive *);
 
 int
 archive_read_support_format_zip_streamable(struct archive *_a)
@@ -166,6 +180,7 @@ archive_read_support_format_zip_streamable(struct archive *_a)
 	    archive_read_format_zip_streamable_read_header,
 	    archive_read_format_zip_read_data,
 	    archive_read_format_zip_read_data_skip,
+	    NULL,
 	    archive_read_format_zip_cleanup);
 
 	if (r != ARCHIVE_OK)
@@ -199,6 +214,7 @@ archive_read_support_format_zip_seekable(struct archive *_a)
 	    archive_read_format_zip_seekable_read_header,
 	    archive_read_format_zip_read_data,
 	    archive_read_format_zip_read_data_skip,
+	    NULL,
 	    archive_read_format_zip_cleanup);
 
 	if (r != ARCHIVE_OK)
@@ -217,14 +233,13 @@ archive_read_support_format_zip(struct archive *a)
 }
 
 /*
- * TODO: This is a performance sink because it forces
- * the read core to drop buffered data from the start
- * of file, which will then have to be re-read again
- * if this bidder loses.
+ * TODO: This is a performance sink because it forces the read core to
+ * drop buffered data from the start of file, which will then have to
+ * be re-read again if this bidder loses.
  *
- * Consider passing in the winning bid value to subsequent
- * bidders so that this bidder in particular can avoid
- * seeking if it knows it's going to lose anyway.
+ * We workaround this a little by passing in the best bid so far so
+ * that later bidders can do nothing if they know they'll never
+ * outbid.  But we can certainly do better...
  */
 static int
 archive_read_format_zip_seekable_bid(struct archive_read *a, int best_bid)
@@ -249,21 +264,63 @@ archive_read_format_zip_seekable_bid(struct archive_read *a, int best_bid)
 	/* First four bytes are signature for end of central directory
 	   record.  Four zero bytes ensure this isn't a multi-volume
 	   Zip file (which we don't yet support). */
-	if (memcmp(p, "PK\005\006\000\000\000\000", 8) != 0)
-		return 0;
+	if (memcmp(p, "PK\005\006\000\000\000\000", 8) != 0) {
+		int64_t i, tail;
+		int found;
+
+		/*
+		 * If there is a comment in end of central directory
+		 * record, 22 bytes are too short. we have to read more
+		 * to properly detect the record. Hopefully, a length
+		 * of the comment is not longer than 16362 bytes(16K-22).
+		 */
+		if (filesize + 22 > 1024 * 16) {
+			tail = 1024 * 16;
+			filesize = __archive_read_seek(a, tail * -1, SEEK_END);
+		} else {
+			tail = filesize + 22;
+			filesize = __archive_read_seek(a, 0, SEEK_SET);
+		}
+		if (filesize < 0)
+			return 0;
+		if ((p = __archive_read_ahead(a, (size_t)tail, NULL)) == NULL)
+			return 0;
+		for (found = 0, i = 0;!found && i < tail - 22;) {
+			switch (p[i]) {
+			case 'P':
+				if (memcmp(p+i,
+				    "PK\005\006\000\000\000\000", 8) == 0) {
+					p += i;
+					filesize += tail -
+					    (22 + archive_le16dec(p+20));
+					found = 1;
+				} else
+					i += 8;
+				break;
+			case 'K': i += 7; break;
+			case 005: i += 6; break;
+			case 006: i += 5; break;
+			default: i += 1; break;
+			}
+		}
+		if (!found)
+			return 0;
+	}
 
 	/* Since we've already done the hard work of finding the
 	   end of central directory record, let's save the important
 	   information. */
 	zip->central_directory_entries = archive_le16dec(p + 10);
 	zip->central_directory_size = archive_le32dec(p + 12);
 	zip->central_directory_offset = archive_le32dec(p + 16);
+	zip->end_of_central_directory_offset = filesize;
 
 	/* Just one volume, so central dir must all be on this volume. */
 	if (zip->central_directory_entries != archive_le16dec(p + 8))
 		return 0;
 	/* Central directory can't extend beyond end of this file. */
-	if (zip->central_directory_offset + zip->central_directory_size > filesize)
+	if (zip->central_directory_offset +
+	    (int64_t)zip->central_directory_size > filesize)
 		return 0;
 
 	/* This is just a tiny bit higher than the maximum returned by
@@ -273,18 +330,117 @@ archive_read_format_zip_seekable_bid(struct archive_read *a, int best_bid)
 }
 
 static int
+cmp_node(const struct archive_rb_node *n1, const struct archive_rb_node *n2)
+{
+	const struct zip_entry *e1 = (const struct zip_entry *)n1;
+	const struct zip_entry *e2 = (const struct zip_entry *)n2;
+
+	return ((int)(e2->local_header_offset - e1->local_header_offset));
+}
+
+static int
+cmp_key(const struct archive_rb_node *n, const void *key)
+{
+	/* This function won't be called */
+	(void)n; /* UNUSED */
+	(void)key; /* UNUSED */
+	return 1;
+}
+
+static int
+rsrc_cmp_node(const struct archive_rb_node *n1,
+    const struct archive_rb_node *n2)
+{
+	const struct zip_entry *e1 = (const struct zip_entry *)n1;
+	const struct zip_entry *e2 = (const struct zip_entry *)n2;
+
+	return (strcmp(e2->rsrcname.s, e1->rsrcname.s));
+}
+
+static int
+rsrc_cmp_key(const struct archive_rb_node *n, const void *key)
+{
+	const struct zip_entry *e = (const struct zip_entry *)n;
+	return (strcmp((const char *)key, e->rsrcname.s));
+}
+
+static const char *
+rsrc_basename(const char *name, size_t name_length)
+{
+	const char *s, *r;
+
+	r = s = name;
+	for (;;) {
+		s = memchr(s, '/', name_length - (s - name));
+		if (s == NULL)
+			break;
+		r = ++s;
+	}
+	return (r);
+}
+
+static void
+expose_parent_dirs(struct zip *zip, const char *name, size_t name_length)
+{
+	struct archive_string str;
+	struct zip_entry *dir;
+	char *s;
+
+	archive_string_init(&str);
+	archive_strncpy(&str, name, name_length);
+	for (;;) {
+		s = strrchr(str.s, '/');
+		if (s == NULL)
+			break;
+		*s = '\0';
+		/* Transfer the parent directory from zip->tree_rsrc RB
+		 * tree to zip->tree RB tree to expose. */
+		dir = (struct zip_entry *)
+		    __archive_rb_tree_find_node(&zip->tree_rsrc, str.s);
+		if (dir == NULL)
+			break;
+		__archive_rb_tree_remove_node(&zip->tree_rsrc, &dir->node);
+		archive_string_free(&dir->rsrcname);
+		__archive_rb_tree_insert_node(&zip->tree, &dir->node);
+	}
+	archive_string_free(&str);
+}
+
+static int
 slurp_central_directory(struct archive_read *a, struct zip *zip)
 {
 	unsigned i;
+	int64_t correction;
+	static const struct archive_rb_tree_ops rb_ops = {
+		&cmp_node, &cmp_key
+	};
+	static const struct archive_rb_tree_ops rb_rsrc_ops = {
+		&rsrc_cmp_node, &rsrc_cmp_key
+	};
+
+	/*
+	 * Consider the archive file we are reading may be SFX.
+	 * So we have to calculate a SFX header size to revise
+	 * ZIP header offsets.
+	 */
+	correction = zip->end_of_central_directory_offset -
+	    (zip->central_directory_offset + zip->central_directory_size);
+	/* The central directory offset is relative value, and so
+	 * we revise this offset for SFX. */
+	zip->central_directory_offset += correction;
 
 	__archive_read_seek(a, zip->central_directory_offset, SEEK_SET);
+	zip->offset = zip->central_directory_offset;
+	__archive_rb_tree_init(&zip->tree, &rb_ops);
+	__archive_rb_tree_init(&zip->tree_rsrc, &rb_rsrc_ops);
 
-	zip->zip_entries = calloc(zip->central_directory_entries, sizeof(struct zip_entry));
+	zip->zip_entries = calloc(zip->central_directory_entries,
+				sizeof(struct zip_entry));
 	for (i = 0; i < zip->central_directory_entries; ++i) {
 		struct zip_entry *zip_entry = &zip->zip_entries[i];
 		size_t filename_length, extra_length, comment_length;
 		uint32_t external_attributes;
-		const char *p;
+		const char *name, *p, *r;
 
 		if ((p = __archive_read_ahead(a, 46, NULL)) == NULL)
 			return ARCHIVE_FATAL;
@@ -298,7 +454,7 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 		zip_entry->system = p[5];
 		/* version_required = archive_le16dec(p + 6); */
 		zip_entry->flags = archive_le16dec(p + 8);
-		zip_entry->compression = archive_le16dec(p + 10);
+		zip_entry->compression = (char)archive_le16dec(p + 10);
 		zip_entry->mtime = zip_time(p + 12);
 		zip_entry->crc32 = archive_le32dec(p + 16);
 		zip_entry->compressed_size = archive_le32dec(p + 20);
@@ -309,31 +465,233 @@ slurp_central_directory(struct archive_read *a, struct zip *zip)
 		/* disk_start = archive_le16dec(p + 34); */ /* Better be zero. */
 		/* internal_attributes = archive_le16dec(p + 36); */ /* text bit */
 		external_attributes = archive_le32dec(p + 38);
-		zip_entry->local_header_offset = archive_le32dec(p + 42);
+		zip_entry->local_header_offset =
+		    archive_le32dec(p + 42) + correction;
 
+		/* If we can't guess the mode, leave it zero here;
+		   when we read the local file header we might get
+		   more information. */
+		zip_entry->mode = 0;
 		if (zip_entry->system == 3) {
 			zip_entry->mode = external_attributes >> 16;
+		}
+
+		/*
+		 * Mac resource fork files are stored under the
+		 * "__MACOSX/" directory, so we should check if
+		 * it is.
+		 */
+		/* Make sure we have the file name. */
+		if ((p = __archive_read_ahead(a, 46 + filename_length, NULL))
+		    == NULL)
+			return ARCHIVE_FATAL;
+		name = p + 46;
+		r = rsrc_basename(name, filename_length);
+		if (filename_length >= 9 &&
+		    strncmp("__MACOSX/", name, 9) == 0) {
+			/* If this file is not a resource fork nor
+			 * a directory. We should treat it as a non
+			 * resource fork file to expose it. */
+			if (name[filename_length-1] != '/' &&
+			    (r - name < 3 || r[0] != '.' || r[1] != '_')) {
+				__archive_rb_tree_insert_node(&zip->tree,
+				    &zip_entry->node);
+				/* Expose its parent directories. */
+				expose_parent_dirs(zip, name, filename_length);
+			} else {
+				/* This file is a resource fork file or
+				 * a directory. */
+				archive_strncpy(&(zip_entry->rsrcname), name,
+				    filename_length);
+				__archive_rb_tree_insert_node(&zip->tree_rsrc,
+				    &zip_entry->node);
+			}
 		} else {
-			zip_entry->mode = AE_IFREG | 0777;
+			/* Generate resource fork name to find its resource
+			 * file at zip->tree_rsrc. */
+			archive_strcpy(&(zip_entry->rsrcname), "__MACOSX/");
+			archive_strncat(&(zip_entry->rsrcname), name, r - name);
+			archive_strcat(&(zip_entry->rsrcname), "._");
+			archive_strncat(&(zip_entry->rsrcname),
+			    name + (r - name), filename_length - (r - name));
+			/* Register an entry to RB tree to sort it by
+			 * file offset. */
+			__archive_rb_tree_insert_node(&zip->tree,
+			    &zip_entry->node);
 		}
 
-		/* Do we need to parse filename here? */
-		/* Or can we wait until we read the local header? */
+		/* We don't read the filename until we get to the
+		   local file header.  Reading it here would speed up
+		   table-of-contents operations (removing the need to
+		   find and read local file header to get the
+		   filename) at the cost of requiring a lot of extra
+		   space. */
+		/* We don't read the extra block here.  We assume it
+		   will be duplicated at the local file header. */
 		__archive_read_consume(a,
 		    46 + filename_length + extra_length + comment_length);
 	}
 
-	/* TODO: Sort zip entries. */
-
 	return ARCHIVE_OK;
 }
 
+static int64_t
+zip_read_consume(struct archive_read *a, int64_t bytes)
+{
+	struct zip *zip = (struct zip *)a->format->data;
+	int64_t skip;
+
+	skip = __archive_read_consume(a, bytes);
+	if (skip > 0)
+		zip->offset += skip;
+	return (skip);
+}
+
+static int
+zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,
+    struct zip_entry *rsrc)
+{
+	struct zip *zip = (struct zip *)a->format->data;
+	unsigned char *metadata, *mp;
+	int64_t offset = zip->offset;
+	size_t remaining_bytes, metadata_bytes;
+	ssize_t hsize;
+	int ret = ARCHIVE_OK, eof;
+
+	switch(rsrc->compression) {
+	case 0:  /* No compression. */
+#ifdef HAVE_ZLIB_H
+	case 8: /* Deflate compression. */
+#endif
+		break;
+	default: /* Unsupported compression. */
+		/* Return a warning. */
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Unsupported ZIP compression method (%s)",
+		    compression_name(rsrc->compression));
+		/* We can't decompress this entry, but we will
+		 * be able to skip() it and try the next entry. */
+		return (ARCHIVE_WARN);
+	}
+
+	if (rsrc->uncompressed_size > (128 * 1024)) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Mac metadata is too large: %jd > 128K bytes",
+		    (intmax_t)rsrc->uncompressed_size);
+		return (ARCHIVE_WARN);
+	}
+
+	metadata = malloc((size_t)rsrc->uncompressed_size);
+	if (metadata == NULL) {
+		archive_set_error(&a->archive, ENOMEM,
+		    "Can't allocate memory for Mac metadata");
+		return (ARCHIVE_FATAL);
+	}
+
+	if (zip->offset < rsrc->local_header_offset)
+		zip_read_consume(a, rsrc->local_header_offset - zip->offset);
+	else if (zip->offset != rsrc->local_header_offset) {
+		__archive_read_seek(a, rsrc->local_header_offset, SEEK_SET);
+		zip->offset = zip->entry->local_header_offset;
+	}
+
+	hsize = zip_get_local_file_header_size(a, 0);
+	zip_read_consume(a, hsize);
+
+	remaining_bytes = (size_t)rsrc->compressed_size;
+	metadata_bytes = (size_t)rsrc->uncompressed_size;
+	mp = metadata;
+	eof = 0;
+	while (!eof && remaining_bytes) {
+		const unsigned char *p;
+		ssize_t bytes_avail;
+		size_t bytes_used;
+
+		p = __archive_read_ahead(a, 1, &bytes_avail);
+		if (p == NULL) {
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
+			    "Truncated ZIP file header");
+			ret = ARCHIVE_WARN;
+			goto exit_mac_metadata;
+		}
+		if ((size_t)bytes_avail > remaining_bytes)
+			bytes_avail = remaining_bytes;
+		switch(rsrc->compression) {
+		case 0:  /* No compression. */
+			memcpy(mp, p, bytes_avail);
+			bytes_used = (size_t)bytes_avail;
+			metadata_bytes -= bytes_used;
+			mp += bytes_used;
+			if (metadata_bytes == 0)
+				eof = 1;
+			break;
+#ifdef HAVE_ZLIB_H
+		case 8: /* Deflate compression. */
+		{
+			int r;
+
+			ret = zip_deflate_init(a, zip);
+			if (ret != ARCHIVE_OK)
+				goto exit_mac_metadata;
+			zip->stream.next_in =
+			    (Bytef *)(uintptr_t)(const void *)p;
+			zip->stream.avail_in = (uInt)bytes_avail;
+			zip->stream.total_in = 0;
+			zip->stream.next_out = mp;
+			zip->stream.avail_out = (uInt)metadata_bytes;
+			zip->stream.total_out = 0;
+
+			r = inflate(&zip->stream, 0);
+			switch (r) {
+			case Z_OK:
+				break;
+			case Z_STREAM_END:
+				eof = 1;
+				break;
+			case Z_MEM_ERROR:
+				archive_set_error(&a->archive, ENOMEM,
+				    "Out of memory for ZIP decompression");
+				ret = ARCHIVE_FATAL;
+				goto exit_mac_metadata;
+			default:
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_MISC,
+				    "ZIP decompression failed (%d)", r);
+				ret = ARCHIVE_FATAL;
+				goto exit_mac_metadata;
+			}
+			bytes_used = zip->stream.total_in;
+			metadata_bytes -= zip->stream.total_out;
+			mp += zip->stream.total_out;
+			break;
+		}
+#endif
+		default:
+			bytes_used = 0;
+			break;
+		}
+		zip_read_consume(a, bytes_used);
+		remaining_bytes -= bytes_used;
+	}
+	archive_entry_copy_mac_metadata(entry, metadata,
+	    (size_t)rsrc->uncompressed_size - metadata_bytes);
+
+	__archive_read_seek(a, offset, SEEK_SET);
+	zip->offset = offset;
+exit_mac_metadata:
+	zip->decompress_init = 0;
+	free(metadata);
+	return (ret);
+}
+
 static int
 archive_read_format_zip_seekable_read_header(struct archive_read *a,
 	struct archive_entry *entry)
 {
 	struct zip *zip = (struct zip *)a->format->data;
-	int r;
+	struct zip_entry *rsrc;
+	int r, ret = ARCHIVE_OK;
 
 	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
 	if (a->archive.archive_format_name == NULL)
@@ -344,26 +702,45 @@ archive_read_format_zip_seekable_read_header(struct archive_read *a,
 		zip->entries_remaining = zip->central_directory_entries;
 		if (r != ARCHIVE_OK)
 			return r;
-		zip->entry = zip->zip_entries;
-	} else {
-		++zip->entry;
+		/* Get first entry whose local header offset is lower than
+		 * other entries in the archive file. */
+		zip->entry =
+		    (struct zip_entry *)ARCHIVE_RB_TREE_MIN(&zip->tree);
+	} else if (zip->entry != NULL) {
+		/* Get next entry in local header offset order. */
+		zip->entry = (struct zip_entry *)__archive_rb_tree_iterate(
+		    &zip->tree, &zip->entry->node, ARCHIVE_RB_DIR_RIGHT);
 	}
 
-	if (zip->entries_remaining <= 0)
+	if (zip->entries_remaining <= 0 || zip->entry == NULL)
 		return ARCHIVE_EOF;
 	--zip->entries_remaining;
 
-	/* TODO: If entries are sorted by offset within the file, we
-	   should be able to skip here instead of seeking.  Skipping is
-	   typically faster (easier for I/O layer to optimize). */
-	__archive_read_seek(a, zip->entry->local_header_offset, SEEK_SET);
+	if (zip->entry->rsrcname.s)
+		rsrc = (struct zip_entry *)__archive_rb_tree_find_node(
+		    &zip->tree_rsrc, zip->entry->rsrcname.s);
+	else
+		rsrc = NULL;
+
+	/* File entries are sorted by the header offset, we should mostly
+	 * use zip_read_consume to advance a read point to avoid redundant
+	 * data reading.  */
+	if (zip->offset < zip->entry->local_header_offset)
+		zip_read_consume(a,
+		    zip->entry->local_header_offset - zip->offset);
+	else if (zip->offset != zip->entry->local_header_offset) {
+		__archive_read_seek(a, zip->entry->local_header_offset,
+			SEEK_SET);
+		zip->offset = zip->entry->local_header_offset;
+	}
 	zip->unconsumed = 0;
 	r = zip_read_local_file_header(a, entry, zip);
 	if (r != ARCHIVE_OK)
 		return r;
 	if ((zip->entry->mode & AE_IFMT) == AE_IFLNK) {
 		const void *p;
-		size_t linkname_length = archive_entry_size(entry);
+		struct archive_string_conv *sconv;
+		size_t linkname_length = (size_t)archive_entry_size(entry);
 
 		archive_entry_set_size(entry, 0);
 		p = __archive_read_ahead(a, linkname_length, NULL);
@@ -373,17 +750,45 @@ archive_read_format_zip_seekable_read_header(struct archive_read *a,
 			return ARCHIVE_FATAL;
 		}
 
+		sconv = zip->sconv;
+		if (sconv == NULL && (zip->entry->flags & ZIP_UTF8_NAME))
+			sconv = zip->sconv_utf8;
+		if (sconv == NULL)
+			sconv = zip->sconv_default;
 		if (archive_entry_copy_symlink_l(entry, p, linkname_length,
-		    NULL) != 0) {
-			/* NOTE: If the last argument is NULL, this will
-			 * fail only by memeory allocation failure. */
-			archive_set_error(&a->archive, ENOMEM,
-			    "Can't allocate memory for Symlink");
-			return (ARCHIVE_FATAL);
+		    sconv) != 0) {
+			if (errno != ENOMEM && sconv == zip->sconv_utf8 &&
+			    (zip->entry->flags & ZIP_UTF8_NAME))
+			    archive_entry_copy_symlink_l(entry, p,
+				linkname_length, NULL);
+			if (errno == ENOMEM) {
+				archive_set_error(&a->archive, ENOMEM,
+				    "Can't allocate memory for Symlink");
+				return (ARCHIVE_FATAL);
+			}
+			/*
+			 * Since there is no character-set regulation for
+			 * symlink name, do not report the conversion error
+			 * in an automatic conversion.
+			 */
+			if (sconv != zip->sconv_utf8 ||
+			    (zip->entry->flags & ZIP_UTF8_NAME) == 0) {
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_FILE_FORMAT,
+				    "Symlink cannot be converted "
+				    "from %s to current locale.",
+				    archive_string_conversion_charset_name(
+					sconv));
+				ret = ARCHIVE_WARN;
+			}
 		}
-		/* TODO: handle character-set issues? */
 	}
-	return ARCHIVE_OK;
+	if (rsrc) {
+		int ret2 = zip_read_mac_metadata(a, entry, rsrc);
+		if (ret2 < ret)
+			ret = ret2;
+	}
+	return (ret);
 }
 
 static int
@@ -410,6 +815,11 @@ archive_read_format_zip_streamable_bid(struct archive_read *a, int best_bid)
 			return (30);
 	}
 
+	/* TODO: It's worth looking ahead a little bit for a valid
+	 * PK signature.  In particular, that would make it possible
+	 * to read some UUEncoded SFX files or SFX files coming from
+	 * a network socket. */
+
 	return (0);
 }
 
@@ -424,11 +834,12 @@ archive_read_format_zip_options(struct archive_read *a,
 	if (strcmp(key, "compat-2x")  == 0) {
 		/* Handle filnames as libarchive 2.x */
 		zip->init_default_conversion = (val != NULL) ? 1 : 0;
-		ret = ARCHIVE_OK;
+		return (ARCHIVE_OK);
 	} else if (strcmp(key, "hdrcharset")  == 0) {
 		if (val == NULL || val[0] == 0)
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "zip: hdrcharset option needs a character-set name");
+			    "zip: hdrcharset option needs a character-set name"
+			);
 		else {
 			zip->sconv = archive_string_conversion_from_charset(
 			    &a->archive, val, 0);
@@ -439,11 +850,13 @@ archive_read_format_zip_options(struct archive_read *a,
 			} else
 				ret = ARCHIVE_FATAL;
 		}
-	} else
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "zip: unknown keyword ``%s''", key);
+		return (ret);
+	}
 
-	return (ret);
+	/* Note: The "warn" return is just to inform the options
+	 * supervisor that we didn't handle it.  It will generate
+	 * a suitable error if no one used this option. */
+	return (ARCHIVE_WARN);
 }
 
 static int
@@ -462,15 +875,16 @@ archive_read_format_zip_streamable_read_header(struct archive_read *a,
 	if (zip->zip_entries == NULL) {
 		zip->zip_entries = malloc(sizeof(struct zip_entry));
 		if (zip->zip_entries == NULL) {
-			archive_set_error(&a->archive, ENOMEM, "Out  of memory");
+			archive_set_error(&a->archive, ENOMEM,
+			    "Out  of memory");
 			return ARCHIVE_FATAL;
 		}
 	}
 	zip->entry = zip->zip_entries;
 	memset(zip->entry, 0, sizeof(struct zip_entry));
 
 	/* Search ahead for the next local file header. */
-	__archive_read_consume(a, zip->unconsumed);
+	zip_read_consume(a, zip->unconsumed);
 	zip->unconsumed = 0;
 	for (;;) {
 		int64_t skipped = 0;
@@ -490,8 +904,9 @@ archive_read_format_zip_streamable_read_header(struct archive_read *a,
 
 				if (p[2] == '\003' && p[3] == '\004') {
 					/* Regular file entry. */
-					__archive_read_consume(a, skipped);
-					return zip_read_local_file_header(a, entry, zip);
+					zip_read_consume(a, skipped);
+					return zip_read_local_file_header(a,
+					    entry, zip);
 				}
 
 				if (p[2] == '\005' && p[3] == '\006')
@@ -501,8 +916,31 @@ archive_read_format_zip_streamable_read_header(struct archive_read *a,
 			++p;
 			++skipped;
 		}
-		__archive_read_consume(a, skipped);
+		zip_read_consume(a, skipped);
+	}
+}
+
+static ssize_t
+zip_get_local_file_header_size(struct archive_read *a, size_t extra)
+{
+	const char *p;
+	ssize_t filename_length, extra_length;
+
+	if ((p = __archive_read_ahead(a, extra + 30, NULL)) == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Truncated ZIP file header");
+		return (ARCHIVE_WARN);
+	}
+	p += extra;
+
+	if (memcmp(p, "PK\003\004", 4) != 0) {
+		archive_set_error(&a->archive, -1, "Damaged Zip archive");
+		return ARCHIVE_WARN;
 	}
+	filename_length = archive_le16dec(p + 26);
+	extra_length = archive_le16dec(p + 28);
+
+	return (30 + filename_length + extra_length);
 }
 
 /*
@@ -550,39 +988,42 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 	version = p[4];
 	zip_entry->system = p[5];
 	zip_entry->flags = archive_le16dec(p + 6);
-	zip_entry->compression = archive_le16dec(p + 8);
+	zip_entry->compression = (char)archive_le16dec(p + 8);
 	zip_entry->mtime = zip_time(p + 10);
 	local_crc32 = archive_le32dec(p + 14);
 	compressed_size = archive_le32dec(p + 18);
 	uncompressed_size = archive_le32dec(p + 22);
 	filename_length = archive_le16dec(p + 26);
 	extra_length = archive_le16dec(p + 28);
 
-	__archive_read_consume(a, 30);
+	zip_read_consume(a, 30);
 
 	if (zip->have_central_directory) {
-		/* If we read the central dir entry, we must have size information
-		   as well, so ignore the length-at-end flag. */
+		/* If we read the central dir entry, we must have size
+		 * information as well, so ignore the length-at-end flag. */
 		zip_entry->flags &= ~ZIP_LENGTH_AT_END;
 		/* If we have values from both the local file header
 		   and the central directory, warn about mismatches
 		   which might indicate a damaged file.  But some
 		   writers always put zero in the local header; don't
 		   bother warning about that. */
 		if (local_crc32 != 0 && local_crc32 != zip_entry->crc32) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Inconsistent CRC32 values");
 			ret = ARCHIVE_WARN;
 		}
 		if (compressed_size != 0
 		    && compressed_size != zip_entry->compressed_size) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Inconsistent compressed size");
 			ret = ARCHIVE_WARN;
 		}
 		if (uncompressed_size != 0
 		    && uncompressed_size != zip_entry->uncompressed_size) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Inconsistent uncompressed size");
 			ret = ARCHIVE_WARN;
 		}
@@ -628,7 +1069,7 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 		    archive_string_conversion_charset_name(sconv));
 		ret = ARCHIVE_WARN;
 	}
-	__archive_read_consume(a, filename_length);
+	zip_read_consume(a, filename_length);
 
 	if (zip_entry->mode == 0) {
 		/* Especially in streaming mode, we can end up
@@ -640,14 +1081,14 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 			if (len > 0 && wp[len - 1] == L'/')
 				zip_entry->mode = AE_IFDIR | 0777;
 			else
-				zip_entry->mode = AE_IFREG | 0777;
+				zip_entry->mode = AE_IFREG | 0666;
 		} else {
 			cp = archive_entry_pathname(entry);
 			len = (cp != NULL)?strlen(cp):0;
 			if (len > 0 && cp[len - 1] == '/')
 				zip_entry->mode = AE_IFDIR | 0777;
 			else
-				zip_entry->mode = AE_IFREG | 0777;
+				zip_entry->mode = AE_IFREG | 0666;
 		}
 	}
 
@@ -658,7 +1099,7 @@ zip_read_local_file_header(struct archive_read *a, struct archive_entry *entry,
 		return (ARCHIVE_FATAL);
 	}
 	process_extra(h, extra_length, zip_entry);
-	__archive_read_consume(a, extra_length);
+	zip_read_consume(a, extra_length);
 
 	/* Populate some additional entry fields: */
 	archive_entry_set_mode(entry, zip_entry->mode);
@@ -702,8 +1143,8 @@ compression_name(int compression)
 		"deflation"
 	};
 
-	if (compression <
-	    sizeof(compression_names)/sizeof(compression_names[0]))
+	if (0 <= compression && compression <
+	    (int)(sizeof(compression_names)/sizeof(compression_names[0])))
 		return compression_names[compression];
 	else
 		return "??";
@@ -755,7 +1196,7 @@ archive_read_format_zip_read_data(struct archive_read *a,
 		return (ARCHIVE_FAILED);
 	}
 
-	__archive_read_consume(a, zip->unconsumed);
+	zip_read_consume(a, zip->unconsumed);
 	zip->unconsumed = 0;
 
 	switch(zip->entry->compression) {
@@ -781,13 +1222,16 @@ archive_read_format_zip_read_data(struct archive_read *a,
 		return (r);
 	/* Update checksum */
 	if (*size)
-		zip->entry_crc32 = crc32(zip->entry_crc32, *buff, *size);
+		zip->entry_crc32 = crc32(zip->entry_crc32, *buff,
+		    (unsigned)*size);
 	/* If we hit the end, swallow any end-of-data marker. */
 	if (zip->end_of_entry) {
 		/* Check file size, CRC against these values. */
-		if (zip->entry->compressed_size != zip->entry_compressed_bytes_read) {
+		if (zip->entry->compressed_size !=
+		    zip->entry_compressed_bytes_read) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "ZIP compressed data is wrong size (read %jd, expected %jd)",
+			    "ZIP compressed data is wrong size "
+			    "(read %jd, expected %jd)",
 			    (intmax_t)zip->entry_compressed_bytes_read,
 			    (intmax_t)zip->entry->compressed_size);
 			return (ARCHIVE_WARN);
@@ -797,7 +1241,8 @@ archive_read_format_zip_read_data(struct archive_read *a,
 		if ((zip->entry->uncompressed_size & UINT32_MAX)
 		    != (zip->entry_uncompressed_bytes_read & UINT32_MAX)) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "ZIP uncompressed data is wrong size (read %jd, expected %jd)",
+			    "ZIP uncompressed data is wrong size "
+			    "(read %jd, expected %jd)",
 			    (intmax_t)zip->entry_uncompressed_bytes_read,
 			    (intmax_t)zip->entry->uncompressed_size);
 			return (ARCHIVE_WARN);
@@ -846,6 +1291,8 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 	const char *buff;
 	ssize_t bytes_avail;
 
+	(void)offset; /* UNUSED */
+
 	zip = (struct zip *)(a->format->data);
 
 	if (zip->entry->flags & ZIP_LENGTH_AT_END) {
@@ -858,7 +1305,8 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 			   that are longer than this, so a failure to get at
 			   least 16 bytes really does indicate a truncated
 			   file. */
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Truncated ZIP file data");
 			return (ARCHIVE_FATAL);
 		}
@@ -867,8 +1315,10 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 		if (p[0] == 'P' && p[1] == 'K' 
 		    && p[2] == '\007' && p[3] == '\010'
 		    && archive_le32dec(p + 4) == zip->entry_crc32
-		    && archive_le32dec(p + 8) == zip->entry_compressed_bytes_read
-		    && archive_le32dec(p + 12) == zip->entry_uncompressed_bytes_read) {
+		    && archive_le32dec(p + 8) ==
+			    zip->entry_compressed_bytes_read
+		    && archive_le32dec(p + 12) ==
+			    zip->entry_uncompressed_bytes_read) {
 			zip->entry->crc32 = archive_le32dec(p + 4);
 			zip->entry->compressed_size = archive_le32dec(p + 8);
 			zip->entry->uncompressed_size = archive_le32dec(p + 12);
@@ -879,9 +1329,10 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 		/* If not at EOF, ensure we consume at least one byte. */
 		++p;
 
-		/* Scan forward until we see where a PK\007\010 signature might be. */
-		/* Return bytes up until that point.  On the next call, the code
-		   above will verify the data descriptor. */
+		/* Scan forward until we see where a PK\007\010 signature
+		 * might be. */
+		/* Return bytes up until that point.  On the next call,
+		 * the code above will verify the data descriptor. */
 		while (p < buff + bytes_avail - 4) {
 			if (p[3] == 'P') { p += 3; }
 			else if (p[3] == 'K') { p += 2; }
@@ -900,12 +1351,13 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 		/* Grab a bunch of bytes. */
 		buff = __archive_read_ahead(a, 1, &bytes_avail);
 		if (bytes_avail <= 0) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+			archive_set_error(&a->archive,
+			    ARCHIVE_ERRNO_FILE_FORMAT,
 			    "Truncated ZIP file data");
 			return (ARCHIVE_FATAL);
 		}
 		if (bytes_avail > zip->entry_bytes_remaining)
-			bytes_avail = zip->entry_bytes_remaining;
+			bytes_avail = (ssize_t)zip->entry_bytes_remaining;
 	}
 	*size = bytes_avail;
 	zip->entry_bytes_remaining -= bytes_avail;
@@ -918,6 +1370,31 @@ zip_read_data_none(struct archive_read *a, const void **_buff,
 
 #ifdef HAVE_ZLIB_H
 static int
+zip_deflate_init(struct archive_read *a, struct zip *zip)
+{
+	int r;
+
+	/* If we haven't yet read any data, initialize the decompressor. */
+	if (!zip->decompress_init) {
+		if (zip->stream_valid)
+			r = inflateReset(&zip->stream);
+		else
+			r = inflateInit2(&zip->stream,
+			    -15 /* Don't check for zlib header */);
+		if (r != Z_OK) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Can't initialize ZIP decompression.");
+			return (ARCHIVE_FATAL);
+		}
+		/* Stream structure has been set up. */
+		zip->stream_valid = 1;
+		/* We've initialized decompression for this stream. */
+		zip->decompress_init = 1;
+	}
+	return (ARCHIVE_OK);
+}
+
+static int
 zip_read_data_deflate(struct archive_read *a, const void **buff,
     size_t *size, int64_t *offset)
 {
@@ -926,6 +1403,8 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 	const void *compressed_buff;
 	int r;
 
+	(void)offset; /* UNUSED */
+
 	zip = (struct zip *)(a->format->data);
 
 	/* If the buffer hasn't been allocated, allocate it now. */
@@ -940,23 +1419,9 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 		}
 	}
 
-	/* If we haven't yet read any data, initialize the decompressor. */
-	if (!zip->decompress_init) {
-		if (zip->stream_valid)
-			r = inflateReset(&zip->stream);
-		else
-			r = inflateInit2(&zip->stream,
-			    -15 /* Don't check for zlib header */);
-		if (r != Z_OK) {
-			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-			    "Can't initialize ZIP decompression.");
-			return (ARCHIVE_FATAL);
-		}
-		/* Stream structure has been set up. */
-		zip->stream_valid = 1;
-		/* We've initialized decompression for this stream. */
-		zip->decompress_init = 1;
-	}
+	r = zip_deflate_init(a, zip);
+	if (r != ARCHIVE_OK)
+		return (r);
 
 	/*
 	 * Note: '1' here is a performance optimization.
@@ -967,7 +1432,7 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 	compressed_buff = __archive_read_ahead(a, 1, &bytes_avail);
 	if (0 == (zip->entry->flags & ZIP_LENGTH_AT_END)
 	    && bytes_avail > zip->entry_bytes_remaining) {
-		bytes_avail = zip->entry_bytes_remaining;
+		bytes_avail = (ssize_t)zip->entry_bytes_remaining;
 	}
 	if (bytes_avail <= 0) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
@@ -982,10 +1447,10 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 	 * cast to remove 'const'.
 	 */
 	zip->stream.next_in = (Bytef *)(uintptr_t)(const void *)compressed_buff;
-	zip->stream.avail_in = bytes_avail;
+	zip->stream.avail_in = (uInt)bytes_avail;
 	zip->stream.total_in = 0;
 	zip->stream.next_out = zip->uncompressed_buffer;
-	zip->stream.avail_out = zip->uncompressed_buffer_size;
+	zip->stream.avail_out = (uInt)zip->uncompressed_buffer_size;
 	zip->stream.total_out = 0;
 
 	r = inflate(&zip->stream, 0);
@@ -1007,7 +1472,7 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 
 	/* Consume as much as the compressor actually used. */
 	bytes_avail = zip->stream.total_in;
-	__archive_read_consume(a, bytes_avail);
+	zip_read_consume(a, bytes_avail);
 	zip->entry_bytes_remaining -= bytes_avail;
 	zip->entry_compressed_bytes_read += bytes_avail;
 
@@ -1025,7 +1490,8 @@ zip_read_data_deflate(struct archive_read *a, const void **buff,
 			return (ARCHIVE_FATAL);
 		}
 		/* Consume the optional PK\007\010 marker. */
-		if (p[0] == 'P' && p[1] == 'K' && p[2] == '\007' && p[3] == '\010') {
+		if (p[0] == 'P' && p[1] == 'K' &&
+		    p[2] == '\007' && p[3] == '\010') {
 			zip->entry->crc32 = archive_le32dec(p + 4);
 			zip->entry->compressed_size = archive_le32dec(p + 8);
 			zip->entry->uncompressed_size = archive_le32dec(p + 12);
@@ -1047,14 +1513,11 @@ archive_read_format_zip_read_data_skip(struct archive_read *a)
 	/* If we've already read to end of data, we're done. */
 	if (zip->end_of_entry)
 		return (ARCHIVE_OK);
-	/* If we're seeking, we're done. */
-	if (zip->have_central_directory)
-		return (ARCHIVE_OK);
 
 	/* So we know we're streaming... */
 	if (0 == (zip->entry->flags & ZIP_LENGTH_AT_END)) {
 		/* We know the compressed length, so we can just skip. */
-		int64_t bytes_skipped = __archive_read_consume(a,
+		int64_t bytes_skipped = zip_read_consume(a,
 		    zip->entry_bytes_remaining + zip->unconsumed);
 		if (bytes_skipped < 0)
 			return (ARCHIVE_FATAL);
@@ -1077,36 +1540,36 @@ archive_read_format_zip_read_data_skip(struct archive_read *a)
 			if (r != ARCHIVE_OK)
 				return (r);
 		}
-		break;
+		return ARCHIVE_OK;
 #endif
 	default: /* Uncompressed or unknown. */
 		/* Scan for a PK\007\010 signature. */
-		__archive_read_consume(a, zip->unconsumed);
+		zip_read_consume(a, zip->unconsumed);
 		zip->unconsumed = 0;
 		for (;;) {
 			const char *p, *buff;
 			ssize_t bytes_avail;
 			buff = __archive_read_ahead(a, 16, &bytes_avail);
 			if (bytes_avail < 16) {
-				archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+				archive_set_error(&a->archive,
+				    ARCHIVE_ERRNO_FILE_FORMAT,
 				    "Truncated ZIP file data");
 				return (ARCHIVE_FATAL);
 			}
 			p = buff;
-			while (p < buff + bytes_avail - 16) {
+			while (p <= buff + bytes_avail - 16) {
 				if (p[3] == 'P') { p += 3; }
 				else if (p[3] == 'K') { p += 2; }
 				else if (p[3] == '\007') { p += 1; }
 				else if (p[3] == '\010' && p[2] == '\007'
 				    && p[1] == 'K' && p[0] == 'P') {
-					__archive_read_consume(a, p - buff + 16);
+					zip_read_consume(a, p - buff + 16);
 					return ARCHIVE_OK;
 				} else { p += 4; }
 			}
-			__archive_read_consume(a, p - buff);
+			zip_read_consume(a, p - buff);
 		}
 	}
-	return ARCHIVE_OK;
 }
 
 static int
@@ -1119,6 +1582,11 @@ archive_read_format_zip_cleanup(struct archive_read *a)
 	if (zip->stream_valid)
 		inflateEnd(&zip->stream);
 #endif
+	if (zip->zip_entries && zip->central_directory_entries) {
+		unsigned i;
+		for (i = 0; i < zip->central_directory_entries; i++)
+			archive_string_free(&(zip->zip_entries[i].rsrcname));
+	}
 	free(zip->zip_entries);
 	free(zip->uncompressed_buffer);
 	archive_string_free(&(zip->extra));
@@ -1201,11 +1669,14 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			/* Info-ZIP Unix Extra Field (old version) "UX". */
 			if (datasize >= 8) {
 				zip_entry->atime = archive_le32dec(p + offset);
-				zip_entry->mtime = archive_le32dec(p + offset + 4);
+				zip_entry->mtime =
+				    archive_le32dec(p + offset + 4);
 			}
 			if (datasize >= 12) {
-				zip_entry->uid = archive_le16dec(p + offset + 8);
-				zip_entry->gid = archive_le16dec(p + offset + 10);
+				zip_entry->uid =
+				    archive_le16dec(p + offset + 8);
+				zip_entry->gid =
+				    archive_le16dec(p + offset + 10);
 			}
 			break;
 		}
@@ -1219,7 +1690,8 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 			if (datasize >= 2)
 				zip_entry->uid = archive_le16dec(p + offset);
 			if (datasize >= 4)
-				zip_entry->gid = archive_le16dec(p + offset + 2);
+				zip_entry->gid =
+				    archive_le16dec(p + offset + 2);
 			break;
 		case 0x7875:
 		{
@@ -1231,22 +1703,26 @@ process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
 					/* get a uid size. */
 					uidsize = p[offset+1];
 					if (uidsize == 2)
-						zip_entry->uid = archive_le16dec(
-						     p + offset + 2);
+						zip_entry->uid =
+						    archive_le16dec(
+						        p + offset + 2);
 					else if (uidsize == 4 && datasize >= 6)
-						zip_entry->uid = archive_le32dec(
-						     p + offset + 2);
+						zip_entry->uid =
+						    archive_le32dec(
+						        p + offset + 2);
 				}
 				if (datasize >= (2 + uidsize + 3)) {
 					/* get a gid size. */
 					gidsize = p[offset+2+uidsize];
 					if (gidsize == 2)
-						zip_entry->gid = archive_le16dec(
-						    p+offset+2+uidsize+1);
+						zip_entry->gid =
+						    archive_le16dec(
+						        p+offset+2+uidsize+1);
 					else if (gidsize == 4 &&
 					    datasize >= (2 + uidsize + 5))
-						zip_entry->gid = archive_le32dec(
-						    p+offset+2+uidsize+1);
+						zip_entry->gid =
+						    archive_le32dec(
+						        p+offset+2+uidsize+1);
 				}
 			}
 			break;