@@ -318,7 +318,7 @@ struct _7zip {
 	uint32_t		 bcj2_code;
 	uint64_t		 bcj2_outPos;
 
-	/* Filename character-set convertion data. */
+	/* Filename character-set conversion data. */
 	struct archive_string_conv *sconv;
 
 	char			 format_name[64];
@@ -409,6 +409,7 @@ archive_read_support_format_7zip(struct archive *_a)
 	    archive_read_format_7zip_read_header,
 	    archive_read_format_7zip_read_data,
 	    archive_read_format_7zip_read_data_skip,
+	    NULL,
 	    archive_read_format_7zip_cleanup);
 
 	if (r != ARCHIVE_OK)
@@ -481,7 +482,7 @@ check_7zip_header_in_sfx(const char *p)
 		 * Magic Code, so we should do this in order not to
 		 * make a mis-detection.
 		 */
-		if (crc32(0, (unsigned char *)p + 12, 20)
+		if (crc32(0, (const unsigned char *)p + 12, 20)
 			!= archive_le32dec(p + 8))
 			return (6); 
 		/* Hit the header! */
@@ -580,7 +581,7 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 		free_Header(&header);
 		if (r != ARCHIVE_OK)
 			return (r);
-		zip->entries_remaining = zip->numFiles;
+		zip->entries_remaining = (size_t)zip->numFiles;
 		zip->entry = zip->entries;
 	} else {
 		++zip->entry;
@@ -630,7 +631,7 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 	if (zip_entry->flg & ATIME_IS_SET)
 		archive_entry_set_atime(entry, zip_entry->atime,
 		    zip_entry->atime_ns);
-	if (zip_entry->ssIndex != -1) {
+	if (zip_entry->ssIndex != (uint32_t)-1) {
 		zip->entry_bytes_remaining =
 		    zip->si.ss.unpackSizes[zip_entry->ssIndex];
 		archive_entry_set_size(entry, zip->entry_bytes_remaining);
@@ -646,27 +647,31 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 	if ((zip_entry->mode & AE_IFMT) == AE_IFLNK) {
 		unsigned char *symname = NULL;
 		size_t symsize = 0;
-		int r;
 
 		/*
 		 * Symbolic-name is recorded as its contents. We have to
 		 * read the contents at this time.
 		 */
 		while (zip->entry_bytes_remaining > 0) {
 			const void *buff;
+			unsigned char *mem;
 			size_t size;
 			int64_t offset;
 
 			r = archive_read_format_7zip_read_data(a, &buff,
 				&size, &offset);
-			if (r < ARCHIVE_WARN)
+			if (r < ARCHIVE_WARN) {
+				free(symname);
 				return (r);
-			symname = realloc(symname, symsize + size + 1);
-			if (symname == NULL) {
+			}
+			mem = realloc(symname, symsize + size + 1);
+			if (mem == NULL) {
+				free(symname);
 				archive_set_error(&a->archive, ENOMEM,
 				    "Can't allocate memory for Symname");
 				return (ARCHIVE_FATAL);
 			}
+			symname = mem;
 			memcpy(symname+symsize, buff, size);
 			symsize += size;
 		}
@@ -680,8 +685,8 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 			symname[symsize] = '\0';
 			archive_entry_copy_symlink(entry,
 			    (const char *)symname);
-			free(symname);
 		}
+		free(symname);
 		archive_entry_set_size(entry, 0);
 	}
 
@@ -705,18 +710,18 @@ archive_read_format_7zip_read_data(struct archive_read *a,
 	if (zip->pack_stream_bytes_unconsumed)
 		read_consume(a);
 
+	*offset = zip->entry_offset;
+	*size = 0;
+	*buff = NULL;
 	/*
 	 * If we hit end-of-entry last time, clean up and return
 	 * ARCHIVE_EOF this time.
 	 */
-	if (zip->end_of_entry) {
-		*offset = zip->entry_offset;
-		*size = 0;
-		*buff = NULL;
+	if (zip->end_of_entry)
 		return (ARCHIVE_EOF);
-	}
 
-	bytes = read_stream(a, buff, zip->entry_bytes_remaining, 0);
+	bytes = read_stream(a, buff,
+		(size_t)zip->entry_bytes_remaining, 0);
 	if (bytes < 0)
 		return ((int)bytes);
 	if (bytes == 0) {
@@ -731,7 +736,8 @@ archive_read_format_7zip_read_data(struct archive_read *a,
 
 	/* Update checksum */
 	if ((zip->entry->flg & CRC32_IS_SET) && bytes)
-		zip->entry_crc32 = crc32(zip->entry_crc32, *buff, bytes);
+		zip->entry_crc32 = crc32(zip->entry_crc32, *buff,
+		    (unsigned)bytes);
 
 	/* If we hit the end, swallow any end-of-data marker. */
 	if (zip->end_of_entry) {
@@ -774,7 +780,7 @@ archive_read_format_7zip_read_data_skip(struct archive_read *a)
 	 * If the length is at the beginning, we can skip the
 	 * compressed data much more quickly.
 	 */
-	bytes_skipped = skip_stream(a, zip->entry_bytes_remaining);
+	bytes_skipped = skip_stream(a, (size_t)zip->entry_bytes_remaining);
 	if (bytes_skipped < 0)
 		return (ARCHIVE_FATAL);
 	zip->entry_bytes_remaining = 0;
@@ -1054,7 +1060,7 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 		ff = &filters[fi];
 #endif
 		r = lzma_properties_decode(&filters[fi], NULL,
-		    coder1->properties, coder1->propertiesSize);
+		    coder1->properties, (size_t)coder1->propertiesSize);
 		if (r != LZMA_OK) {
 			set_error(a, r);
 			return (ARCHIVE_FAILED);
@@ -1358,9 +1364,9 @@ decompress(struct archive_read *a, struct _7zip *zip,
 #ifdef HAVE_ZLIB_H
 	case _7Z_DEFLATE:
 		zip->stream.next_in = (Bytef *)(uintptr_t)t_next_in;
-		zip->stream.avail_in = t_avail_in;
+		zip->stream.avail_in = (uInt)t_avail_in;
 		zip->stream.next_out = t_next_out;
-		zip->stream.avail_out = t_avail_out;
+		zip->stream.avail_out = (uInt)t_avail_out;
 		r = inflate(&(zip->stream), 0);
 		switch (r) {
 		case Z_STREAM_END: /* Found end of stream. */
@@ -1382,7 +1388,7 @@ decompress(struct archive_read *a, struct _7zip *zip,
 		uint64_t flush_bytes;
 
 		if (!zip->ppmd7_valid || zip->ppmd7_stat < 0 ||
-		    t_avail_in < 0 || t_avail_out <= 0) {
+		    t_avail_out <= 0) {
 			archive_set_error(&(a->archive),
 			    ARCHIVE_ERRNO_MISC,
 			    "Decompression internal error");
@@ -1442,8 +1448,8 @@ decompress(struct archive_read *a, struct _7zip *zip,
 		} while (zip->ppstream.avail_out &&
 			(zip->ppstream.avail_in || flush_bytes));
 
-		t_avail_in = zip->ppstream.avail_in;
-		t_avail_out = zip->ppstream.avail_out;
+		t_avail_in = (size_t)zip->ppstream.avail_in;
+		t_avail_out = (size_t)zip->ppstream.avail_out;
 		break;
 	}
 	default:
@@ -1506,6 +1512,10 @@ free_decompression(struct archive_read *a, struct _7zip *zip)
 {
 	int r = ARCHIVE_OK;
 
+#if !defined(HAVE_ZLIB_H) &&\
+	!(defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR))
+	(void)a;/* UNUSED */
+#endif
 #ifdef HAVE_LZMA_H
 	if (zip->lzstream_valid)
 		lzma_end(&(zip->lzstream));
@@ -1598,9 +1608,10 @@ read_Digests(struct archive_read *a, struct _7z_digests *d, size_t num)
 	const unsigned char *p;
 	unsigned i;
 
+	if (num == 0)
+		return (-1);
 	memset(d, 0, sizeof(*d));
 
-
 	d->defineds = malloc(num);
 	if (d->defineds == NULL)
 		return (-1);
@@ -1672,8 +1683,8 @@ read_PackInfo(struct archive_read *a, struct _7z_pack_info *pi)
 		return (0);
 	if (*p != kSize)
 		return (-1);
-	pi->sizes = calloc(pi->numPackStreams, sizeof(uint64_t));
-	pi->positions = calloc(pi->numPackStreams, sizeof(uint64_t));
+	pi->sizes = calloc((size_t)pi->numPackStreams, sizeof(uint64_t));
+	pi->positions = calloc((size_t)pi->numPackStreams, sizeof(uint64_t));
 	if (pi->sizes == NULL || pi->positions == NULL)
 		return (-1);
 
@@ -1690,9 +1701,9 @@ read_PackInfo(struct archive_read *a, struct _7z_pack_info *pi)
 	if (*p == kEnd) {
 		/* PackStreamDigests[num] are not present. */
 		pi->digest.defineds =
-		    calloc(pi->numPackStreams, sizeof(*pi->digest.defineds));
+		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.defineds));
 		pi->digest.digests =
-		    calloc(pi->numPackStreams, sizeof(*pi->digest.digests));
+		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.digests));
 		if (pi->digest.defineds == NULL || pi->digest.digests == NULL)
 			return (-1);
 		return (0);
@@ -1701,7 +1712,7 @@ read_PackInfo(struct archive_read *a, struct _7z_pack_info *pi)
 	if (*p != kSize)
 		return (-1);
 
-	if (read_Digests(a, &(pi->digest), pi->numPackStreams) < 0)
+	if (read_Digests(a, &(pi->digest), (size_t)pi->numPackStreams) < 0)
 		return (-1);
 
 	/*
@@ -1750,7 +1761,7 @@ read_Folder(struct archive_read *a, struct _7z_folder *f)
 		/* Too many coders. */
 		return (-1);
 
-	f->coders = calloc(f->numCoders, sizeof(*f->coders));
+	f->coders = calloc((size_t)f->numCoders, sizeof(*f->coders));
 	if (f->coders == NULL)
 		return (-1);
 	for (i = 0; i< f->numCoders; i++) {
@@ -1802,14 +1813,14 @@ read_Folder(struct archive_read *a, struct _7z_folder *f)
 			    a, &(f->coders[i].propertiesSize)) < 0)
 				return (-1);
 			if ((p = header_bytes(
-			    a, f->coders[i].propertiesSize)) == NULL)
+			    a, (size_t)f->coders[i].propertiesSize)) == NULL)
 				return (-1);
 			f->coders[i].properties =
-			    malloc(f->coders[i].propertiesSize);
+			    malloc((size_t)f->coders[i].propertiesSize);
 			if (f->coders[i].properties == NULL)
 				return (-1);
 			memcpy(f->coders[i].properties, p,
-			    f->coders[i].propertiesSize);
+			    (size_t)f->coders[i].propertiesSize);
 		}
 
 		numInStreamsTotal += f->coders[i].numInStreams;
@@ -1823,9 +1834,13 @@ read_Folder(struct archive_read *a, struct _7z_folder *f)
 	f->numBindPairs = numOutStreamsTotal - 1;
 	if (zip->header_bytes_remaining < f->numBindPairs)
 			return (-1);
-	f->bindPairs = calloc(f->numBindPairs, sizeof(*f->bindPairs));
-	if (f->bindPairs == NULL)
-		return (-1);
+	if (f->numBindPairs > 0) {
+		f->bindPairs =
+			calloc((size_t)f->numBindPairs, sizeof(*f->bindPairs));
+		if (f->bindPairs == NULL)
+			return (-1);
+	} else
+		f->bindPairs = NULL;
 	for (i = 0; i < f->numBindPairs; i++) {
 		if (parse_7zip_uint64(a, &(f->bindPairs[i].inIndex)) < 0)
 			return (-1);
@@ -1839,7 +1854,7 @@ read_Folder(struct archive_read *a, struct _7z_folder *f)
 
 	f->numPackedStreams = numInStreamsTotal - f->numBindPairs;
 	f->packedStreams =
-	    calloc(f->numPackedStreams, sizeof(*f->packedStreams));
+	    calloc((size_t)f->numPackedStreams, sizeof(*f->packedStreams));
 	if (f->packedStreams == NULL)
 		return (-1);
 	if (f->numPackedStreams == 1) {
@@ -1911,7 +1926,8 @@ read_CodersInfo(struct archive_read *a, struct _7z_coders_info *ci)
 		goto failed;
 	switch (*p) {
 	case 0:
-		ci->folders = calloc(ci->numFolders, sizeof(*ci->folders));
+		ci->folders =
+			calloc((size_t)ci->numFolders, sizeof(*ci->folders));
 		if (ci->folders == NULL)
 			return (-1);
 		for (i = 0; i < ci->numFolders; i++) {
@@ -1937,7 +1953,7 @@ read_CodersInfo(struct archive_read *a, struct _7z_coders_info *ci)
 		unsigned j;
 
 		folder->unPackSize =
-		    calloc(folder->numOutStreams, sizeof(*folder->unPackSize));
+		    calloc((size_t)folder->numOutStreams, sizeof(*folder->unPackSize));
 		if (folder->unPackSize == NULL)
 			goto failed;
 		for (j = 0; j < folder->numOutStreams; j++) {
@@ -1955,7 +1971,7 @@ read_CodersInfo(struct archive_read *a, struct _7z_coders_info *ci)
 		return (0);
 	if (*p != kCRC)
 		goto failed;
-	if (read_Digests(a, &digest, ci->numFolders) < 0)
+	if (read_Digests(a, &digest, (size_t)ci->numFolders) < 0)
 		goto failed;
 	for (i = 0; i < ci->numFolders; i++) {
 		ci->folders[i].digest_defined = digest.defineds[i];
@@ -1979,13 +1995,13 @@ read_CodersInfo(struct archive_read *a, struct _7z_coders_info *ci)
 static uint64_t
 folder_uncompressed_size(struct _7z_folder *f)
 {
-	int n = f->numOutStreams;
-	unsigned pairs = f->numBindPairs;
+	int n = (int)f->numOutStreams;
+	unsigned pairs = (unsigned)f->numBindPairs;
 
 	while (--n >= 0) {
 		unsigned i;
 		for (i = 0; i < pairs; i++) {
-			if (f->bindPairs[i].outIndex == n)
+			if (f->bindPairs[i].outIndex == (uint64_t)n)
 				break;
 		}
 		if (i >= pairs)
@@ -2029,7 +2045,7 @@ read_SubStreamsInfo(struct archive_read *a, struct _7z_substream_info *ss,
 				return (-1);
 			if (1000000 < f[i].numUnpackStreams)
 				return (-1);
-			unpack_streams += f[i].numUnpackStreams;
+			unpack_streams += (size_t)f[i].numUnpackStreams;
 		}
 		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
@@ -2083,7 +2099,7 @@ read_SubStreamsInfo(struct archive_read *a, struct _7z_substream_info *ss,
 	numDigests = 0;
 	for (i = 0; i < numFolders; i++) {
 		if (f[i].numUnpackStreams != 1 || !f[i].digest_defined)
-			numDigests += f[i].numUnpackStreams;
+			numDigests += (uint32_t)f[i].numUnpackStreams;
 	}
 
 	if (type == kCRC) {
@@ -2181,7 +2197,7 @@ read_StreamsInfo(struct archive_read *a, struct _7z_stream_info *si)
 		f = si->ci.folders;
 		for (i = 0; i < si->ci.numFolders; i++) {
 			f[i].packIndex = packIndex;
-			packIndex += f[i].numPackedStreams;
+			packIndex += (uint32_t)f[i].numPackedStreams;
 			if (packIndex > si->pi.numPackStreams)
 				return (-1);
 		}
@@ -2191,7 +2207,7 @@ read_StreamsInfo(struct archive_read *a, struct _7z_stream_info *si)
 
 	if (*p == kSubStreamsInfo) {
 		if (read_SubStreamsInfo(a, &(si->ss),
-		    si->ci.folders, si->ci.numFolders) < 0)
+		    si->ci.folders, (size_t)si->ci.numFolders) < 0)
 			return (-1);
 		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
@@ -2279,7 +2295,7 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 	if (1000000 < zip->numFiles)
 			return (-1);
 
-	zip->entries = calloc(zip->numFiles, sizeof(*zip->entries));
+	zip->entries = calloc((size_t)zip->numFiles, sizeof(*zip->entries));
 	if (zip->entries == NULL)
 		return (-1);
 	entries = zip->entries;
@@ -2304,12 +2320,12 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 
 		switch (type) {
 		case kEmptyStream:
-			h->emptyStreamBools = calloc(zip->numFiles,
+			h->emptyStreamBools = calloc((size_t)zip->numFiles,
 			    sizeof(*h->emptyStreamBools));
 			if (h->emptyStreamBools == NULL)
 				return (-1);
 			if (read_Bools(
-			    a, h->emptyStreamBools, zip->numFiles) < 0)
+			    a, h->emptyStreamBools, (size_t)zip->numFiles) < 0)
 				return (-1);
 			empty_streams = 0;
 			for (i = 0; i < zip->numFiles; i++) {
@@ -2318,6 +2334,12 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 			}
 			break;
 		case kEmptyFile:
+			if (empty_streams <= 0) {
+				/* Unexcepted sequence. Skip this. */
+				if (header_bytes(a, ll) == NULL)
+					return (-1);
+				break;
+			}
 			h->emptyFileBools = calloc(empty_streams,
 			    sizeof(*h->emptyFileBools));
 			if (h->emptyFileBools == NULL)
@@ -2326,6 +2348,12 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 				return (-1);
 			break;
 		case kAnti:
+			if (empty_streams <= 0) {
+				/* Unexcepted sequence. Skip this. */
+				if (header_bytes(a, ll) == NULL)
+					return (-1);
+				break;
+			}
 			h->antiBools = calloc(empty_streams,
 			    sizeof(*h->antiBools));
 			if (h->antiBools == NULL)
@@ -2404,15 +2432,15 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 			if ((p = header_bytes(a, 2)) == NULL)
 				return (-1);
 			allAreDefined = *p;
-			h->attrBools = calloc(zip->numFiles,
+			h->attrBools = calloc((size_t)zip->numFiles,
 			    sizeof(*h->attrBools));
 			if (h->attrBools == NULL)
 				return (-1);
 			if (allAreDefined)
-				memset(h->attrBools, 1, zip->numFiles);
+				memset(h->attrBools, 1, (size_t)zip->numFiles);
 			else {
 				if (read_Bools(a, h->attrBools,
-				      zip->numFiles) < 0)
+				      (size_t)zip->numFiles) < 0)
 					return (-1);
 			}
 			for (i = 0; i < zip->numFiles; i++) {
@@ -2446,7 +2474,7 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 			if ((size_t)sindex >= si->ss.unpack_streams)
 				return (-1);
 			if (entries[i].mode == 0)
-				entries[i].mode = AE_IFREG | 0777;
+				entries[i].mode = AE_IFREG | 0666;
 			if (si->ss.digestsDefined[sindex])
 				entries[i].flg |= CRC32_IS_SET;
 			entries[i].ssIndex = sindex;
@@ -2466,7 +2494,7 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 				if (dir)
 					entries[i].mode = AE_IFDIR | 0777;
 				else
-					entries[i].mode = AE_IFREG | 0777;
+					entries[i].mode = AE_IFREG | 0666;
 			} else if (dir &&
 			    (entries[i].mode & AE_IFMT) != AE_IFDIR) {
 				entries[i].mode &= ~AE_IFMT;
@@ -2517,17 +2545,17 @@ read_Header(struct archive_read *a, struct _7z_header_info *h,
 
 #define EPOC_TIME ARCHIVE_LITERAL_ULL(116444736000000000)
 static void
-fileTimeToUtc(uint64_t fileTime, time_t *time, long *ns)
+fileTimeToUtc(uint64_t fileTime, time_t *timep, long *ns)
 {
 
 	if (fileTime >= EPOC_TIME) {
 		fileTime -= EPOC_TIME;
 		/* milli seconds base */
-		*time = (time_t)(fileTime / 10000000);
+		*timep = (time_t)(fileTime / 10000000);
 		/* nano seconds base */
 		*ns = (long)(fileTime % 10000000) * 100;
 	} else {
-		*time = 0;
+		*timep = 0;
 		*ns = 0;
 	}
 }
@@ -2542,7 +2570,7 @@ read_Times(struct archive_read *a, struct _7z_header_info *h, int type)
 	int allAreDefined;
 	unsigned i;
 
-	timeBools = calloc(zip->numFiles, sizeof(*timeBools));
+	timeBools = calloc((size_t)zip->numFiles, sizeof(*timeBools));
 	if (timeBools == NULL)
 		return (-1);
 
@@ -2551,9 +2579,9 @@ read_Times(struct archive_read *a, struct _7z_header_info *h, int type)
 		goto failed;
 	allAreDefined = *p;
 	if (allAreDefined)
-		memset(timeBools, 1, zip->numFiles);
+		memset(timeBools, 1, (size_t)zip->numFiles);
 	else {
-		if (read_Bools(a, timeBools, zip->numFiles) < 0)
+		if (read_Bools(a, timeBools, (size_t)zip->numFiles) < 0)
 			goto failed;
 	}
 
@@ -2564,7 +2592,7 @@ read_Times(struct archive_read *a, struct _7z_header_info *h, int type)
 		if (parse_7zip_uint64(a, &(h->dataIndex)) < 0)
 			goto failed;
 		if (1000000 < h->dataIndex)
-			return (-1);
+			goto failed;
 	}
 
 	for (i = 0; i < zip->numFiles; i++) {
@@ -2661,7 +2689,7 @@ header_bytes(struct archive_read *a, size_t rbytes)
 	}
 
 	/* Update checksum */
-	zip->header_crc32 = crc32(zip->header_crc32, p, rbytes);
+	zip->header_crc32 = crc32(zip->header_crc32, p, (unsigned)rbytes);
 	return (p);
 }
 
@@ -2695,7 +2723,8 @@ slurp_central_directory(struct archive_read *a, struct _7zip *zip,
 	}
 
 	/* CRC check. */
-	if (crc32(0, (unsigned char *)p + 12, 20) != archive_le32dec(p + 8)) {
+	if (crc32(0, (const unsigned char *)p + 12, 20)
+	    != archive_le32dec(p + 8)) {
 		archive_set_error(&a->archive, -1, "Header CRC error");
 		return (ARCHIVE_FATAL);
 	}
@@ -2714,7 +2743,7 @@ slurp_central_directory(struct archive_read *a, struct _7zip *zip,
 	}
 	__archive_read_consume(a, 32);
 	if (next_header_offset != 0) {
-		if (bytes_avail >= next_header_offset)
+		if (bytes_avail >= (ssize_t)next_header_offset)
 			__archive_read_consume(a, next_header_offset);
 		else if (__archive_read_seek(a,
 		    next_header_offset + zip->seek_base, SEEK_SET) < 0)
@@ -2827,7 +2856,7 @@ get_uncompressed_data(struct archive_read *a, const void **buff, size_t size,
 	struct _7zip *zip = (struct _7zip *)a->format->data;
 	ssize_t bytes_avail;
 
-	if (zip->codec == _7Z_COPY && zip->codec2 == -1) {
+	if (zip->codec == _7Z_COPY && zip->codec2 == (unsigned long)-1) {
 		/* Copy mode. */
 
 		/*
@@ -2886,7 +2915,7 @@ extract_pack_stream(struct archive_read *a, size_t minimum)
 	ssize_t bytes_avail;
 	int r;
 
-	if (zip->codec == _7Z_COPY && zip->codec2 == -1) {
+	if (zip->codec == _7Z_COPY && zip->codec2 == (unsigned long)-1) {
 		if (minimum == 0)
 			minimum = 1;
 		if (__archive_read_ahead(a, minimum, &bytes_avail) == NULL
@@ -2896,11 +2925,11 @@ extract_pack_stream(struct archive_read *a, size_t minimum)
 			    "Truncated 7-Zip file body");
 			return (ARCHIVE_FATAL);
 		}
-		if (bytes_avail > zip->pack_stream_inbytes_remaining)
-			bytes_avail = zip->pack_stream_inbytes_remaining;
+		if (bytes_avail > (ssize_t)zip->pack_stream_inbytes_remaining)
+			bytes_avail = (ssize_t)zip->pack_stream_inbytes_remaining;
 		zip->pack_stream_inbytes_remaining -= bytes_avail;
-		if (bytes_avail > zip->folder_outbytes_remaining)
-			bytes_avail = zip->folder_outbytes_remaining;
+		if (bytes_avail > (ssize_t)zip->folder_outbytes_remaining)
+			bytes_avail = (ssize_t)zip->folder_outbytes_remaining;
 		zip->folder_outbytes_remaining -= bytes_avail;
 		zip->uncompressed_buffer_bytes_remaining = bytes_avail;
 		return (ARCHIVE_OK);
@@ -2939,16 +2968,19 @@ extract_pack_stream(struct archive_read *a, size_t minimum)
 			 * Expand the uncompressed buffer up to
 			 * the minimum size.
 			 */
-			zip->uncompressed_buffer_size = minimum + 1023;
-			zip->uncompressed_buffer_size &= ~0x3ff;
-			zip->uncompressed_buffer =
-			    realloc(zip->uncompressed_buffer,
-				zip->uncompressed_buffer_size);
-			if (zip->uncompressed_buffer == NULL) {
+			void *p;
+			size_t new_size;
+
+			new_size = minimum + 1023;
+			new_size &= ~0x3ff;
+			p = realloc(zip->uncompressed_buffer, new_size);
+			if (p == NULL) {
 				archive_set_error(&a->archive, ENOMEM,
 				    "No memory for 7-Zip decompression");
 				return (ARCHIVE_FATAL);
 			}
+			zip->uncompressed_buffer = (unsigned char *)p;
+			zip->uncompressed_buffer_size = new_size;
 		}
 		/*
 		 * Move unconsumed bytes to the head.
@@ -2965,7 +2997,7 @@ extract_pack_stream(struct archive_read *a, size_t minimum)
 		size_t bytes_in, bytes_out;
 		const void *buff_in;
 		unsigned char *buff_out;
-		int eof;
+		int end_of_data;
 
 		/*
 		 * Note: '1' here is a performance optimization.
@@ -2987,23 +3019,23 @@ extract_pack_stream(struct archive_read *a, size_t minimum)
 			- zip->uncompressed_buffer_bytes_remaining;
 		bytes_in = bytes_avail;
 		if (bytes_in > zip->pack_stream_inbytes_remaining)
-			bytes_in = zip->pack_stream_inbytes_remaining;
+			bytes_in = (size_t)zip->pack_stream_inbytes_remaining;
 		/* Drive decompression. */
 		r = decompress(a, zip, buff_out, &bytes_out,
 			buff_in, &bytes_in);
 		switch (r) {
 		case ARCHIVE_OK:
-			eof = 0;
+			end_of_data = 0;
 			break;
 		case ARCHIVE_EOF:
-			eof = 1;
+			end_of_data = 1;
 			break;
 		default:
 			return (ARCHIVE_FATAL);
 		}
 		zip->pack_stream_inbytes_remaining -= bytes_in;
 		if (bytes_out > zip->folder_outbytes_remaining)
-			bytes_out = zip->folder_outbytes_remaining;
+			bytes_out = (size_t)zip->folder_outbytes_remaining;
 		zip->folder_outbytes_remaining -= bytes_out;
 		zip->uncompressed_buffer_bytes_remaining += bytes_out;
 		zip->pack_stream_bytes_unconsumed = bytes_in;
@@ -3021,7 +3053,7 @@ extract_pack_stream(struct archive_read *a, size_t minimum)
 		if (zip->pack_stream_inbytes_remaining == 0 &&
 		    zip->folder_outbytes_remaining == 0)
 			break;
-		if (eof || (bytes_in == 0 && bytes_out == 0)) {
+		if (end_of_data || (bytes_in == 0 && bytes_out == 0)) {
 			archive_set_error(&(a->archive),
 			    ARCHIVE_ERRNO_MISC, "Damaged 7-Zip archive");
 			return (ARCHIVE_FATAL);
@@ -3041,7 +3073,7 @@ static int
 seek_pack(struct archive_read *a)
 {
 	struct _7zip *zip = (struct _7zip *)a->format->data;
-	uint64_t pack_offset;
+	int64_t pack_offset;
 
 	if (zip->pack_stream_remaining <= 0) {
 		archive_set_error(&(a->archive),
@@ -3068,7 +3100,7 @@ read_stream(struct archive_read *a, const void **buff, size_t size,
 {
 	struct _7zip *zip = (struct _7zip *)a->format->data;
 	uint64_t skip_bytes = 0;
-	int r;
+	ssize_t r;
 
 	if (zip->uncompressed_buffer_bytes_remaining == 0) {
 		if (zip->pack_stream_inbytes_remaining > 0) {
@@ -3160,7 +3192,8 @@ read_stream(struct archive_read *a, const void **buff, size_t size,
 				return (ARCHIVE_FATAL);
 			}
 		}
-		skipped = get_uncompressed_data(a, buff, skip_bytes, 0);
+		skipped = get_uncompressed_data(
+			a, buff, (size_t)skip_bytes, 0);
 		if (skipped < 0)
 			return (skipped);
 		skip_bytes -= skipped;
@@ -3292,13 +3325,13 @@ setup_decode_folder(struct archive_read *a, struct _7z_folder *folder,
 			}
 			coder2 = &(fc[3]);
 			zip->main_stream_bytes_remaining =
-				folder->unPackSize[2];
+				(size_t)folder->unPackSize[2];
 		} else if (coder2 != NULL && coder2->codec == _7Z_X86_BCJ2 &&
 		    zip->pack_stream_remaining == 4 &&
 		    folder->numInStreams == 5 && folder->numOutStreams == 2) {
 			/* Source type 0 made by 7z */
 			zip->main_stream_bytes_remaining =
-				folder->unPackSize[0];
+				(size_t)folder->unPackSize[0];
 		} else {
 			/* We got an unexpected form. */
 			archive_set_error(&(a->archive),
@@ -3311,45 +3344,54 @@ setup_decode_folder(struct archive_read *a, struct _7z_folder *folder,
 		if ((r = seek_pack(a)) < 0)
 			return (r);
 		zip->pack_stream_bytes_unconsumed =
-		    zip->pack_stream_inbytes_remaining;
+		    (size_t)zip->pack_stream_inbytes_remaining;
 		read_consume(a);
 
 		/* Read following three sub streams. */
 		for (i = 0; i < 3; i++) {
 			const struct _7z_coder *coder = scoder[i];
 
-			if ((r = seek_pack(a)) < 0)
+			if ((r = seek_pack(a)) < 0) {
+				free(b[0]); free(b[1]); free(b[2]);
 				return (r);
+			}
 
-			if (sunpack[i] == -1)
+			if (sunpack[i] == (uint64_t)-1)
 				zip->folder_outbytes_remaining =
 				    zip->pack_stream_inbytes_remaining;
 			else
 				zip->folder_outbytes_remaining = sunpack[i];
 
 			r = init_decompression(a, zip, coder, NULL);
-			if (r != ARCHIVE_OK)
+			if (r != ARCHIVE_OK) {
+				free(b[0]); free(b[1]); free(b[2]);
 				return (ARCHIVE_FATAL);
+			}
 
 			/* Allocate memory for the decorded data of a sub
 			 * stream. */
-			b[i] = malloc(zip->folder_outbytes_remaining);
+			b[i] = malloc((size_t)zip->folder_outbytes_remaining);
 			if (b[i] == NULL) {
+				free(b[0]); free(b[1]); free(b[2]);
 				archive_set_error(&a->archive, ENOMEM,
 				    "No memory for 7-Zip decompression");
 				return (ARCHIVE_FATAL);
 			}
 
 			/* Extract a sub stream. */
 			while (zip->pack_stream_inbytes_remaining > 0) {
-				r = extract_pack_stream(a, 0);
-				if (r < 0)
+				r = (int)extract_pack_stream(a, 0);
+				if (r < 0) {
+					free(b[0]); free(b[1]); free(b[2]);
 					return (r);
+				}
 				bytes = get_uncompressed_data(a, &buff,
 				    zip->uncompressed_buffer_bytes_remaining,
 				    0);
-				if (bytes < 0)
+				if (bytes < 0) {
+					free(b[0]); free(b[1]); free(b[2]);
 					return ((int)bytes);
+				}
 				memcpy(b[i]+s[i], buff, bytes);
 				s[i] += bytes;
 				if (zip->pack_stream_bytes_unconsumed)
@@ -3428,7 +3470,7 @@ skip_stream(struct archive_read *a, size_t skip_bytes)
 			    "Truncated 7-Zip file body");
 			return (ARCHIVE_FATAL);
 		}
-		bytes -= skipped_bytes;
+		bytes -= (size_t)skipped_bytes;
 		if (zip->pack_stream_bytes_unconsumed)
 			read_consume(a);
 	}
@@ -3506,16 +3548,16 @@ x86_Convert(struct _7zip *zip, uint8_t *data, size_t size)
 			uint32_t dest;
 			for (;;) {
 				uint8_t b;
-				int index;
+				int b_index;
 
 				dest = src - (ip + (uint32_t)bufferPos);
 				if (prevMask == 0)
 					break;
-				index = kMaskToBitNumber[prevMask] * 8;
-				b = (uint8_t)(dest >> (24 - index));
+				b_index = kMaskToBitNumber[prevMask] * 8;
+				b = (uint8_t)(dest >> (24 - b_index));
 				if (!Test86MSByte(b))
 					break;
-				src = dest ^ ((1 << (32 - index)) - 1);
+				src = dest ^ ((1 << (32 - b_index)) - 1);
 			}
 			p[4] = (uint8_t)(~(((dest >> 24) & 1) - 1));
 			p[3] = (uint8_t)(dest >> 16);
@@ -3529,7 +3571,7 @@ x86_Convert(struct _7zip *zip, uint8_t *data, size_t size)
 	}
 	zip->bcj_prevPosT = prevPosT;
 	zip->bcj_prevMask = prevMask;
-	zip->bcj_ip += bufferPos;
+	zip->bcj_ip += (uint32_t)bufferPos;
 	return (bufferPos);
 }
 
@@ -3556,7 +3598,7 @@ x86_Convert(struct _7zip *zip, uint8_t *data, size_t size)
 #define RC_READ_BYTE (*buffer++)
 #define RC_TEST { if (buffer == bufferLim) return SZ_ERROR_DATA; }
 #define RC_INIT2 zip->bcj2_code = 0; zip->bcj2_range = 0xFFFFFFFF; \
-  { int i; for (i = 0; i < 5; i++) { RC_TEST; zip->bcj2_code = (zip->bcj2_code << 8) | RC_READ_BYTE; }}
+  { int ii; for (ii = 0; ii < 5; ii++) { RC_TEST; zip->bcj2_code = (zip->bcj2_code << 8) | RC_READ_BYTE; }}
 
 #define NORMALIZE if (zip->bcj2_range < kTopValue) { RC_TEST; zip->bcj2_range <<= 8; zip->bcj2_code = (zip->bcj2_code << 8) | RC_READ_BYTE; }
 
@@ -3622,14 +3664,14 @@ Bcj2_Decode(struct _7zip *zip, uint8_t *outBuf, size_t outSize)
 
 		if (zip->bcj_state == 1) {
 			while (limit != 0) {
-				uint8_t b = buf0[inPos];
-				outBuf[outPos++] = b;
-				if (IsJ(zip->bcj2_prevByte, b)) {
+				uint8_t bb = buf0[inPos];
+				outBuf[outPos++] = bb;
+				if (IsJ(zip->bcj2_prevByte, bb)) {
 					zip->bcj_state = 2;
 					break;
 				}
 				inPos++;
-				zip->bcj2_prevByte = b;
+				zip->bcj2_prevByte = bb;
 				limit--;
 			}
 		}
@@ -3673,7 +3715,7 @@ Bcj2_Decode(struct _7zip *zip, uint8_t *outBuf, size_t outSize)
 			    ((uint32_t)v[1] << 16) |
 			    ((uint32_t)v[2] << 8) |
 			    ((uint32_t)v[3])) -
-			    ((uint32_t)zip->bcj2_outPos + outPos + 4);
+			    ((uint32_t)zip->bcj2_outPos + (uint32_t)outPos + 4);
 			out[0] = (uint8_t)dest;
 			out[1] = (uint8_t)(dest >> 8);
 			out[2] = (uint8_t)(dest >> 16);
@@ -3688,7 +3730,7 @@ Bcj2_Decode(struct _7zip *zip, uint8_t *outBuf, size_t outSize)
 				 */
 				zip->odd_bcj_size = 4 -i;
 				for (; i < 4; i++) {
-					j = i - 4 + zip->odd_bcj_size;
+					j = i - 4 + (unsigned)zip->odd_bcj_size;
 					zip->odd_bcj[j] = out[i];
 				}
 				break;