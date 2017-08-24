@@ -1,7 +1,7 @@
 /*-
  * Copyright (c) 2003-2007 Tim Kientzle
  * Copyright (c) 2009 Andreas Henriksson <andreas@fatal.se>
- * Copyright (c) 2009-2011 Michihiro NAKAJIMA
+ * Copyright (c) 2009-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -374,6 +374,8 @@ struct iso9660 {
 	size_t		 utf16be_path_len;
 	unsigned char *utf16be_previous_path;
 	size_t		 utf16be_previous_path_len;
+	/* Null buufer used in bidder to improve its performance. */
+	unsigned char	 null[2048];
 };
 
 static int	archive_read_format_iso9660_bid(struct archive_read *, int);
@@ -475,6 +477,7 @@ archive_read_support_format_iso9660(struct archive *_a)
 	    archive_read_format_iso9660_read_header,
 	    archive_read_format_iso9660_read_data,
 	    archive_read_format_iso9660_read_data_skip,
+	    NULL,
 	    archive_read_format_iso9660_cleanup);
 
 	if (r != ARCHIVE_OK) {
@@ -588,6 +591,23 @@ archive_read_format_iso9660_options(struct archive_read *a,
 }
 
 static int
+isNull(struct iso9660 *iso9660, const unsigned char *h, unsigned offset,
+unsigned bytes)
+{
+
+	while (bytes >= sizeof(iso9660->null)) {
+		if (!memcmp(iso9660->null, h + offset, sizeof(iso9660->null)))
+			return (0);
+		offset += sizeof(iso9660->null);
+		bytes -= sizeof(iso9660->null);
+	}
+	if (bytes)
+		return memcmp(iso9660->null, h + offset, bytes) == 0;
+	else
+		return (1);
+}
+
+static int
 isBootRecord(struct iso9660 *iso9660, const unsigned char *h)
 {
 	(void)iso9660; /* UNUSED */
@@ -632,8 +652,6 @@ isVolumePartition(struct iso9660 *iso9660, const unsigned char *h)
 static int
 isVDSetTerminator(struct iso9660 *iso9660, const unsigned char *h)
 {
-	int i;
-
 	(void)iso9660; /* UNUSED */
 
 	/* Type of the Volume Descriptor Set Terminator must be 255. */
@@ -645,9 +663,8 @@ isVDSetTerminator(struct iso9660 *iso9660, const unsigned char *h)
 		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 7; i < 2048; ++i)
-		if (h[i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, 7, 2048-7))
+		return (0);
 
 	return (1);
 }
@@ -708,7 +725,6 @@ isSVD(struct iso9660 *iso9660, const unsigned char *h)
 	ssize_t logical_block_size;
 	int32_t volume_block;
 	int32_t location;
-	int i;
 
 	(void)iso9660; /* UNUSED */
 
@@ -717,15 +733,12 @@ isSVD(struct iso9660 *iso9660, const unsigned char *h)
 		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < SVD_reserved1_size; ++i)
-		if (h[SVD_reserved1_offset + i] != 0)
-			return (0);
-	for (i = 0; i < SVD_reserved2_size; ++i)
-		if (h[SVD_reserved2_offset + i] != 0)
-			return (0);
-	for (i = 0; i < SVD_reserved3_size; ++i)
-		if (h[SVD_reserved3_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, SVD_reserved1_offset, SVD_reserved1_size))
+		return (0);
+	if (!isNull(iso9660, h, SVD_reserved2_offset, SVD_reserved2_size))
+		return (0);
+	if (!isNull(iso9660, h, SVD_reserved3_offset, SVD_reserved3_size))
+		return (0);
 
 	/* File structure version must be 1 for ISO9660/ECMA119. */
 	if (h[SVD_file_structure_version_offset] != 1)
@@ -771,7 +784,6 @@ isEVD(struct iso9660 *iso9660, const unsigned char *h)
 	ssize_t logical_block_size;
 	int32_t volume_block;
 	int32_t location;
-	int i;
 
 	(void)iso9660; /* UNUSED */
 
@@ -788,14 +800,12 @@ isEVD(struct iso9660 *iso9660, const unsigned char *h)
 		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < PVD_reserved2_size; ++i)
-		if (h[PVD_reserved2_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, PVD_reserved2_offset, PVD_reserved2_size))
+		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < PVD_reserved3_size; ++i)
-		if (h[PVD_reserved3_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, PVD_reserved3_offset, PVD_reserved3_size))
+		return (0);
 
 	/* Logical block size must be > 0. */
 	/* I've looked at Ecma 119 and can't find any stronger
@@ -830,14 +840,12 @@ isEVD(struct iso9660 *iso9660, const unsigned char *h)
 		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < PVD_reserved4_size; ++i)
-		if (h[PVD_reserved4_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, PVD_reserved4_offset, PVD_reserved4_size))
+		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < PVD_reserved5_size; ++i)
-		if (h[PVD_reserved5_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, PVD_reserved5_offset, PVD_reserved5_size))
+		return (0);
 
 	/* Read Root Directory Record in Volume Descriptor. */
 	p = h + PVD_root_directory_record_offset;
@@ -869,14 +877,12 @@ isPVD(struct iso9660 *iso9660, const unsigned char *h)
 		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < PVD_reserved2_size; ++i)
-		if (h[PVD_reserved2_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, PVD_reserved2_offset, PVD_reserved2_size))
+		return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < PVD_reserved3_size; ++i)
-		if (h[PVD_reserved3_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, PVD_reserved3_offset, PVD_reserved3_size))
+		return (0);
 
 	/* Logical block size must be > 0. */
 	/* I've looked at Ecma 119 and can't find any stronger
@@ -919,9 +925,8 @@ isPVD(struct iso9660 *iso9660, const unsigned char *h)
 			return (0);
 
 	/* Reserved field must be 0. */
-	for (i = 0; i < PVD_reserved5_size; ++i)
-		if (h[PVD_reserved5_offset + i] != 0)
-			return (0);
+	if (!isNull(iso9660, h, PVD_reserved5_offset, PVD_reserved5_size))
+		return (0);
 
 	/* XXX TODO: Check other values for sanity; reject more
 	 * malformed PVDs. XXX */
@@ -934,8 +939,10 @@ isPVD(struct iso9660 *iso9660, const unsigned char *h)
 	if (!iso9660->primary.location) {
 		iso9660->logical_block_size = logical_block_size;
 		iso9660->volume_block = volume_block;
-		iso9660->volume_size = logical_block_size * (uint64_t)volume_block;
-		iso9660->primary.location = archive_le32dec(p + DR_extent_offset);
+		iso9660->volume_size =
+		    logical_block_size * (uint64_t)volume_block;
+		iso9660->primary.location =
+		    archive_le32dec(p + DR_extent_offset);
 		iso9660->primary.size = archive_le32dec(p + DR_size_offset);
 	}
 
@@ -951,6 +958,12 @@ read_children(struct archive_read *a, struct file_info *parent)
 	size_t step, skip_size;
 
 	iso9660 = (struct iso9660 *)(a->format->data);
+	/* flush any remaining bytes from the last round to ensure
+	 * we're positioned */
+	if (iso9660->entry_bytes_unconsumed) {
+		__archive_read_consume(a, iso9660->entry_bytes_unconsumed);
+		iso9660->entry_bytes_unconsumed = 0;
+	}
 	if (iso9660->current_position > parent->offset) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Ignoring out-of-order directory (%s) %jd > %jd",
@@ -975,8 +988,8 @@ read_children(struct archive_read *a, struct file_info *parent)
 		iso9660->current_position = parent->offset;
 	}
 
-	step = ((parent->size + iso9660->logical_block_size -1) /
-	    iso9660->logical_block_size) * iso9660->logical_block_size;
+	step = (size_t)(((parent->size + iso9660->logical_block_size -1) /
+	    iso9660->logical_block_size) * iso9660->logical_block_size);
 	b = __archive_read_ahead(a, step, NULL);
 	if (b == NULL) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
@@ -1060,101 +1073,112 @@ read_children(struct archive_read *a, struct file_info *parent)
 }
 
 static int
-archive_read_format_iso9660_read_header(struct archive_read *a,
-    struct archive_entry *entry)
+choose_volume(struct archive_read *a, struct iso9660 *iso9660)
 {
-	struct iso9660 *iso9660;
 	struct file_info *file;
-	int r, rd_r = ARCHIVE_OK;
-
-	iso9660 = (struct iso9660 *)(a->format->data);
+	int64_t skipsize;
+	struct vd *vd;
+	const void *block;
+	char seenJoliet;
 
-	if (!a->archive.archive_format) {
-		a->archive.archive_format = ARCHIVE_FORMAT_ISO9660;
-		a->archive.archive_format_name = "ISO9660";
+	vd = &(iso9660->primary);
+	if (!iso9660->opt_support_joliet)
+		iso9660->seenJoliet = 0;
+	if (iso9660->seenJoliet &&
+		vd->location > iso9660->joliet.location)
+		/* This condition is unlikely; by way of caution. */
+		vd = &(iso9660->joliet);
+
+	skipsize = LOGICAL_BLOCK_SIZE * vd->location;
+	skipsize = __archive_read_consume(a, skipsize);
+	if (skipsize < 0)
+		return ((int)skipsize);
+	iso9660->current_position = skipsize;
+
+	block = __archive_read_ahead(a, vd->size, NULL);
+	if (block == NULL) {
+		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+		    "Failed to read full block when scanning "
+		    "ISO9660 directory list");
+		return (ARCHIVE_FATAL);
 	}
 
-	if (iso9660->current_position == 0) {
-		int64_t skipsize;
-		struct vd *vd;
-		const void *block;
-		char seenJoliet;
-
-		vd = &(iso9660->primary);
-		if (!iso9660->opt_support_joliet)
-			iso9660->seenJoliet = 0;
-		if (iso9660->seenJoliet &&
-			vd->location > iso9660->joliet.location)
-			/* This condition is unlikely; by way of caution. */
-			vd = &(iso9660->joliet);
+	/*
+	 * While reading Root Directory, flag seenJoliet must be zero to
+	 * avoid converting special name 0x00(Current Directory) and
+	 * next byte to UCS2.
+	 */
+	seenJoliet = iso9660->seenJoliet;/* Save flag. */
+	iso9660->seenJoliet = 0;
+	file = parse_file_info(a, NULL, block);
+	if (file == NULL)
+		return (ARCHIVE_FATAL);
+	iso9660->seenJoliet = seenJoliet;
 
+	/*
+	 * If the iso image has both RockRidge and Joliet, we preferentially
+	 * use RockRidge Extensions rather than Joliet ones.
+	 */
+	if (vd == &(iso9660->primary) && iso9660->seenRockridge
+	    && iso9660->seenJoliet)
+		iso9660->seenJoliet = 0;
+
+	if (vd == &(iso9660->primary) && !iso9660->seenRockridge
+	    && iso9660->seenJoliet) {
+		/* Switch reading data from primary to joliet. */
+		vd = &(iso9660->joliet);
 		skipsize = LOGICAL_BLOCK_SIZE * vd->location;
+		skipsize -= iso9660->current_position;
 		skipsize = __archive_read_consume(a, skipsize);
 		if (skipsize < 0)
 			return ((int)skipsize);
-		iso9660->current_position = skipsize;
+		iso9660->current_position += skipsize;
 
 		block = __archive_read_ahead(a, vd->size, NULL);
 		if (block == NULL) {
-			archive_set_error(&a->archive,
-			    ARCHIVE_ERRNO_MISC,
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "Failed to read full block when scanning "
 			    "ISO9660 directory list");
 			return (ARCHIVE_FATAL);
 		}
-
-		/*
-		 * While reading Root Directory, flag seenJoliet
-		 * must be zero to avoid converting special name
-		 * 0x00(Current Directory) and next byte to UCS2.
-		 */
-		seenJoliet = iso9660->seenJoliet;/* Save flag. */
 		iso9660->seenJoliet = 0;
 		file = parse_file_info(a, NULL, block);
 		if (file == NULL)
 			return (ARCHIVE_FATAL);
 		iso9660->seenJoliet = seenJoliet;
-		if (vd == &(iso9660->primary) && iso9660->seenRockridge
-		    && iso9660->seenJoliet)
-			/*
-			 * If iso image has RockRidge and Joliet,
-			 * we use RockRidge Extensions.
-			 */
-			iso9660->seenJoliet = 0;
-		if (vd == &(iso9660->primary) && !iso9660->seenRockridge
-		    && iso9660->seenJoliet) {
-			/* Switch reading data from primary to joliet. */ 
-			vd = &(iso9660->joliet);
-			skipsize = LOGICAL_BLOCK_SIZE * vd->location;
-			skipsize -= iso9660->current_position;
-			skipsize = __archive_read_consume(a, skipsize);
-			if (skipsize < 0)
-				return ((int)skipsize);
-			iso9660->current_position += skipsize;
-
-			block = __archive_read_ahead(a, vd->size, NULL);
-			if (block == NULL) {
-				archive_set_error(&a->archive,
-				    ARCHIVE_ERRNO_MISC,
-				    "Failed to read full block when scanning "
-				    "ISO9660 directory list");
-				return (ARCHIVE_FATAL);
-			}
-			iso9660->seenJoliet = 0;
-			file = parse_file_info(a, NULL, block);
-			if (file == NULL)
-				return (ARCHIVE_FATAL);
-			iso9660->seenJoliet = seenJoliet;
-		}
-		/* Store the root directory in the pending list. */
-		if (add_entry(a, iso9660, file) != ARCHIVE_OK)
-			return (ARCHIVE_FATAL);
-		if (iso9660->seenRockridge) {
-			a->archive.archive_format =
-			    ARCHIVE_FORMAT_ISO9660_ROCKRIDGE;
-			a->archive.archive_format_name =
-			    "ISO9660 with Rockridge extensions";
-		}
+	}
+
+	/* Store the root directory in the pending list. */
+	if (add_entry(a, iso9660, file) != ARCHIVE_OK)
+		return (ARCHIVE_FATAL);
+	if (iso9660->seenRockridge) {
+		a->archive.archive_format = ARCHIVE_FORMAT_ISO9660_ROCKRIDGE;
+		a->archive.archive_format_name =
+		    "ISO9660 with Rockridge extensions";
+	}
+
+	return (ARCHIVE_OK);
+}
+
+static int
+archive_read_format_iso9660_read_header(struct archive_read *a,
+    struct archive_entry *entry)
+{
+	struct iso9660 *iso9660;
+	struct file_info *file;
+	int r, rd_r = ARCHIVE_OK;
+
+	iso9660 = (struct iso9660 *)(a->format->data);
+
+	if (!a->archive.archive_format) {
+		a->archive.archive_format = ARCHIVE_FORMAT_ISO9660;
+		a->archive.archive_format_name = "ISO9660";
+	}
+
+	if (iso9660->current_position == 0) {
+		r = choose_volume(a, iso9660);
+		if (r != ARCHIVE_OK)
+			return (r);
 	}
 
 	file = NULL;/* Eliminate a warning. */
@@ -1227,14 +1251,14 @@ archive_read_format_iso9660_read_header(struct archive_read *a,
 	}
 
 	iso9660->entry_bytes_remaining = file->size;
-	iso9660->entry_sparse_offset = 0; /* Offset for sparse-file-aware clients. */
+	/* Offset for sparse-file-aware clients. */
+	iso9660->entry_sparse_offset = 0;
 
 	if (file->offset + file->size > iso9660->volume_size) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "File is beyond end-of-media: %s",
 		    archive_entry_pathname(entry));
 		iso9660->entry_bytes_remaining = 0;
-		iso9660->entry_sparse_offset = 0;
 		return (ARCHIVE_WARN);
 	}
 
@@ -1286,36 +1310,33 @@ archive_read_format_iso9660_read_header(struct archive_read *a,
 			    iso9660->previous_pathname.s);
 		archive_entry_unset_size(entry);
 		iso9660->entry_bytes_remaining = 0;
-		iso9660->entry_sparse_offset = 0;
 		return (rd_r);
 	}
 
-	/* Except for the hardlink case above, if the offset of the
-	 * next entry is before our current position, we can't seek
-	 * backwards to extract it, so issue a warning.  Note that
-	 * this can only happen if this entry was added to the heap
-	 * after we passed this offset, that is, only if the directory
-	 * mentioning this entry is later than the body of the entry.
-	 * Such layouts are very unusual; most ISO9660 writers lay out
-	 * and record all directory information first, then store
-	 * all file bodies. */
-	/* TODO: Someday, libarchive's I/O core will support optional
-	 * seeking.  When that day comes, this code should attempt to
-	 * seek and only return the error if the seek fails.  That
-	 * will give us support for whacky ISO images that require
-	 * seeking while retaining the ability to read almost all ISO
-	 * images in a streaming fashion. */
 	if ((file->mode & AE_IFMT) != AE_IFDIR &&
 	    file->offset < iso9660->current_position) {
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "Ignoring out-of-order file @%jx (%s) %jd < %jd",
-		    (intmax_t)file->number,
-		    iso9660->pathname.s,
-		    (intmax_t)file->offset,
-		    (intmax_t)iso9660->current_position);
-		iso9660->entry_bytes_remaining = 0;
-		iso9660->entry_sparse_offset = 0;
-		return (ARCHIVE_WARN);
+		int64_t r64;
+
+		r64 = __archive_read_seek(a, file->offset, SEEK_SET);
+		if (r64 != (int64_t)file->offset) {
+			/* We can't seek backwards to extract it, so issue
+			 * a warning.  Note that this can only happen if
+			 * this entry was added to the heap after we passed
+			 * this offset, that is, only if the directory
+			 * mentioning this entry is later than the body of
+			 * the entry. Such layouts are very unusual; most
+			 * ISO9660 writers lay out and record all directory
+			 * information first, then store all file bodies. */
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Ignoring out-of-order file @%jx (%s) %jd < %jd",
+			    (intmax_t)file->number,
+			    iso9660->pathname.s,
+			    (intmax_t)file->offset,
+			    (intmax_t)iso9660->current_position);
+			iso9660->entry_bytes_remaining = 0;
+			return (ARCHIVE_WARN);
+		}
+		iso9660->current_position = (uint64_t)r64;
 	}
 
 	/* Initialize zisofs variables. */
@@ -1356,7 +1377,6 @@ archive_read_format_iso9660_read_header(struct archive_read *a,
 		archive_entry_set_nlink(entry, 2 + file->subdirs);
 		/* Directory data has been read completely. */
 		iso9660->entry_bytes_remaining = 0;
-		iso9660->entry_sparse_offset = 0;
 	}
 
 	if (rd_r != ARCHIVE_OK)
@@ -1397,17 +1417,17 @@ zisofs_read_data(struct archive_read *a,
 		return (ARCHIVE_FATAL);
 	}
 	if (bytes_read > iso9660->entry_bytes_remaining)
-		bytes_read = iso9660->entry_bytes_remaining;
+		bytes_read = (ssize_t)iso9660->entry_bytes_remaining;
 	avail = bytes_read;
 	uncompressed_size = 0;
 
 	if (!zisofs->initialized) {
 		size_t ceil, xsize;
 
 		/* Allocate block pointers buffer. */
-		ceil = (zisofs->pz_uncompressed_size +
+		ceil = (size_t)((zisofs->pz_uncompressed_size +
 			(((int64_t)1) << zisofs->pz_log2_bs) - 1)
-			>> zisofs->pz_log2_bs;
+			>> zisofs->pz_log2_bs);
 		xsize = (ceil + 1) * 4;
 		if (zisofs->block_pointers_alloc < xsize) {
 			size_t alloc;
@@ -1426,7 +1446,7 @@ zisofs_read_data(struct archive_read *a,
 		zisofs->block_pointers_size = xsize;
 
 		/* Allocate uncompressed data buffer. */
-		xsize = 1UL << zisofs->pz_log2_bs;
+		xsize = (size_t)1UL << zisofs->pz_log2_bs;
 		if (zisofs->uncompressed_buffer_size < xsize) {
 			if (zisofs->uncompressed_buffer != NULL)
 				free(zisofs->uncompressed_buffer);
@@ -1563,9 +1583,10 @@ zisofs_read_data(struct archive_read *a,
 		if (avail > zisofs->block_avail)
 			zisofs->stream.avail_in = zisofs->block_avail;
 		else
-			zisofs->stream.avail_in = avail;
+			zisofs->stream.avail_in = (uInt)avail;
 		zisofs->stream.next_out = zisofs->uncompressed_buffer;
-		zisofs->stream.avail_out = zisofs->uncompressed_buffer_size;
+		zisofs->stream.avail_out =
+		    (uInt)zisofs->uncompressed_buffer_size;
 
 		r = inflate(&zisofs->stream, 0);
 		switch (r) {
@@ -1580,7 +1601,7 @@ zisofs_read_data(struct archive_read *a,
 		uncompressed_size =
 		    zisofs->uncompressed_buffer_size - zisofs->stream.avail_out;
 		avail -= zisofs->stream.next_in - p;
-		zisofs->block_avail -= zisofs->stream.next_in - p;
+		zisofs->block_avail -= (uint32_t)(zisofs->stream.next_in - p);
 	}
 next_data:
 	bytes_read -= avail;
@@ -1590,7 +1611,7 @@ zisofs_read_data(struct archive_read *a,
 	iso9660->entry_sparse_offset += uncompressed_size;
 	iso9660->entry_bytes_remaining -= bytes_read;
 	iso9660->current_position += bytes_read;
-	zisofs->pz_offset += bytes_read;
+	zisofs->pz_offset += (uint32_t)bytes_read;
 	iso9660->entry_bytes_unconsumed += bytes_read;
 
 	return (ARCHIVE_OK);
@@ -1671,7 +1692,7 @@ archive_read_format_iso9660_read_data(struct archive_read *a,
 	if (*buff == NULL)
 		return (ARCHIVE_FATAL);
 	if (bytes_read > iso9660->entry_bytes_remaining)
-		bytes_read = iso9660->entry_bytes_remaining;
+		bytes_read = (ssize_t)iso9660->entry_bytes_remaining;
 	*size = bytes_read;
 	*offset = iso9660->entry_sparse_offset;
 	iso9660->entry_sparse_offset += bytes_read;
@@ -1756,7 +1777,8 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 	 */
 	if (location > 0 &&
 	    (location + ((fsize + iso9660->logical_block_size -1)
-	       / iso9660->logical_block_size)) > iso9660->volume_block) {
+	       / iso9660->logical_block_size))
+			> (uint32_t)iso9660->volume_block) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Invalid location of extent of file");
 		return (NULL);
@@ -1872,9 +1894,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 	if (iso9660->opt_support_rockridge) {
 		if (parent == NULL && rr_end - rr_start >= 7) {
 			p = rr_start;
-			if (p[0] == 'S' && p[1] == 'P'
-			    && p[2] == 7 && p[3] == 1
-			    && p[4] == 0xBE && p[5] == 0xEF) {
+			if (memcmp(p, "SP\x07\x01\xbe\xef", 6) == 0) {
 				/*
 				 * SP extension stores the suspOffset
 				 * (Number of bytes to skip between
@@ -1907,6 +1927,19 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 				free(file);
 				return (NULL);
 			}
+			/*
+			 * A file size of symbolic link files in ISO images
+			 * made by makefs is not zero and its location is
+			 * the same as those of next regular file. That is
+			 * the same as hard like file and it causes unexpected
+			 * error. 
+			 */
+			if (file->size > 0 &&
+			    (file->mode & AE_IFMT) == AE_IFLNK) {
+				file->size = 0;
+				file->number = -1;
+				file->offset = -1;
+			}
 		} else
 			/* If there isn't SUSP, disable parsing
 			 * rock ridge extensions. */
@@ -1921,6 +1954,7 @@ parse_file_info(struct archive_read *a, struct file_info *parent,
 	if (iso9660->seenRockridge) {
 		if (parent != NULL && parent->parent == NULL &&
 		    (flags & 0x02) && iso9660->rr_moved == NULL &&
+		    file->name.s &&
 		    (strcmp(file->name.s, "rr_moved") == 0 ||
 		     strcmp(file->name.s, ".rr_moved") == 0)) {
 			iso9660->rr_moved = file;
@@ -2053,14 +2087,9 @@ parse_rockridge(struct archive_read *a, struct file_info *file,
 		int data_length = p[2] - 4;
 		int version = p[3];
 
-		/*
-		 * Yes, each 'if' here does test p[0] again.
-		 * Otherwise, the fall-through handling to catch
-		 * unsupported extensions doesn't work.
-		 */
 		switch(p[0]) {
 		case 'C':
-			if (p[0] == 'C' && p[1] == 'E') {
+			if (p[1] == 'E') {
 				if (version == 1 && data_length == 24) {
 					/*
 					 * CE extension comprises:
@@ -2078,53 +2107,42 @@ parse_rockridge(struct archive_read *a, struct file_info *file,
 					    != ARCHIVE_OK)
 						return (ARCHIVE_FATAL);
 				}
-				break;
 			}
-			if (p[0] == 'C' && p[1] == 'L') {
+			else if (p[1] == 'L') {
 				if (version == 1 && data_length == 8) {
 					file->cl_offset = (uint64_t)
 					    iso9660->logical_block_size *
 					    (uint64_t)archive_le32dec(data);
 					iso9660->seenRockridge = 1;
 				}
-				break;
 			}
-			/* FALLTHROUGH */
+			break;
 		case 'N':
-			if (p[0] == 'N' && p[1] == 'M') {
+			if (p[1] == 'M') {
 				if (version == 1) {
 					parse_rockridge_NM1(file,
 					    data, data_length);
 					iso9660->seenRockridge = 1;
 				}
-				break;
 			}
-			/* FALLTHROUGH */
+			break;
 		case 'P':
-			if (p[0] == 'P' && p[1] == 'D') {
-				/*
-				 * PD extension is padding;
-				 * contents are always ignored.
-				 */
-				break;
-			}
-			if (p[0] == 'P' && p[1] == 'L') {
-				/*
-				 * PL extension won't appear;
-				 * contents are always ignored.
-				 */
-				break;
-			}
-			if (p[0] == 'P' && p[1] == 'N') {
+			/*
+			 * PD extension is padding;
+			 * contents are always ignored.
+			 *
+			 * PL extension won't appear;
+			 * contents are always ignored.
+			 */
+			if (p[1] == 'N') {
 				if (version == 1 && data_length == 16) {
 					file->rdev = toi(data,4);
 					file->rdev <<= 32;
 					file->rdev |= toi(data + 8, 4);
 					iso9660->seenRockridge = 1;
 				}
-				break;
 			}
-			if (p[0] == 'P' && p[1] == 'X') {
+			else if (p[1] == 'X') {
 				/*
 				 * PX extension comprises:
 				 *   8 bytes for mode,
@@ -2151,35 +2169,31 @@ parse_rockridge(struct archive_read *a, struct file_info *file,
 						    = toi(data + 32, 4);
 					iso9660->seenRockridge = 1;
 				}
-				break;
 			}
-			/* FALLTHROUGH */
+			break;
 		case 'R':
-			if (p[0] == 'R' && p[1] == 'E' && version == 1) {
+			if (p[1] == 'E' && version == 1) {
 				file->re = 1;
 				iso9660->seenRockridge = 1;
-				break;
 			}
-			if (p[0] == 'R' && p[1] == 'R' && version == 1) {
+			else if (p[1] == 'R' && version == 1) {
 				/*
 				 * RR extension comprises:
 				 *    one byte flag value
 				 * This extension is obsolete,
 				 * so contents are always ignored.
 				 */
-				break;
 			}
-			/* FALLTHROUGH */
+			break;
 		case 'S':
-			if (p[0] == 'S' && p[1] == 'L') {
+			if (p[1] == 'L') {
 				if (version == 1) {
 					parse_rockridge_SL1(file,
 					    data, data_length);
 					iso9660->seenRockridge = 1;
 				}
-				break;
 			}
-			if (p[0] == 'S' && p[1] == 'T'
+			else if (p[1] == 'T'
 			    && data_length == 0 && version == 1) {
 				/*
 				 * ST extension marks end of this
@@ -2194,32 +2208,27 @@ parse_rockridge(struct archive_read *a, struct file_info *file,
 				iso9660->seenRockridge = 0;
 				return (ARCHIVE_OK);
 			}
+			break;
 		case 'T':
-			if (p[0] == 'T' && p[1] == 'F') {
+			if (p[1] == 'F') {
 				if (version == 1) {
 					parse_rockridge_TF1(file,
 					    data, data_length);
 					iso9660->seenRockridge = 1;
 				}
-				break;
 			}
-			/* FALLTHROUGH */
+			break;
 		case 'Z':
-			if (p[0] == 'Z' && p[1] == 'F') {
+			if (p[1] == 'F') {
 				if (version == 1)
 					parse_rockridge_ZF1(file,
 					    data, data_length);
-				break;
 			}
-			/* FALLTHROUGH */
+			break;
 		default:
-			/* The FALLTHROUGHs above leave us here for
-			 * any unsupported extension. */
 			break;
 		}
 
-
-
 		p += p[2];
 	}
 	return (ARCHIVE_OK);
@@ -2241,7 +2250,7 @@ register_CE(struct archive_read *a, int32_t location,
 	    offset >= file->offset) ||
 	    offset < iso9660->current_position ||
 	    (((uint64_t)file->ce_offset) + file->ce_size)
-	      > iso9660->logical_block_size ||
+	      > (uint64_t)iso9660->logical_block_size ||
 	    offset + file->ce_offset + file->ce_size
 		  > iso9660->volume_size) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
@@ -2263,7 +2272,7 @@ register_CE(struct archive_read *a, int32_t location,
 			archive_set_error(&a->archive, ENOMEM, "Out of memory");
 			return (ARCHIVE_FATAL);
 		}
-		p = malloc(new_size * sizeof(p[0]));
+		p = calloc(new_size, sizeof(p[0]));
 		if (p == NULL) {
 			archive_set_error(&a->archive, ENOMEM, "Out of memory");
 			return (ARCHIVE_FATAL);
@@ -2513,9 +2522,6 @@ parse_rockridge_SL1(struct file_info *file, const unsigned char *data,
 
 	if (!file->symlink_continues || file->symlink.length < 1)
 		archive_string_empty(&file->symlink);
-	else if (!file->symlink_continues &&
-	    file->symlink.s[file->symlink.length - 1] != '/')
-		separator = "/";
 	file->symlink_continues = 0;
 
 	/*
@@ -2882,8 +2888,9 @@ next_cache_entry(struct archive_read *a, struct iso9660 *iso9660,
 
 fatal_rr:
 	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-	    "Failed to connect 'CL' pointer to 'RE' rr_moved pointer of"
-	    "Rockridge extensions");
+	    "Failed to connect 'CL' pointer to 'RE' rr_moved pointer of "
+	    "Rockridge extensions: current position = %jd, CL offset = %jd",
+	    (intmax_t)iso9660->current_position, (intmax_t)file->cl_offset);
 	return (ARCHIVE_FATAL);
 }
 
@@ -3085,6 +3092,8 @@ isodate7(const unsigned char *v)
 {
 	struct tm tm;
 	int offset;
+	time_t t;
+
 	memset(&tm, 0, sizeof(tm));
 	tm.tm_year = v[0];
 	tm.tm_mon = v[1] - 1;
@@ -3098,14 +3107,19 @@ isodate7(const unsigned char *v)
 		tm.tm_hour -= offset / 4;
 		tm.tm_min -= (offset % 4) * 15;
 	}
-	return (time_from_tm(&tm));
+	t = time_from_tm(&tm);
+	if (t == (time_t)-1)
+		return ((time_t)0);
+	return (t);
 }
 
 static time_t
 isodate17(const unsigned char *v)
 {
 	struct tm tm;
 	int offset;
+	time_t t;
+
 	memset(&tm, 0, sizeof(tm));
 	tm.tm_year = (v[0] - '0') * 1000 + (v[1] - '0') * 100
 	    + (v[2] - '0') * 10 + (v[3] - '0')
@@ -3121,7 +3135,10 @@ isodate17(const unsigned char *v)
 		tm.tm_hour -= offset / 4;
 		tm.tm_min -= (offset % 4) * 15;
 	}
-	return (time_from_tm(&tm));
+	t = time_from_tm(&tm);
+	if (t == (time_t)-1)
+		return ((time_t)0);
+	return (t);
 }
 
 static time_t
@@ -3135,7 +3152,8 @@ time_from_tm(struct tm *t)
 #else
 	/* Else use direct calculation using POSIX assumptions. */
 	/* First, fix up tm_yday based on the year/month/day. */
-	mktime(t);
+	if (mktime(t) == (time_t)-1)
+		return ((time_t)-1);
 	/* Then we can compute timegm() from first principles. */
 	return (t->tm_sec + t->tm_min * 60 + t->tm_hour * 3600
 	    + t->tm_yday * 86400 + (t->tm_year - 70) * 31536000
@@ -3204,10 +3222,12 @@ dump_isodirrec(FILE *out, const unsigned char *isodirrec)
 	fprintf(out, " ilv %d,",
 	    toi(isodirrec + DR_interleave_offset, DR_interleave_size));
 	fprintf(out, " seq %d,",
-	    toi(isodirrec + DR_volume_sequence_number_offset, DR_volume_sequence_number_size));
+	    toi(isodirrec + DR_volume_sequence_number_offset,
+		DR_volume_sequence_number_size));
 	fprintf(out, " nl %d:",
 	    toi(isodirrec + DR_name_len_offset, DR_name_len_size));
 	fprintf(out, " `%.*s'",
-	    toi(isodirrec + DR_name_len_offset, DR_name_len_size), isodirrec + DR_name_offset);
+	    toi(isodirrec + DR_name_len_offset, DR_name_len_size),
+		isodirrec + DR_name_offset);
 }
 #endif