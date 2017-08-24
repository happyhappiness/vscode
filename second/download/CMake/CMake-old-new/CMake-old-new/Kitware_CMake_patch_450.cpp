@@ -204,6 +204,10 @@ struct _7zip {
 	/* Structural information about the archive. */
 	struct _7z_stream_info	 si;
 
+	int			 header_is_being_read;
+	int			 header_is_encoded;
+	uint64_t		 header_bytes_remaining;
+	unsigned long		 header_crc32;
 	/* Header offset to check that reading pointes of the file contens
 	 * will not exceed the header. */
 	uint64_t		 header_offset;
@@ -228,6 +232,7 @@ struct _7zip {
 	char			 end_of_entry;
 
 	/* Uncompressed buffer control.  */
+#define UBUFF_SIZE	(64 * 1024)
 	unsigned char 		*uncompressed_buffer;
 	unsigned char 		*uncompressed_buffer_pointer;
 	size_t 			 uncompressed_buffer_size;
@@ -288,6 +293,10 @@ struct _7zip {
 	uint32_t		 bcj_state;
 	size_t			 odd_bcj_size;
 	unsigned char		 odd_bcj[4];
+	/* Decoding BCJ data. */
+	size_t			 bcj_prevPosT;
+	uint32_t		 bcj_prevMask;
+	uint32_t		 bcj_ip;
 
 	/* Decoding BCJ2 data. */
 	size_t			 main_stream_bytes_remaining;
@@ -324,12 +333,11 @@ static int	archive_read_format_7zip_read_header(struct archive_read *,
 		    struct archive_entry *);
 static int	check_7zip_header_in_sfx(const char *);
 static unsigned long decode_codec_id(const unsigned char *, size_t);
-static ssize_t	decode_header_image(struct archive_read *, struct _7zip *,
-		    struct _7z_stream_info *, const unsigned char *, uint64_t,
-		    const void **);
+static int	decode_encoded_header_info(struct archive_read *,
+		    struct _7z_stream_info *);
 static int	decompress(struct archive_read *, struct _7zip *,
 		    void *, size_t *, const void *, size_t *);
-static ssize_t	extract_pack_stream(struct archive_read *);
+static ssize_t	extract_pack_stream(struct archive_read *, size_t);
 static void	fileTimeToUtc(uint64_t, time_t *, long *);
 static uint64_t folder_uncompressed_size(struct _7z_folder *);
 static void	free_CodersInfo(struct _7z_coders_info *);
@@ -341,39 +349,39 @@ static void	free_StreamsInfo(struct _7z_stream_info *);
 static void	free_SubStreamsInfo(struct _7z_substream_info *);
 static int	free_decompression(struct archive_read *, struct _7zip *);
 static ssize_t	get_uncompressed_data(struct archive_read *, const void **,
-		    size_t);
+		    size_t, size_t);
+static const unsigned char * header_bytes(struct archive_read *, size_t);
 static int	init_decompression(struct archive_read *, struct _7zip *,
 		    const struct _7z_coder *, const struct _7z_coder *);
-static int	parse_7zip_uint64(const unsigned char *, size_t, uint64_t *);
-static int	read_Bools(unsigned char *, size_t, const unsigned char *,
-		    size_t);
-static int	read_CodersInfo(struct _7z_coders_info *,
-		    const unsigned char *, size_t);
-static int	read_Digests(struct _7z_digests *, size_t,
-		    const unsigned char *, size_t);
-static int	read_Folder(struct _7z_folder *, const unsigned char *,
-		    size_t);
-static int	read_Header(struct _7zip *, struct _7z_header_info *,
-		    const unsigned char *, size_t);
-static int	read_PackInfo(struct _7z_pack_info *, const unsigned char *,
+static int	parse_7zip_uint64(struct archive_read *, uint64_t *);
+static int	read_Bools(struct archive_read *, unsigned char *, size_t);
+static int	read_CodersInfo(struct archive_read *,
+		    struct _7z_coders_info *);
+static int	read_Digests(struct archive_read *, struct _7z_digests *,
 		    size_t);
-static int	read_StreamsInfo(struct _7zip *, struct _7z_stream_info *,
-		    const unsigned char *, size_t);
-static int	read_SubStreamsInfo(struct _7z_substream_info *,
-		    struct _7z_folder *, size_t, const unsigned char *,
-		    size_t);
-static int	read_Times(struct _7zip *, struct _7z_header_info *, int,
-		    const unsigned char *, size_t);
+static int	read_Folder(struct archive_read *, struct _7z_folder *);
+static int	read_Header(struct archive_read *, struct _7z_header_info *,
+		    int);
+static int	read_PackInfo(struct archive_read *, struct _7z_pack_info *);
+static int	read_StreamsInfo(struct archive_read *,
+		    struct _7z_stream_info *);
+static int	read_SubStreamsInfo(struct archive_read *,
+		    struct _7z_substream_info *, struct _7z_folder *, size_t);
+static int	read_Times(struct archive_read *, struct _7z_header_info *,
+		    int);
 static void	read_consume(struct archive_read *);
-static ssize_t	read_stream(struct archive_read *, const void **, size_t);
+static ssize_t	read_stream(struct archive_read *, const void **, size_t,
+		    size_t);
+static int	seek_pack(struct archive_read *);
 static int64_t	skip_stream(struct archive_read *, size_t);
 static int	skip_sfx(struct archive_read *, ssize_t);
 static int	slurp_central_directory(struct archive_read *, struct _7zip *,
 		    struct _7z_header_info *);
 static int	setup_decode_folder(struct archive_read *, struct _7z_folder *,
 		    int);
-static size_t	x86_Convert(uint8_t *, size_t, uint32_t, uint32_t *);
-ssize_t		Bcj2_Decode(struct _7zip *, uint8_t *, size_t);
+static void	x86_Init(struct _7zip *);
+static size_t	x86_Convert(struct _7zip *, uint8_t *, size_t);
+static ssize_t		Bcj2_Decode(struct _7zip *, uint8_t *, size_t);
 
 
 int
@@ -641,16 +649,16 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 		int r;
 
 		/*
-		 * Symbolic-name is recorded as its contents. We have to read the
-		 * contents at this time.
+		 * Symbolic-name is recorded as its contents. We have to
+		 * read the contents at this time.
 		 */
 		while (zip->entry_bytes_remaining > 0) {
 			const void *buff;
 			size_t size;
 			int64_t offset;
 
-			r = archive_read_format_7zip_read_data(a, &buff, &size,
-				&offset);
+			r = archive_read_format_7zip_read_data(a, &buff,
+				&size, &offset);
 			if (r < ARCHIVE_WARN)
 				return (r);
 			symname = realloc(symname, symsize + size + 1);
@@ -663,13 +671,15 @@ archive_read_format_7zip_read_header(struct archive_read *a,
 			symsize += size;
 		}
 		if (symsize == 0) {
-			/* If there is no synname, handle it as a regular file. */
+			/* If there is no synname, handle it as a regular
+			 * file. */
 			zip_entry->mode &= ~AE_IFMT;
 			zip_entry->mode |= AE_IFREG;
 			archive_entry_set_mode(entry, zip_entry->mode);
 		} else {
 			symname[symsize] = '\0';
-			archive_entry_copy_symlink(entry, (const char *)symname);
+			archive_entry_copy_symlink(entry,
+			    (const char *)symname);
 			free(symname);
 		}
 		archive_entry_set_size(entry, 0);
@@ -706,7 +716,7 @@ archive_read_format_7zip_read_data(struct archive_read *a,
 		return (ARCHIVE_EOF);
 	}
 
-	bytes = read_stream(a, buff, zip->entry_bytes_remaining);
+	bytes = read_stream(a, buff, zip->entry_bytes_remaining, 0);
 	if (bytes < 0)
 		return ((int)bytes);
 	if (bytes == 0) {
@@ -929,6 +939,8 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 			}
 			zip->codec2 = coder2->codec;
 			zip->bcj_state = 0;
+			if (coder2->codec == _7Z_X86)
+				x86_Init(zip);
 		}
 		break;
 	default:
@@ -990,7 +1002,7 @@ init_decompression(struct archive_read *a, struct _7zip *zip,
 					fi++;
 				} else
 					/* Use our filter. */
-					zip->bcj_state = 0;
+					x86_Init(zip);
 				break;
 			case _7Z_X86_BCJ2:
 				/* Use our filter. */
@@ -1213,6 +1225,14 @@ decompress(struct archive_read *a, struct _7zip *zip,
 
 	if (zip->codec != _7Z_LZMA2 && zip->codec2 == _7Z_X86) {
 		int i;
+
+		/* Do not copy out the BCJ remaining bytes when the output
+		 * buffer size is less than five bytes. */
+		if (o_avail_in != 0 && t_avail_out < 5 && zip->odd_bcj_size) {
+			*used = 0;
+			*outbytes = 0;
+			return (ret);
+		}
 		for (i = 0; zip->odd_bcj_size > 0 && t_avail_out; i++) {
 			*t_next_out++ = zip->odd_bcj[i];
 			t_avail_out--;
@@ -1233,7 +1253,7 @@ decompress(struct archive_read *a, struct _7zip *zip,
 		/*
 		 * Decord a remaining decompressed main stream for BCJ2.
 		 */
-		if (zip->tmp_stream_bytes_remaining > 0) {
+		if (zip->tmp_stream_bytes_remaining) {
 			ssize_t bytes;
 			size_t remaining = zip->tmp_stream_bytes_remaining;
 			bytes = Bcj2_Decode(zip, t_next_out, t_avail_out);
@@ -1249,7 +1269,8 @@ decompress(struct archive_read *a, struct _7zip *zip,
 			if (o_avail_in == 0 || t_avail_out == 0) {
 				*used = 0;
 				*outbytes = o_avail_out - t_avail_out;
-				if (o_avail_in == 0)
+				if (o_avail_in == 0 &&
+				    zip->tmp_stream_bytes_remaining)
 					ret = ARCHIVE_EOF;
 				return (ret);
 			}
@@ -1440,7 +1461,7 @@ decompress(struct archive_read *a, struct _7zip *zip,
 	 * Decord BCJ.
 	 */
 	if (zip->codec != _7Z_LZMA2 && zip->codec2 == _7Z_X86) {
-		size_t l = x86_Convert(buff, *outbytes, 0, &(zip->bcj_state));
+		size_t l = x86_Convert(zip, buff, *outbytes);
 		zip->odd_bcj_size = *outbytes - l;
 		if (zip->odd_bcj_size > 0 && zip->odd_bcj_size <= 4 &&
 		    o_avail_in && ret != ARCHIVE_EOF) {
@@ -1520,49 +1541,48 @@ free_decompression(struct archive_read *a, struct _7zip *zip)
 }
 
 static int
-parse_7zip_uint64(const unsigned char *p, size_t len, uint64_t *val)
+parse_7zip_uint64(struct archive_read *a, uint64_t *val)
 {
-	const unsigned char *_p = p;
+	const unsigned char *p;
 	unsigned char avail, mask;
 	int i;
 
-	if (len-- == 0)
+	if ((p = header_bytes(a, 1)) == NULL)
 		return (-1);
-	avail = *p++;
+	avail = *p;
 	mask = 0x80;
 	*val = 0;
 	for (i = 0; i < 8; i++) {
 		if (avail & mask) {
-			if (len-- == 0)
+			if ((p = header_bytes(a, 1)) == NULL)
 				return (-1);
-			*val |= ((uint64_t)*p++) << (8 * i);
+			*val |= ((uint64_t)*p) << (8 * i);
 			mask >>= 1;
 			continue;
 		}
 		*val += (avail & (mask -1)) << (8 * i);
 		break;
 	}
-	return (p - _p);
+	return (0);
 }
 
 static int
-read_Bools(unsigned char *data, size_t num, const unsigned char *p, size_t len)
+read_Bools(struct archive_read *a, unsigned char *data, size_t num)
 {
-	const unsigned char *_p = p;
-	unsigned i, mask = 0, avail;
+	const unsigned char *p;
+	unsigned i, mask = 0, avail = 0;
 
 	for (i = 0; i < num; i++) {
 		if (mask == 0) {
-			if (len == 0)
+			if ((p = header_bytes(a, 1)) == NULL)
 				return (-1);
-			avail = *p++;
-			len--;
+			avail = *p;
 			mask = 0x80;
 		}
 		data[i] = (avail & mask)?1:0;
 		mask >>= 1;
 	}
-	return (p - _p);
+	return (0);
 }
 
 static void
@@ -1573,48 +1593,41 @@ free_Digest(struct _7z_digests *d)
 }
 
 static int
-read_Digests(struct _7z_digests *d, size_t num, const unsigned char *p,
-    size_t len)
+read_Digests(struct archive_read *a, struct _7z_digests *d, size_t num)
 {
-	const unsigned char *_p = p;
+	const unsigned char *p;
 	unsigned i;
 
 	memset(d, 0, sizeof(*d));
 
-	if (len == 0)
-		return (-1);
 
 	d->defineds = malloc(num);
 	if (d->defineds == NULL)
 		return (-1);
 	/*
 	 * Read Bools.
 	 */
-	len--;
-	if (*p++ == 0) {
-		int r = read_Bools(d->defineds, num, p, len);
-		if (r < 0)
+	if ((p = header_bytes(a, 1)) == NULL)
+		return (-1);
+	if (*p == 0) {
+		if (read_Bools(a, d->defineds, num) < 0)
 			return (-1);
-		p += r;
-		len -= r;
 	} else
 		/* All are defined */
 		memset(d->defineds, 1, num);
 
 	d->digests = calloc(num, sizeof(*d->digests));
 	if (d->digests == NULL)
 		return (-1);
-	if (len < 4 * num)
-		return (-1);
 	for (i = 0; i < num; i++) {
 		if (d->defineds[i]) {
+			if ((p = header_bytes(a, 4)) == NULL)
+				return (-1);
 			d->digests[i] = archive_le32dec(p);
-			p += 4;
-			len -= 4;
 		}
 	}
 
-	return (p - _p);
+	return (0);
 }
 
 static void
@@ -1626,88 +1639,79 @@ free_PackInfo(struct _7z_pack_info *pi)
 }
 
 static int
-read_PackInfo(struct _7z_pack_info *pi, const unsigned char *p, size_t len)
+read_PackInfo(struct archive_read *a, struct _7z_pack_info *pi)
 {
-	const unsigned char *_p = p;
+	const unsigned char *p;
 	unsigned i;
-	int r;
 
 	memset(pi, 0, sizeof(*pi));
 
-	if (len < 3 || *p++ != kPackInfo)
-		return (-1);
-	--len;
-
 	/*
 	 * Read PackPos.
 	 */
-	r = parse_7zip_uint64(p, len, &(pi->pos));
-	if (r < 0)
-		return (r);
-	p += r;
-	len -= r;
+	if (parse_7zip_uint64(a, &(pi->pos)) < 0)
+		return (-1);
 
 	/*
 	 * Read NumPackStreams.
 	 */
-	r = parse_7zip_uint64(p, len, &(pi->numPackStreams));
-	if (r < 0 || pi->numPackStreams == 0)
-		return (r);
-	p += r;
-	len -= r;
+	if (parse_7zip_uint64(a, &(pi->numPackStreams)) < 0)
+		return (-1);
+	if (pi->numPackStreams == 0)
+		return (-1);
+	if (1000000 < pi->numPackStreams)
+		return (-1);
 
 	/*
 	 * Read PackSizes[num]
 	 */
-	if (len >= 1 && *p == kEnd)
+	if ((p = header_bytes(a, 1)) == NULL)
+		return (-1);
+	if (*p == kEnd)
 		/* PackSizes[num] are not present. */
-		return (p - _p + 1);
-	if (len < 1 + pi->numPackStreams || *p++ != kSize)
+		return (0);
+	if (*p != kSize)
 		return (-1);
-	--len;
 	pi->sizes = calloc(pi->numPackStreams, sizeof(uint64_t));
 	pi->positions = calloc(pi->numPackStreams, sizeof(uint64_t));
 	if (pi->sizes == NULL || pi->positions == NULL)
 		return (-1);
 
 	for (i = 0; i < pi->numPackStreams; i++) {
-		r = parse_7zip_uint64(p, len, &(pi->sizes[i]));
-		if (r < 0)
+		if (parse_7zip_uint64(a, &(pi->sizes[i])) < 0)
 			return (-1);
-		p += r;
-		len -= r;
 	}
 
 	/*
 	 * Read PackStreamDigests[num]
 	 */
-	if (len >= 1 && *p == kEnd) {
+	if ((p = header_bytes(a, 1)) == NULL)
+		return (-1);
+	if (*p == kEnd) {
 		/* PackStreamDigests[num] are not present. */
 		pi->digest.defineds =
 		    calloc(pi->numPackStreams, sizeof(*pi->digest.defineds));
 		pi->digest.digests =
 		    calloc(pi->numPackStreams, sizeof(*pi->digest.digests));
 		if (pi->digest.defineds == NULL || pi->digest.digests == NULL)
 			return (-1);
-		return (p - _p + 1);
+		return (0);
 	}
 
-	if (len < 1 + pi->numPackStreams || *p++ != kSize)
+	if (*p != kSize)
 		return (-1);
-	--len;
 
-	r = read_Digests(&(pi->digest), pi->numPackStreams, p, len);
-	if (r < 0)
+	if (read_Digests(a, &(pi->digest), pi->numPackStreams) < 0)
 		return (-1);
-	p += r;
-	len -= r;
 
 	/*
 	 *  Must be marked by kEnd.
 	 */
-	if (len == 0 || *p++ != kEnd)
+	if ((p = header_bytes(a, 1)) == NULL)
+		return (-1);
+	if (*p != kEnd)
 		return (-1);
-	return (p - _p);
+	return (0);
 }
 
 static void
@@ -1727,24 +1731,24 @@ free_Folder(struct _7z_folder *f)
 }
 
 static int
-read_Folder(struct _7z_folder *f, const unsigned char *p, size_t len)
+read_Folder(struct archive_read *a, struct _7z_folder *f)
 {
-	const unsigned char *_p = p;
+	struct _7zip *zip = (struct _7zip *)a->format->data;
+	const unsigned char *p;
 	uint64_t numInStreamsTotal = 0;
 	uint64_t numOutStreamsTotal = 0;
-	int r;
 	unsigned i;
 
 	memset(f, 0, sizeof(*f));
 
 	/*
 	 * Read NumCoders.
 	 */
-	r = parse_7zip_uint64(p, len, &(f->numCoders));
-	if (r < 0)
+	if (parse_7zip_uint64(a, &(f->numCoders)) < 0)
+		return (-1);
+	if (f->numCoders > 4)
+		/* Too many coders. */
 		return (-1);
-	p += r;
-	len -= r;
 
 	f->coders = calloc(f->numCoders, sizeof(*f->coders));
 	if (f->coders == NULL)
@@ -1753,7 +1757,7 @@ read_Folder(struct _7z_folder *f, const unsigned char *p, size_t len)
 		size_t codec_size;
 		int simple, attr;
 
-		if (len == 0)
+		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
 		/*
 		 * 0:3 CodecIdSize
@@ -1768,55 +1772,44 @@ read_Folder(struct _7z_folder *f, const unsigned char *p, size_t len)
 		attr = *p & 0x20;
 		if (*p & 0x80)
 			return (-1);/* Not supported. */
-		p++;
-		len--;
 
 		/*
 		 * Read Decompression Method IDs.
 		 */
-		if (len < codec_size)
+		if ((p = header_bytes(a, codec_size)) == NULL)
 			return (-1);
 
 		f->coders[i].codec = decode_codec_id(p, codec_size);
-		p += codec_size;
-		len -= codec_size;
 
 		if (simple) {
 			f->coders[i].numInStreams = 1;
 			f->coders[i].numOutStreams = 1;
 		} else {
-			r = parse_7zip_uint64(p, len,
-			    &(f->coders[i].numInStreams));
-			if (r < 0)
+			if (parse_7zip_uint64(
+			    a, &(f->coders[i].numInStreams)) < 0)
 				return (-1);
-			p += r;
-			len -= r;
-			r = parse_7zip_uint64(p, len,
-			    &(f->coders[i].numOutStreams));
-			if (r < 0)
+			if (1000000 < f->coders[i].numInStreams)
+				return (-1);
+			if (parse_7zip_uint64(
+			    a, &(f->coders[i].numOutStreams)) < 0)
+				return (-1);
+			if (1000000 < f->coders[i].numOutStreams)
 				return (-1);
-			p += r;
-			len -= r;
 		}
 
 		if (attr) {
-			r = parse_7zip_uint64(p, len,
-				&(f->coders[i].propertiesSize));
-			if (r < 0)
+			if (parse_7zip_uint64(
+			    a, &(f->coders[i].propertiesSize)) < 0)
 				return (-1);
-			p += r;
-			len -= r;
-
-			if (len < f->coders[i].propertiesSize)
+			if ((p = header_bytes(
+			    a, f->coders[i].propertiesSize)) == NULL)
 				return (-1);
 			f->coders[i].properties =
 			    malloc(f->coders[i].propertiesSize);
 			if (f->coders[i].properties == NULL)
 				return (-1);
 			memcpy(f->coders[i].properties, p,
 			    f->coders[i].propertiesSize);
-			p += f->coders[i].propertiesSize;
-			len -= f->coders[i].propertiesSize;
 		}
 
 		numInStreamsTotal += f->coders[i].numInStreams;
@@ -1828,20 +1821,20 @@ read_Folder(struct _7z_folder *f, const unsigned char *p, size_t len)
 		return (-1);
 
 	f->numBindPairs = numOutStreamsTotal - 1;
+	if (zip->header_bytes_remaining < f->numBindPairs)
+			return (-1);
 	f->bindPairs = calloc(f->numBindPairs, sizeof(*f->bindPairs));
 	if (f->bindPairs == NULL)
 		return (-1);
 	for (i = 0; i < f->numBindPairs; i++) {
-		r = parse_7zip_uint64(p, len, &(f->bindPairs[i].inIndex));
-		if (r < 0)
+		if (parse_7zip_uint64(a, &(f->bindPairs[i].inIndex)) < 0)
 			return (-1);
-		p += r;
-		len -= r;
-		r = parse_7zip_uint64(p, len, &(f->bindPairs[i].outIndex));
-		if (r < 0)
+		if (1000000 < f->bindPairs[i].inIndex)
+			return (-1);
+		if (parse_7zip_uint64(a, &(f->bindPairs[i].outIndex)) < 0)
+			return (-1);
+		if (1000000 < f->bindPairs[i].outIndex)
 			return (-1);
-		p += r;
-		len -= r;
 	}
 
 	f->numPackedStreams = numInStreamsTotal - f->numBindPairs;
@@ -1864,17 +1857,16 @@ read_Folder(struct _7z_folder *f, const unsigned char *p, size_t len)
 		f->packedStreams[0] = i;
 	} else {
 		for (i = 0; i < f->numPackedStreams; i++) {
-			r = parse_7zip_uint64(p, len, &(f->packedStreams[i]));
-			if (r < 0)
+			if (parse_7zip_uint64(a, &(f->packedStreams[i])) < 0)
+				return (-1);
+			if (1000000 < f->packedStreams[i])
 				return (-1);
-			p += r;
-			len -= r;
 		}
 	}
 	f->numInStreams = numInStreamsTotal;
 	f->numOutStreams = numOutStreamsTotal;
 
-	return (p - _p);
+	return (0);
 }
 
 static void
@@ -1890,65 +1882,55 @@ free_CodersInfo(struct _7z_coders_info *ci)
 }
 
 static int
-read_CodersInfo(struct _7z_coders_info *ci, const unsigned char *p, size_t len)
+read_CodersInfo(struct archive_read *a, struct _7z_coders_info *ci)
 {
-	const unsigned char *_p = p;
+	const unsigned char *p;
 	struct _7z_digests digest;
-	unsigned i, external;
-	int r;
+	unsigned i;
 
 	memset(ci, 0, sizeof(*ci));
 	memset(&digest, 0, sizeof(digest));
 
-	if (len < 3 || *p++ != kUnPackInfo)
+	if ((p = header_bytes(a, 1)) == NULL)
 		goto failed;
-	--len;
-
-	if (len < 3 || *p++ != kFolder)
+	if (*p != kFolder)
 		goto failed;
-	--len;
 
 	/*
 	 * Read NumFolders.
 	 */
-	r = parse_7zip_uint64(p, len, &(ci->numFolders));
-	if (r < 0)
+	if (parse_7zip_uint64(a, &(ci->numFolders)) < 0)
 		goto failed;
-	p += r;
-	len -= r;
+	if (1000000 < ci->numFolders)
+			return (-1);
 
 	/*
 	 * Read External.
 	 */
-	if (len == 0)
+	if ((p = header_bytes(a, 1)) == NULL)
 		goto failed;
-	external = *p++;
-	len --;
-	switch (external) {
+	switch (*p) {
 	case 0:
 		ci->folders = calloc(ci->numFolders, sizeof(*ci->folders));
 		if (ci->folders == NULL)
 			return (-1);
 		for (i = 0; i < ci->numFolders; i++) {
-			r = read_Folder(&(ci->folders[i]), p, len);
-			if (r < 0)
+			if (read_Folder(a, &(ci->folders[i])) < 0)
 				goto failed;
-			p += r;
-			len -= r;
 		}
 		break;
 	case 1:
-		r = parse_7zip_uint64(p, len, &(ci->dataStreamIndex));
-		if (r < 0)
-			return (r);
-		p += r;
-		len -= r;
+		if (parse_7zip_uint64(a, &(ci->dataStreamIndex)) < 0)
+			return (-1);
+		if (1000000 < ci->dataStreamIndex)
+			return (-1);
 		break;
 	}
 
-	if (len < 1 + ci->numFolders || *p++ != kCodersUnPackSize)
+	if ((p = header_bytes(a, 1)) == NULL)
+		goto failed;
+	if (*p != kCodersUnPackSize)
 		goto failed;
-	--len;
 
 	for (i = 0; i < ci->numFolders; i++) {
 		struct _7z_folder *folder = &(ci->folders[i]);
@@ -1959,30 +1941,22 @@ read_CodersInfo(struct _7z_coders_info *ci, const unsigned char *p, size_t len)
 		if (folder->unPackSize == NULL)
 			goto failed;
 		for (j = 0; j < folder->numOutStreams; j++) {
-			r = parse_7zip_uint64(p, len,
-			      &(folder->unPackSize[j]));
-			if (r < 0)
+			if (parse_7zip_uint64(a, &(folder->unPackSize[j])) < 0)
 				goto failed;
-			p += r;
-			len -= r;
 		}
 	}
 
 	/*
 	 * Read CRCs.
 	 */
-	if (len == 0)
+	if ((p = header_bytes(a, 1)) == NULL)
 		goto failed;
 	if (*p == kEnd)
-		return (p - _p + 1);
-	if (len < 1 + ci->numFolders || *p++ != kCRC)
+		return (0);
+	if (*p != kCRC)
 		goto failed;
-	--len;
-	r = read_Digests(&digest, ci->numFolders, p, len);
-	if (r < 0)
+	if (read_Digests(a, &digest, ci->numFolders) < 0)
 		goto failed;
-	p += r;
-	len -= r;
 	for (i = 0; i < ci->numFolders; i++) {
 		ci->folders[i].digest_defined = digest.defineds[i];
 		ci->folders[i].digest = digest.digests[i];
@@ -1991,10 +1965,12 @@ read_CodersInfo(struct _7z_coders_info *ci, const unsigned char *p, size_t len)
 	/*
 	 *  Must be kEnd.
 	 */
-	if (len == 0 || *p++ != kEnd)
+	if ((p = header_bytes(a, 1)) == NULL)
+		goto failed;
+	if (*p != kEnd)
 		goto failed;
 	free_Digest(&digest);
-	return (p - _p);
+	return (0);
 failed:
 	free_Digest(&digest);
 	return (-1);
@@ -2027,44 +2003,37 @@ free_SubStreamsInfo(struct _7z_substream_info *ss)
 }
 
 static int
-read_SubStreamsInfo(struct _7z_substream_info *ss, struct _7z_folder *f,
-    size_t numFolders, const unsigned char *p, size_t len)
+read_SubStreamsInfo(struct archive_read *a, struct _7z_substream_info *ss,
+    struct _7z_folder *f, size_t numFolders)
 {
-	const unsigned char *_p = p;
+	const unsigned char *p;
 	uint64_t *usizes;
 	size_t unpack_streams;
-	int r, type;
+	int type;
 	unsigned i;
 	uint32_t numDigests;
 
 	memset(ss, 0, sizeof(*ss));
 
-	if (len < 2 || *p++ != kSubStreamsInfo)
-		return (-1);
-	--len;
-
 	for (i = 0; i < numFolders; i++)
 		f[i].numUnpackStreams = 1;
 
-	if (len < 1)
+	if ((p = header_bytes(a, 1)) == NULL)
 		return (-1);
-	type = *p++;
-	--len;
+	type = *p;
 
 	if (type == kNumUnPackStream) {
 		unpack_streams = 0;
 		for (i = 0; i < numFolders; i++) {
-			r = parse_7zip_uint64(p, len, &(f[i].numUnpackStreams));
-			if (r < 0)
+			if (parse_7zip_uint64(a, &(f[i].numUnpackStreams)) < 0)
+				return (-1);
+			if (1000000 < f[i].numUnpackStreams)
 				return (-1);
-			p += r;
-			len -= r;
 			unpack_streams += f[i].numUnpackStreams;
 		}
-		if (len < 1)
+		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
-		type = *p++;
-		--len;
+		type = *p;
 	} else
 		unpack_streams = numFolders;
 
@@ -2092,22 +2061,18 @@ read_SubStreamsInfo(struct _7z_substream_info *ss, struct _7z_folder *f,
 		sum = 0;
 		if (type == kSize) {
 			for (pack = 1; pack < f[i].numUnpackStreams; pack++) {
-				r = parse_7zip_uint64(p, len, usizes);
-				if (r < 0)
+				if (parse_7zip_uint64(a, usizes) < 0)
 					return (-1);
-				p += r;
-				len -= r;
 				sum += *usizes++;
 			}
 		}
 		*usizes++ = folder_uncompressed_size(&f[i]) - sum;
 	}
 
 	if (type == kSize) {
-		if (len < 1)
+		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
-		type = *p++;
-		--len;
+		type = *p;
 	}
 
 	for (i = 0; i < unpack_streams; i++) {
@@ -2117,8 +2082,7 @@ read_SubStreamsInfo(struct _7z_substream_info *ss, struct _7z_folder *f,
 
 	numDigests = 0;
 	for (i = 0; i < numFolders; i++) {
-		if (f[i].numUnpackStreams != 1 ||
-			!f[i].digest_defined)
+		if (f[i].numUnpackStreams != 1 || !f[i].digest_defined)
 			numDigests += f[i].numUnpackStreams;
 	}
 
@@ -2129,13 +2093,10 @@ read_SubStreamsInfo(struct _7z_substream_info *ss, struct _7z_folder *f,
 		int di = 0;
 
 		memset(&tmpDigests, 0, sizeof(tmpDigests));
-		r = read_Digests(&(tmpDigests), numDigests, p, len);
-		if (r < 0) {
+		if (read_Digests(a, &(tmpDigests), numDigests) < 0) {
 			free_Digest(&tmpDigests);
 			return (-1);
 		}
-		p += r;
-		len -= r;
 		for (i = 0; i < numFolders; i++) {
 			if (f[i].numUnpackStreams == 1 && f[i].digest_defined) {
 				*digestsDefined++ = 1;
@@ -2153,18 +2114,17 @@ read_SubStreamsInfo(struct _7z_substream_info *ss, struct _7z_folder *f,
 			}
 		}
 		free_Digest(&tmpDigests);
-		if (len < 1)
+		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
-		type = *p++;
-		--len;
+		type = *p;
 	}
 
 	/*
 	 *  Must be kEnd.
 	 */
 	if (type != kEnd)
 		return (-1);
-	return (p - _p);
+	return (0);
 }
 
 static void
@@ -2176,24 +2136,24 @@ free_StreamsInfo(struct _7z_stream_info *si)
 }
 
 static int
-read_StreamsInfo(struct _7zip *zip, struct _7z_stream_info *si,
-    const unsigned char *p, size_t len)
+read_StreamsInfo(struct archive_read *a, struct _7z_stream_info *si)
 {
-	const unsigned char *_p = p;
+	struct _7zip *zip = (struct _7zip *)a->format->data;
+	const unsigned char *p;
 	unsigned i;
-	int r;
 
 	memset(si, 0, sizeof(*si));
 
-	if (len > 0 && *p == kPackInfo) {
+	if ((p = header_bytes(a, 1)) == NULL)
+		return (-1);
+	if (*p == kPackInfo) {
 		uint64_t packPos;
 
-		r = read_PackInfo(&(si->pi), p, len);
-		if (r < 0)
+		if (read_PackInfo(a, &(si->pi)) < 0)
 			return (-1);
-		p += r;
-		len -= r;
 
+		if (si->pi.positions == NULL || si->pi.sizes == NULL)
+			return (-1);
 		/*
 		 * Calculate packed stream positions.
 		 */
@@ -2204,16 +2164,15 @@ read_StreamsInfo(struct _7zip *zip, struct _7z_stream_info *si,
 			if (packPos > zip->header_offset)
 				return (-1);
 		}
+		if ((p = header_bytes(a, 1)) == NULL)
+			return (-1);
 	}
-	if (len > 0 && *p == kUnPackInfo) {
+	if (*p == kUnPackInfo) {
 		uint32_t packIndex;
 		struct _7z_folder *f;
 
-		r = read_CodersInfo(&(si->ci), p, len);
-		if (r < 0)
+		if (read_CodersInfo(a, &(si->ci)) < 0)
 			return (-1);
-		p += r;
-		len -= r;
 
 		/*
 		 * Calculate packed stream indexes.
@@ -2226,22 +2185,24 @@ read_StreamsInfo(struct _7zip *zip, struct _7z_stream_info *si,
 			if (packIndex > si->pi.numPackStreams)
 				return (-1);
 		}
+		if ((p = header_bytes(a, 1)) == NULL)
+			return (-1);
 	}
-	if (len > 0 && *p == kSubStreamsInfo) {
-		r = read_SubStreamsInfo(&(si->ss),
-		    si->ci.folders, si->ci.numFolders, p, len);
-		if (r < 0)
+
+	if (*p == kSubStreamsInfo) {
+		if (read_SubStreamsInfo(a, &(si->ss),
+		    si->ci.folders, si->ci.numFolders) < 0)
+			return (-1);
+		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
-		p += r;
-		len -= r;
 	}
 
 	/*
 	 *  Must be kEnd.
 	 */
-	if (len == 0 || *p++ != kEnd)
+	if (*p != kEnd)
 		return (-1);
-	return (p - _p);
+	return (0);
 }
 
 static void
@@ -2254,71 +2215,69 @@ free_Header(struct _7z_header_info *h)
 }
 
 static int
-read_Header(struct _7zip *zip, struct _7z_header_info *h,
-    const unsigned char *p, size_t len)
+read_Header(struct archive_read *a, struct _7z_header_info *h,
+    int check_header_id)
 {
-	const unsigned char *_p = p;
+	struct _7zip *zip = (struct _7zip *)a->format->data;
+	const unsigned char *p;
 	struct _7z_folder *folders;
 	struct _7z_stream_info *si = &(zip->si);
 	struct _7zip_entry *entries;
 	uint32_t folderIndex, indexInFolder;
 	unsigned i;
-	int eindex, empty_streams, r, sindex;
+	int eindex, empty_streams, sindex;
 
-	if (len < 2 || *p++ != kHeader)
-		return (-1);
-	len--;
+	if (check_header_id) {
+		/*
+		 * Read Header.
+		 */
+		if ((p = header_bytes(a, 1)) == NULL)
+			return (-1);
+		if (*p != kHeader)
+			return (-1);
+	}
 
 	/*
 	 * Read ArchiveProperties.
 	 */
+	if ((p = header_bytes(a, 1)) == NULL)
+		return (-1);
 	if (*p == kArchiveProperties) {
-		p++;
-		len--;
-
 		for (;;) {
 			uint64_t size;
-			int atype = *p++;
-			len--;
-			if (atype == 0)
+			if ((p = header_bytes(a, 1)) == NULL)
+				return (-1);
+			if (*p == 0)
 				break;
-			r = parse_7zip_uint64(p, len, &size);
-			if (r < 0 || len < r + size)
+			if (parse_7zip_uint64(a, &size) < 0)
 				return (-1);
-			p += r + size;
-			len -= r + size;
 		}
+		if ((p = header_bytes(a, 1)) == NULL)
+			return (-1);
 	}
 
 	/*
 	 * Read MainStreamsInfo.
 	 */
 	if (*p == kMainStreamsInfo) {
-		p++;
-		len--;
-		r = read_StreamsInfo(zip, &(zip->si), p, len);
-		if (r < 0)
+		if (read_StreamsInfo(a, &(zip->si)) < 0)
+			return (-1);
+		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
-		p += r;
-		len -= r;
 	}
-	if (len == 0)
-		return (-1);
 	if (*p == kEnd)
-		return (p - _p + 1);
+		return (0);
 
 	/*
 	 * Read FilesInfo.
 	 */
-	if (len < 2 || *p++ != kFilesInfo)
+	if (*p != kFilesInfo)
 		return (-1);
-	len--;
 
-	r = parse_7zip_uint64(p, len, &(zip->numFiles));
-	if (r < 0)
+	if (parse_7zip_uint64(a, &(zip->numFiles)) < 0)
 		return (-1);
-	p += r;
-	len -= r;
+	if (1000000 < zip->numFiles)
+			return (-1);
 
 	zip->entries = calloc(zip->numFiles, sizeof(*zip->entries));
 	if (zip->entries == NULL)
@@ -2331,33 +2290,27 @@ read_Header(struct _7zip *zip, struct _7z_header_info *h,
 		uint64_t size;
 		size_t ll;
 
-		if (len < 1)
+		if ((p = header_bytes(a, 1)) == NULL)
 			return (-1);
-		type = *p++;
-		len--;
+		type = *p;
 		if (type == kEnd)
 			break;
 
-		r = parse_7zip_uint64(p, len, &size);
-		if (r < 0 || len < size)
+		if (parse_7zip_uint64(a, &size) < 0)
+			return (-1);
+		if (zip->header_bytes_remaining < size)
 			return (-1);
-		p += r;
-		len -= r;
 		ll = (size_t)size;
-		len -= ll;
 
 		switch (type) {
 		case kEmptyStream:
 			h->emptyStreamBools = calloc(zip->numFiles,
 			    sizeof(*h->emptyStreamBools));
 			if (h->emptyStreamBools == NULL)
 				return (-1);
-			r = read_Bools(h->emptyStreamBools, zip->numFiles,
-			    p, ll);
-			if (r < 0)
+			if (read_Bools(
+			    a, h->emptyStreamBools, zip->numFiles) < 0)
 				return (-1);
-			p += r;
-			ll -= r;
 			empty_streams = 0;
 			for (i = 0; i < zip->numFiles; i++) {
 				if (h->emptyStreamBools[i])
@@ -2369,48 +2322,59 @@ read_Header(struct _7zip *zip, struct _7z_header_info *h,
 			    sizeof(*h->emptyFileBools));
 			if (h->emptyFileBools == NULL)
 				return (-1);
-			r = read_Bools(h->emptyFileBools, empty_streams,
-			    p, len);
-			if (r < 0)
+			if (read_Bools(a, h->emptyFileBools, empty_streams) < 0)
 				return (-1);
-			p += r;
-			ll -= r;
 			break;
 		case kAnti:
 			h->antiBools = calloc(empty_streams,
 			    sizeof(*h->antiBools));
 			if (h->antiBools == NULL)
 				return (-1);
-			r = read_Bools(h->antiBools, empty_streams, p, len);
-			if (r < 0)
+			if (read_Bools(a, h->antiBools, empty_streams) < 0)
 				return (-1);
-			p += r;
-			ll -= r;
 			break;
 		case kCTime:
 		case kATime:
 		case kMTime:
-			r = read_Times(zip, h, type, p, ll);
-			if (r < 0)
+			if (read_Times(a, h, type) < 0)
 				return (-1);
-			p += r;
-			ll -= r;
 			break;
 		case kName:
 		{
 			unsigned char *np;
-			size_t nl;
+			size_t nl, nb;
 
-			if (ll < 1)
+			/* Skip one byte. */
+			if ((p = header_bytes(a, 1)) == NULL)
 				return (-1);
-			p++; ll--;/* Skip one byte. */
+			ll--;
+
 			if ((ll & 1) || ll < zip->numFiles * 4)
 				return (-1);
 
 			zip->entry_names = malloc(ll);
 			if (zip->entry_names == NULL)
 				return (-1);
-			memcpy(zip->entry_names, p, ll);
+			np = zip->entry_names;
+			nb = ll;
+			/*
+			 * Copy whole file names.
+			 * NOTE: This loop prevents from expanding
+			 * the uncompressed buffer in order not to
+			 * use extra memory resource.
+			 */
+			while (nb) {
+				size_t b;
+				if (nb > UBUFF_SIZE)
+					b = UBUFF_SIZE;
+				else
+					b = nb;
+				if ((p = header_bytes(a, b)) == NULL)
+					return (-1);
+				memcpy(np, p, b);
+				np += b;
+				nb -= b;
+			}
 			np = zip->entry_names;
 			nl = ll;
 
@@ -2437,41 +2401,34 @@ read_Header(struct _7zip *zip, struct _7z_header_info *h,
 		{
 			int allAreDefined;
 
-			if (ll < 2)
+			if ((p = header_bytes(a, 2)) == NULL)
 				return (-1);
-			allAreDefined = *p++;
-			--ll;
-			p++; --ll;/* Skip one byte. */
+			allAreDefined = *p;
 			h->attrBools = calloc(zip->numFiles,
 			    sizeof(*h->attrBools));
 			if (h->attrBools == NULL)
 				return (-1);
 			if (allAreDefined)
 				memset(h->attrBools, 1, zip->numFiles);
 			else {
-				r = read_Bools(h->attrBools,
-				      zip->numFiles, p, ll);
-				if (r < 0)
+				if (read_Bools(a, h->attrBools,
+				      zip->numFiles) < 0)
 					return (-1);
-				p += r;
-				ll -= r;
 			}
 			for (i = 0; i < zip->numFiles; i++) {
 				if (h->attrBools[i]) {
-					if (ll < 4)
+					if ((p = header_bytes(a, 4)) == NULL)
 						return (-1);
 					entries[i].attr = archive_le32dec(p);
-					p += 4;
-					ll -= 4;
 				}
 			}
 			break;
 		}
 		default:
+			if (header_bytes(a, ll) == NULL)
+				return (-1);
 			break;
 		}
-		/* Skip remaining data. */
-		p += ll;
 	}
 
 	/*
@@ -2481,8 +2438,7 @@ read_Header(struct _7zip *zip, struct _7z_header_info *h,
 	eindex = sindex = 0;
 	folderIndex = indexInFolder = 0;
 	for (i = 0; i < zip->numFiles; i++) {
-		if (h->emptyStreamBools == NULL ||
-		    h->emptyStreamBools[i] == 0)
+		if (h->emptyStreamBools == NULL || h->emptyStreamBools[i] == 0)
 			entries[i].flg |= HAS_STREAM;
 		/* The high 16 bits of attributes is a posix file mode. */
 		entries[i].mode = entries[i].attr >> 16;
@@ -2556,7 +2512,7 @@ read_Header(struct _7zip *zip, struct _7z_header_info *h,
 		}
 	}
 
-	return (p - _p);
+	return (0);
 }
 
 #define EPOC_TIME ARCHIVE_LITERAL_ULL(116444736000000000)
@@ -2577,50 +2533,44 @@ fileTimeToUtc(uint64_t fileTime, time_t *time, long *ns)
 }
 
 static int
-read_Times(struct _7zip *zip, struct _7z_header_info *h, int type,
-    const unsigned char *p, size_t len)
+read_Times(struct archive_read *a, struct _7z_header_info *h, int type)
 {
-	const unsigned char *_p = p;
+	struct _7zip *zip = (struct _7zip *)a->format->data;
+	const unsigned char *p;
 	struct _7zip_entry *entries = zip->entries;
 	unsigned char *timeBools;
-	int r;
-	int allAreDefined, external;
+	int allAreDefined;
 	unsigned i;
 
 	timeBools = calloc(zip->numFiles, sizeof(*timeBools));
 	if (timeBools == NULL)
 		return (-1);
 
-	if (len < 1)
+	/* Read allAreDefined. */
+	if ((p = header_bytes(a, 1)) == NULL)
 		goto failed;
-	allAreDefined = *p++;
-	len--;
+	allAreDefined = *p;
 	if (allAreDefined)
 		memset(timeBools, 1, zip->numFiles);
 	else {
-		r = read_Bools(timeBools, zip->numFiles, p, len);
-		if (r < 0)
+		if (read_Bools(a, timeBools, zip->numFiles) < 0)
 			goto failed;
-		p += r;
-		len -= r;
 	}
 
-	if (len < 1)
+	/* Read external. */
+	if ((p = header_bytes(a, 1)) == NULL)
 		goto failed;
-	external = *p++;
-	len--;
-	if (external) {
-		r = parse_7zip_uint64(p, len, &(h->dataIndex));
-		if (r < 0)
+	if (*p) {
+		if (parse_7zip_uint64(a, &(h->dataIndex)) < 0)
 			goto failed;
-		p += r;
-		len -= r;
+		if (1000000 < h->dataIndex)
+			return (-1);
 	}
 
 	for (i = 0; i < zip->numFiles; i++) {
 		if (!timeBools[i])
 			continue;
-		if (len < 8)
+		if ((p = header_bytes(a, 8)) == NULL)
 			goto failed;
 		switch (type) {
 		case kCTime:
@@ -2642,29 +2592,22 @@ read_Times(struct _7zip *zip, struct _7z_header_info *h, int type,
 			entries[i].flg |= MTIME_IS_SET;
 			break;
 		}
-		p += 8;
-		len -= 8;
 	}
 
 	free(timeBools);
-	return (p - _p);
+	return (0);
 failed:
 	free(timeBools);
 	return (-1);
 }
 
-static ssize_t
-decode_header_image(struct archive_read *a, struct _7zip *zip,
-    struct _7z_stream_info *si, const unsigned char *p, uint64_t len,
-    const void **image)
+static int
+decode_encoded_header_info(struct archive_read *a, struct _7z_stream_info *si)
 {
-	const unsigned char *v;
-	size_t vsize;
-	int r;
+	struct _7zip *zip = (struct _7zip *)a->format->data;
 
 	errno = 0;
-	r = read_StreamsInfo(zip, si, p, len);
-	if (r < 0) {
+	if (read_StreamsInfo(a, si) < 0) {
 		if (errno == ENOMEM)
 			archive_set_error(&a->archive, -1,
 			    "Couldn't allocate memory");
@@ -2686,93 +2629,52 @@ decode_header_image(struct archive_read *a, struct _7zip *zip,
 		return (ARCHIVE_FATAL);
 	}
 
-	r = setup_decode_folder(a, si->ci.folders, 1);
-	if (r != ARCHIVE_OK)
-		return (ARCHIVE_FATAL);
-
-	/* Get an uncompressed header size. */
-	vsize = (size_t)zip->folder_outbytes_remaining;
-
-	/*
-	 * Allocate an uncompressed buffer for the header image.
-	 */
-	zip->uncompressed_buffer_size = 64 * 1024;
-	if (vsize > zip->uncompressed_buffer_size)
-		zip->uncompressed_buffer_size = vsize;
-	zip->uncompressed_buffer = malloc(zip->uncompressed_buffer_size);
-	if (zip->uncompressed_buffer == NULL) {
-		archive_set_error(&a->archive, ENOMEM,
-		    "No memory for 7-Zip decompression");
-		return (ARCHIVE_FATAL);
-	}
+	return (ARCHIVE_OK);
+}
 
-	/* Get the bytes we can read to decode the header. */
-	zip->pack_stream_inbytes_remaining = si->pi.sizes[0];
+static const unsigned char *
+header_bytes(struct archive_read *a, size_t rbytes)
+{
+	struct _7zip *zip = (struct _7zip *)a->format->data;
+	const unsigned char *p;
 
-	/* Seek the read point. */
-	if (__archive_read_seek(a, si->pi.pos + zip->seek_base, SEEK_SET) < 0)
-		return (ARCHIVE_FATAL);
-	zip->header_offset = si->pi.pos;
+	if (zip->header_bytes_remaining < rbytes)
+		return (NULL);
+	if (zip->pack_stream_bytes_unconsumed)
+		read_consume(a);
 
-	/* Extract a pack stream. */
-	r = extract_pack_stream(a);
-	if (r < 0)
-		return (r);
-	for (;;) {
+	if (zip->header_is_encoded == 0) {
+		p = __archive_read_ahead(a, rbytes, NULL);
+		if (p == NULL)
+			return (NULL);
+		zip->header_bytes_remaining -= rbytes;
+		zip->pack_stream_bytes_unconsumed = rbytes;
+	} else {
+		const void *buff;
 		ssize_t bytes;
-		
-		bytes = get_uncompressed_data(a, image, vsize);
-		if (bytes < 0)
-			return (r);
-		if (bytes != vsize) {
-			if (*image != zip->uncompressed_buffer) {
-				/* This might happen if the coder was COPY.
-				 * We have to make sure we read a full plain
-				 * header image. */
-				if (NULL==__archive_read_ahead(a, vsize, NULL))
-					return (ARCHIVE_FATAL);
-				continue;
-			} else {
-				archive_set_error(&a->archive, -1,
-				    "Malformed 7-Zip archive file");
-				return (ARCHIVE_FATAL);
-			}
-		}
-		break;
-	}
-	v = *image;
-
-	/* Clean up variables which will not be used for decoding the
-	 * archive header */
-	zip->pack_stream_remaining = 0;
-	zip->pack_stream_index = 0;
-	zip->folder_outbytes_remaining = 0;
-	zip->uncompressed_buffer_bytes_remaining = 0;
-	zip->pack_stream_bytes_unconsumed = 0;
 
-	/* Check the header CRC. */
-	if (si->ci.folders[0].digest_defined){
-		uint32_t c = crc32(0, v, vsize);
-		if (c != si->ci.folders[0].digest) {
-			archive_set_error(&a->archive, -1, "Header CRC error");
-			return (ARCHIVE_FATAL);
-		}
+		bytes = read_stream(a, &buff, rbytes, rbytes);
+		if (bytes <= 0)
+			return (NULL);
+		zip->header_bytes_remaining -= bytes;
+		p = buff;
 	}
-	return ((ssize_t)vsize);
+
+	/* Update checksum */
+	zip->header_crc32 = crc32(zip->header_crc32, p, rbytes);
+	return (p);
 }
 
 static int
 slurp_central_directory(struct archive_read *a, struct _7zip *zip,
     struct _7z_header_info *header)
 {
 	const unsigned char *p;
-	const void *image;
-	uint64_t len;
 	uint64_t next_header_offset;
 	uint64_t next_header_size;
 	uint32_t next_header_crc;
-	ssize_t bytes_avail, image_bytes;
-	int r;
+	ssize_t bytes_avail;
+	int check_header_crc, r;
 
 	if ((p = __archive_read_ahead(a, 32, &bytes_avail)) == NULL)
 		return (ARCHIVE_FATAL);
@@ -2782,7 +2684,7 @@ slurp_central_directory(struct archive_read *a, struct _7zip *zip,
 		r = skip_sfx(a, bytes_avail);
 		if (r < ARCHIVE_WARN)
 			return (r);
-		if ((p = __archive_read_ahead(a, 32, NULL)) == NULL)
+		if ((p = __archive_read_ahead(a, 32, &bytes_avail)) == NULL)
 			return (ARCHIVE_FATAL);
 	}
 	zip->seek_base += 32;
@@ -2810,45 +2712,71 @@ slurp_central_directory(struct archive_read *a, struct _7zip *zip,
 		archive_set_error(&a->archive, -1, "Malformed 7-Zip archive");
 		return (ARCHIVE_FATAL);
 	}
-	if (__archive_read_seek(a, next_header_offset + zip->seek_base,
-	    SEEK_SET) < 0)
-		return (ARCHIVE_FATAL);
+	__archive_read_consume(a, 32);
+	if (next_header_offset != 0) {
+		if (bytes_avail >= next_header_offset)
+			__archive_read_consume(a, next_header_offset);
+		else if (__archive_read_seek(a,
+		    next_header_offset + zip->seek_base, SEEK_SET) < 0)
+			return (ARCHIVE_FATAL);
+	}
+	zip->stream_offset = next_header_offset;
 	zip->header_offset = next_header_offset;
+	zip->header_bytes_remaining = next_header_size;
+	zip->header_crc32 = 0;
+	zip->header_is_encoded = 0;
+	zip->header_is_being_read = 1;
+	check_header_crc = 1;
 
-	if ((p = __archive_read_ahead(a, next_header_size, NULL)) == NULL)
-		return (ARCHIVE_FATAL);
-
-	if (crc32(0, p, next_header_size) != next_header_crc) {
-		archive_set_error(&a->archive, -1, "Damaged 7-Zip archive");
+	if ((p = header_bytes(a, 1)) == NULL) {
+		archive_set_error(&a->archive,
+		    ARCHIVE_ERRNO_FILE_FORMAT,
+		    "Truncated 7-Zip file body");
 		return (ARCHIVE_FATAL);
 	}
-
-	len = next_header_size;
 	/* Parse ArchiveProperties. */
 	switch (p[0]) {
 	case kEncodedHeader:
-		p++;
-		len--;
-
 		/*
 		 * The archive has an encoded header and we have to decode it
 		 * in order to parse the header correctly.
 		 */
-		image_bytes =
-		    decode_header_image(a, zip, &(zip->si), p, len, &image);
+		r = decode_encoded_header_info(a, &(zip->si));
+
+		/* Check the EncodedHeader CRC.*/
+		if (r == 0 && zip->header_crc32 != next_header_crc) {
+			archive_set_error(&a->archive, -1,
+			    "Damaged 7-Zip archive");
+			r = -1;
+		}
+		if (r == 0) {
+			if (zip->si.ci.folders[0].digest_defined)
+				next_header_crc = zip->si.ci.folders[0].digest;
+			else
+				check_header_crc = 0;
+			if (zip->pack_stream_bytes_unconsumed)
+				read_consume(a);
+			r = setup_decode_folder(a, zip->si.ci.folders, 1);
+			if (r == 0) {
+				zip->header_bytes_remaining =
+					zip->folder_outbytes_remaining;
+				r = seek_pack(a);
+			}
+		}
+		/* Clean up StreamsInfo. */
 		free_StreamsInfo(&(zip->si));
 		memset(&(zip->si), 0, sizeof(zip->si));
-		if (image_bytes < 0)
+		if (r < 0)
 			return (ARCHIVE_FATAL);
-		p = image;
-		len = image_bytes;
+		zip->header_is_encoded = 1;
+		zip->header_crc32 = 0;
 		/* FALL THROUGH */
 	case kHeader:
 		/*
 		 * Parse the header.
 		 */
 		errno = 0;
-		r = read_Header(zip, header, p, len);
+		r = read_Header(a, header, zip->header_is_encoded);
 		if (r < 0) {
 			if (errno == ENOMEM)
 				archive_set_error(&a->archive, -1,
@@ -2858,7 +2786,18 @@ slurp_central_directory(struct archive_read *a, struct _7zip *zip,
 				    "Damaged 7-Zip archive");
 			return (ARCHIVE_FATAL);
 		}
-		if (len - r == 0 || p[r] != kEnd) {
+
+		/*
+		 *  Must be kEnd.
+		 */
+		if ((p = header_bytes(a, 1)) == NULL ||*p != kEnd) {
+			archive_set_error(&a->archive, -1,
+			    "Malformed 7-Zip archive");
+			return (ARCHIVE_FATAL);
+		}
+
+		/* Check the Header CRC.*/
+		if (check_header_crc && zip->header_crc32 != next_header_crc) {
 			archive_set_error(&a->archive, -1,
 			    "Malformed 7-Zip archive");
 			return (ARCHIVE_FATAL);
@@ -2869,24 +2808,21 @@ slurp_central_directory(struct archive_read *a, struct _7zip *zip,
 		    "Unexpected Property ID = %X", p[0]);
 		return (ARCHIVE_FATAL);
 	}
-	zip->stream_offset = -1;
 
-	/*
-	 * If the uncompressed buffer was allocated more than 64K for
-	 * the header image, release it.
-	 */
-	if (zip->uncompressed_buffer != NULL &&
-	    zip->uncompressed_buffer_size != 64 * 1024) {
-		free(zip->uncompressed_buffer);
-		zip->uncompressed_buffer = NULL;
-		zip->uncompressed_buffer_size = 0;
-	}
+	/* Clean up variables be used for decoding the archive header */
+	zip->pack_stream_remaining = 0;
+	zip->pack_stream_index = 0;
+	zip->folder_outbytes_remaining = 0;
+	zip->uncompressed_buffer_bytes_remaining = 0;
+	zip->pack_stream_bytes_unconsumed = 0;
+	zip->header_is_being_read = 0;
 
 	return (ARCHIVE_OK);
 }
 
 static ssize_t
-get_uncompressed_data(struct archive_read *a, const void **buff, size_t size)
+get_uncompressed_data(struct archive_read *a, const void **buff, size_t size,
+    size_t minimum)
 {
 	struct _7zip *zip = (struct _7zip *)a->format->data;
 	ssize_t bytes_avail;
@@ -2922,6 +2858,15 @@ get_uncompressed_data(struct archive_read *a, const void **buff, size_t size)
 		return (ARCHIVE_FATAL);
 	} else {
 		/* Packed mode. */
+		if (minimum > zip->uncompressed_buffer_bytes_remaining) {
+			/*
+			 * If remaining uncompressed data size is less than
+			 * the minimum size, fill the buffer up to the
+			 * minimum size.
+			 */
+			if (extract_pack_stream(a, minimum) < 0)
+				return (ARCHIVE_FATAL);
+		}
 		if (size > zip->uncompressed_buffer_bytes_remaining)
 			bytes_avail = (ssize_t)
 			    zip->uncompressed_buffer_bytes_remaining;
@@ -2935,14 +2880,16 @@ get_uncompressed_data(struct archive_read *a, const void **buff, size_t size)
 }
 
 static ssize_t
-extract_pack_stream(struct archive_read *a)
+extract_pack_stream(struct archive_read *a, size_t minimum)
 {
 	struct _7zip *zip = (struct _7zip *)a->format->data;
 	ssize_t bytes_avail;
 	int r;
 
 	if (zip->codec == _7Z_COPY && zip->codec2 == -1) {
-		if (__archive_read_ahead(a, 1, &bytes_avail) == NULL
+		if (minimum == 0)
+			minimum = 1;
+		if (__archive_read_ahead(a, minimum, &bytes_avail) == NULL
 		    || bytes_avail <= 0) {
 			archive_set_error(&a->archive,
 			    ARCHIVE_ERRNO_FILE_FORMAT,
@@ -2961,16 +2908,58 @@ extract_pack_stream(struct archive_read *a)
 
 	/* If the buffer hasn't been allocated, allocate it now. */
 	if (zip->uncompressed_buffer == NULL) {
-		zip->uncompressed_buffer_size = 64 * 1024;
+		zip->uncompressed_buffer_size = UBUFF_SIZE;
+		if (zip->uncompressed_buffer_size < minimum) {
+			zip->uncompressed_buffer_size = minimum + 1023;
+			zip->uncompressed_buffer_size &= ~0x3ff;
+		}
 		zip->uncompressed_buffer =
 		    malloc(zip->uncompressed_buffer_size);
 		if (zip->uncompressed_buffer == NULL) {
 			archive_set_error(&a->archive, ENOMEM,
 			    "No memory for 7-Zip decompression");
 			return (ARCHIVE_FATAL);
 		}
-	}
-	zip->uncompressed_buffer_bytes_remaining = 0;
+		zip->uncompressed_buffer_bytes_remaining = 0;
+	} else if (zip->uncompressed_buffer_size < minimum ||
+	    zip->uncompressed_buffer_bytes_remaining < minimum) {
+		/*
+		 * Make sure the uncompressed buffer can have bytes
+		 * at least `minimum' bytes.
+		 * NOTE: This case happen when reading the header.
+		 */
+		size_t used;
+		if (zip->uncompressed_buffer_pointer != 0)
+			used = zip->uncompressed_buffer_pointer -
+				zip->uncompressed_buffer;
+		else
+			used = 0;
+		if (zip->uncompressed_buffer_size < minimum) {
+			/*
+			 * Expand the uncompressed buffer up to
+			 * the minimum size.
+			 */
+			zip->uncompressed_buffer_size = minimum + 1023;
+			zip->uncompressed_buffer_size &= ~0x3ff;
+			zip->uncompressed_buffer =
+			    realloc(zip->uncompressed_buffer,
+				zip->uncompressed_buffer_size);
+			if (zip->uncompressed_buffer == NULL) {
+				archive_set_error(&a->archive, ENOMEM,
+				    "No memory for 7-Zip decompression");
+				return (ARCHIVE_FATAL);
+			}
+		}
+		/*
+		 * Move unconsumed bytes to the head.
+		 */
+		if (used) {
+			memmove(zip->uncompressed_buffer,
+				zip->uncompressed_buffer + used,
+				zip->uncompressed_buffer_bytes_remaining);
+		}
+	} else
+		zip->uncompressed_buffer_bytes_remaining = 0;
 	zip->uncompressed_buffer_pointer = NULL;
 	for (;;) {
 		size_t bytes_in, bytes_out;
@@ -3025,6 +3014,10 @@ extract_pack_stream(struct archive_read *a)
 		if (zip->uncompressed_buffer_bytes_remaining ==
 		    zip->uncompressed_buffer_size)
 			break;
+		if (zip->codec2 == _7Z_X86 && zip->odd_bcj_size &&
+		    zip->uncompressed_buffer_bytes_remaining + 5 >
+		    zip->uncompressed_buffer_size)
+			break;
 		if (zip->pack_stream_inbytes_remaining == 0 &&
 		    zip->folder_outbytes_remaining == 0)
 			break;
@@ -3035,6 +3028,11 @@ extract_pack_stream(struct archive_read *a)
 		}
 		read_consume(a);
 	}
+	if (zip->uncompressed_buffer_bytes_remaining < minimum) {
+		archive_set_error(&(a->archive),
+		    ARCHIVE_ERRNO_MISC, "Damaged 7-Zip archive");
+		return (ARCHIVE_FATAL);
+	}
 	zip->uncompressed_buffer_pointer = zip->uncompressed_buffer;
 	return (ARCHIVE_OK);
 }
@@ -3065,37 +3063,45 @@ seek_pack(struct archive_read *a)
 }
 
 static ssize_t
-read_stream(struct archive_read *a, const void **buff, size_t size)
+read_stream(struct archive_read *a, const void **buff, size_t size,
+    size_t minimum)
 {
 	struct _7zip *zip = (struct _7zip *)a->format->data;
 	uint64_t skip_bytes = 0;
 	int r;
 
 	if (zip->uncompressed_buffer_bytes_remaining == 0) {
 		if (zip->pack_stream_inbytes_remaining > 0) {
-			r = extract_pack_stream(a);
+			r = extract_pack_stream(a, 0);
 			if (r < 0)
 				return (r);
-			return (get_uncompressed_data(a, buff, size));
+			return (get_uncompressed_data(a, buff, size, minimum));
 		} else if (zip->folder_outbytes_remaining > 0) {
 			/* Extract a remaining pack stream. */
-			r = extract_pack_stream(a);
+			r = extract_pack_stream(a, 0);
 			if (r < 0)
 				return (r);
-			return (get_uncompressed_data(a, buff, size));
+			return (get_uncompressed_data(a, buff, size, minimum));
 		}
 	} else
-		return (get_uncompressed_data(a, buff, size));
+		return (get_uncompressed_data(a, buff, size, minimum));
 
 	/*
 	 * Current pack stream has been consumed.
 	 */
 	if (zip->pack_stream_remaining == 0) {
+		if (zip->header_is_being_read) {
+			/* Invalid sequence. This might happen when
+			 * reading a malformed archive. */
+			archive_set_error(&(a->archive),
+			    ARCHIVE_ERRNO_MISC, "Malformed 7-Zip archive");
+			return (ARCHIVE_FATAL);
+		}
+
 		/*
 		 * All current folder's pack streams have been
 		 * consumed. Switch to next folder.
 		 */
-
 		if (zip->folder_index == 0 &&
 		    (zip->si.ci.folders[zip->entry->folderIndex].skipped_bytes
 		     || zip->folder_index != zip->entry->folderIndex)) {
@@ -3127,7 +3133,7 @@ read_stream(struct archive_read *a, const void **buff, size_t size)
 		return (r);
 
 	/* Extract a new pack stream. */
-	r = extract_pack_stream(a);
+	r = extract_pack_stream(a, 0);
 	if (r < 0)
 		return (r);
 
@@ -3139,12 +3145,12 @@ read_stream(struct archive_read *a, const void **buff, size_t size)
 
 		if (zip->uncompressed_buffer_bytes_remaining == 0) {
 			if (zip->pack_stream_inbytes_remaining > 0) {
-				r = extract_pack_stream(a);
+				r = extract_pack_stream(a, 0);
 				if (r < 0)
 					return (r);
 			} else if (zip->folder_outbytes_remaining > 0) {
 				/* Extract a remaining pack stream. */
-				r = extract_pack_stream(a);
+				r = extract_pack_stream(a, 0);
 				if (r < 0)
 					return (r);
 			} else {
@@ -3154,15 +3160,15 @@ read_stream(struct archive_read *a, const void **buff, size_t size)
 				return (ARCHIVE_FATAL);
 			}
 		}
-		skipped = get_uncompressed_data(a, buff, skip_bytes);
+		skipped = get_uncompressed_data(a, buff, skip_bytes, 0);
 		if (skipped < 0)
 			return (skipped);
 		skip_bytes -= skipped;
 		if (zip->pack_stream_bytes_unconsumed)
 			read_consume(a);
 	}
 
-	return (get_uncompressed_data(a, buff, size));
+	return (get_uncompressed_data(a, buff, size, minimum));
 }
 
 static int
@@ -3336,11 +3342,12 @@ setup_decode_folder(struct archive_read *a, struct _7z_folder *folder,
 
 			/* Extract a sub stream. */
 			while (zip->pack_stream_inbytes_remaining > 0) {
-				r = extract_pack_stream(a);
+				r = extract_pack_stream(a, 0);
 				if (r < 0)
 					return (r);
 				bytes = get_uncompressed_data(a, &buff,
-				    zip->uncompressed_buffer_bytes_remaining);
+				    zip->uncompressed_buffer_bytes_remaining,
+				    0);
 				if (bytes < 0)
 					return ((int)bytes);
 				memcpy(b[i]+s[i], buff, bytes);
@@ -3412,7 +3419,7 @@ skip_stream(struct archive_read *a, size_t skip_bytes)
 	}
 
 	while (bytes) {
-		skipped_bytes = read_stream(a, &p, bytes);
+		skipped_bytes = read_stream(a, &p, bytes, 0);
 		if (skipped_bytes < 0)
 			return (skipped_bytes);
 		if (skipped_bytes == 0) {
@@ -3438,18 +3445,30 @@ skip_stream(struct archive_read *a, size_t skip_bytes)
 
 #define Test86MSByte(b) ((b) == 0 || (b) == 0xFF)
 
-static const unsigned char kMaskToAllowedStatus[8] = {1, 1, 1, 0, 1, 0, 0, 0};
-static const unsigned char kMaskToBitNumber[8] = {0, 1, 2, 2, 3, 3, 3, 3};
+static void
+x86_Init(struct _7zip *zip)
+{
+	zip->bcj_state = 0;
+	zip->bcj_prevPosT = (size_t)0 - 1;
+	zip->bcj_prevMask = 0;
+	zip->bcj_ip = 5;
+}
 
 static size_t
-x86_Convert(uint8_t *data, size_t size, uint32_t ip, uint32_t *state)
+x86_Convert(struct _7zip *zip, uint8_t *data, size_t size)
 {
-	size_t bufferPos = 0, prevPosT;
-	uint32_t prevMask = *state & 0x7;
+	static const uint8_t kMaskToAllowedStatus[8] = {1, 1, 1, 0, 1, 0, 0, 0};
+	static const uint8_t kMaskToBitNumber[8] = {0, 1, 2, 2, 3, 3, 3, 3};
+	size_t bufferPos, prevPosT;
+	uint32_t ip, prevMask;
+
 	if (size < 5)
 		return 0;
-	ip += 5;
-	prevPosT = (size_t)0 - 1;
+
+	bufferPos = 0;
+	prevPosT = zip->bcj_prevPosT;
+	prevMask = zip->bcj_prevMask;
+	ip = zip->bcj_ip;
 
 	for (;;) {
 		uint8_t *p = data + bufferPos;
@@ -3508,9 +3527,9 @@ x86_Convert(uint8_t *data, size_t size, uint32_t ip, uint32_t *state)
 			bufferPos++;
 		}
 	}
-	prevPosT = bufferPos - prevPosT;
-	*state = ((prevPosT > 3) ? 
-			0 : ((prevMask << ((int)prevPosT - 1)) & 0x7));
+	zip->bcj_prevPosT = prevPosT;
+	zip->bcj_prevMask = prevMask;
+	zip->bcj_ip += bufferPos;
 	return (bufferPos);
 }
 
@@ -3545,7 +3564,7 @@ x86_Convert(uint8_t *data, size_t size, uint32_t ip, uint32_t *state)
 #define UPDATE_0(p) zip->bcj2_range = bound; *(p) = (CProb)(ttt + ((kBitModelTotal - ttt) >> kNumMoveBits)); NORMALIZE;
 #define UPDATE_1(p) zip->bcj2_range -= bound; zip->bcj2_code -= bound; *(p) = (CProb)(ttt - (ttt >> kNumMoveBits)); NORMALIZE;
 
-ssize_t
+static ssize_t
 Bcj2_Decode(struct _7zip *zip, uint8_t *outBuf, size_t outSize)
 {
 	size_t inPos = 0, outPos = 0;