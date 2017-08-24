@@ -1,5 +1,5 @@
 /*-
- * Copyright (c) 2010-2011 Michihiro NAKAJIMA
+ * Copyright (c) 2010-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -292,6 +292,8 @@ struct cab {
 	char			 end_of_archive;
 	char			 end_of_entry;
 	char			 end_of_entry_cleanup;
+	char			 read_data_invoked;
+	int64_t			 bytes_skipped;
 
 	unsigned char		*uncompressed_buffer;
 	size_t			 uncompressed_buffer_size;
@@ -349,7 +351,7 @@ static int	lzx_read_bitlen(struct lzx_stream *, struct huffman *, int);
 static int	lzx_huffman_init(struct huffman *, size_t, int);
 static void	lzx_huffman_free(struct huffman *);
 static int	lzx_make_huffman_table(struct huffman *);
-static int inline lzx_decode_huffman(struct huffman *, unsigned);
+static inline int lzx_decode_huffman(struct huffman *, unsigned);
 static int	lzx_decode_huffman_tree(struct huffman *, unsigned, int);
 
 
@@ -380,6 +382,7 @@ archive_read_support_format_cab(struct archive *_a)
 	    archive_read_format_cab_read_header,
 	    archive_read_format_cab_read_data,
 	    archive_read_format_cab_read_data_skip,
+	    NULL,
 	    archive_read_format_cab_cleanup);
 
 	if (r != ARCHIVE_OK)
@@ -478,11 +481,13 @@ archive_read_format_cab_options(struct archive_read *a,
 			else
 				ret = ARCHIVE_FATAL;
 		}
-	} else
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "cab: unknown keyword ``%s''", key);
+		return (ret);
+	}
 
-	return (ret);
+	/* Note: The "warn" return is just to inform the options
+	 * supervisor that we didn't handle it.  It will generate
+	 * a suitable error if no one used this option. */
+	return (ARCHIVE_WARN);
 }
 
 static int
@@ -535,7 +540,7 @@ truncated_error(struct archive_read *a)
 	return (ARCHIVE_FATAL);
 }
 
-static int
+static ssize_t
 cab_strnlen(const unsigned char *p, size_t maxlen)
 {
 	size_t i;
@@ -546,7 +551,7 @@ cab_strnlen(const unsigned char *p, size_t maxlen)
 	}
 	if (i > maxlen)
 		return (-1);/* invalid */
-	return (i);
+	return ((ssize_t)i);
 }
 
 /* Read bytes as much as remaining. */
@@ -622,8 +627,9 @@ cab_read_header(struct archive_read *a)
 	struct cab *cab;
 	struct cfheader *hd;
 	size_t bytes, used;
+	ssize_t len;
 	int64_t skip;
-	int err, i, len;
+	int err, i;
 	int cur_folder, prev_folder;
 	uint32_t offset32;
 	
@@ -796,7 +802,7 @@ cab_read_header(struct archive_read *a)
 		file->offset = archive_le32dec(p + CFFILE_uoffFolderStart);
 		file->folder = archive_le16dec(p + CFFILE_iFolder);
 		file->mtime = cab_dos_time(p + CFFILE_date_time);
-		file->attr = archive_le16dec(p + CFFILE_attribs);
+		file->attr = (uint8_t)archive_le16dec(p + CFFILE_attribs);
 		__archive_read_consume(a, 16);
 
 		cab->cab_offset += 16;
@@ -986,7 +992,7 @@ archive_read_format_cab_read_header(struct archive_read *a,
 	if (file->attr & ATTR_RDONLY)
 		archive_entry_set_mode(entry, AE_IFREG | 0555);
 	else
-		archive_entry_set_mode(entry, AE_IFREG | 0777);
+		archive_entry_set_mode(entry, AE_IFREG | 0666);
 	archive_entry_set_mtime(entry, file->mtime, 0);
 
 	cab->entry_bytes_remaining = file->uncompressed_size;
@@ -1024,9 +1030,22 @@ archive_read_format_cab_read_data(struct archive_read *a,
 	default:
 		break;
 	}
+	if (cab->read_data_invoked == 0) {
+		if (cab->bytes_skipped) {
+			if (cab->entry_cfdata == NULL) {
+				r = cab_next_cfdata(a);
+				if (r < 0)
+					return (r);
+			}
+			if (cab_consume_cfdata(a, cab->bytes_skipped) < 0)
+				return (ARCHIVE_FATAL);
+			cab->bytes_skipped = 0;
+		}
+		cab->read_data_invoked = 1;
+	}
 	if (cab->entry_unconsumed) {
 		/* Consume as much as the compressor actually used. */
-		r = cab_consume_cfdata(a, cab->entry_unconsumed);
+		r = (int)cab_consume_cfdata(a, cab->entry_unconsumed);
 		cab->entry_unconsumed = 0;
 		if (r < 0)
 			return (r);
@@ -1049,13 +1068,13 @@ static uint32_t
 cab_checksum_cfdata_4(const void *p, size_t bytes, uint32_t seed)
 {
 	const unsigned char *b;
-	int u32num;
+	unsigned u32num;
 	uint32_t sum;
 
-	u32num = bytes / 4;
+	u32num = (unsigned)bytes / 4;
 	sum = seed;
 	b = p;
-	while (--u32num >= 0) {
+	for (;u32num > 0; --u32num) {
 		sum ^= archive_le32dec(b);
 		b += 4;
 	}
@@ -1356,46 +1375,25 @@ cab_read_ahead_cfdata_none(struct archive_read *a, ssize_t *avail)
 	struct cab *cab = (struct cab *)(a->format->data);
 	struct cfdata *cfdata;
 	const void *d;
-	int64_t skipped_bytes;
 
 	cfdata = cab->entry_cfdata;
 
-	if (cfdata->uncompressed_avail == 0 &&
-		cfdata->read_offset > 0) {
-		/* we've already skipped some bytes before really read. */
-		skipped_bytes = cfdata->read_offset;
-		cfdata->read_offset = 0;
-		cfdata->uncompressed_bytes_remaining += skipped_bytes;
-	} else
-		skipped_bytes = 0;
-	do {
-		/*
-		 * Note: '1' here is a performance optimization.
-		 * Recall that the decompression layer returns a count of
-		 * available bytes; asking for more than that forces the
-		 * decompressor to combine reads by copying data.
-		 */
-		d = __archive_read_ahead(a, 1, avail);
-		if (*avail <= 0) {
-			*avail = truncated_error(a);
-			return (NULL);
-		}
-		if (*avail > cfdata->uncompressed_bytes_remaining)
-			*avail = cfdata->uncompressed_bytes_remaining;
-		cfdata->uncompressed_avail = cfdata->uncompressed_size;
-		cfdata->unconsumed = *avail;
-		cfdata->sum_ptr = d;
-		if (skipped_bytes > 0) {
-			skipped_bytes =
-			    cab_minimum_consume_cfdata(a, skipped_bytes);
-			if (skipped_bytes < 0) {
-				*avail = ARCHIVE_FATAL;
-				return (NULL);
-			}
-			continue;
-		}
-	} while (0);
-
+	/*
+	 * Note: '1' here is a performance optimization.
+	 * Recall that the decompression layer returns a count of
+	 * available bytes; asking for more than that forces the
+	 * decompressor to combine reads by copying data.
+	 */
+	d = __archive_read_ahead(a, 1, avail);
+	if (*avail <= 0) {
+		*avail = truncated_error(a);
+		return (NULL);
+	}
+	if (*avail > cfdata->uncompressed_bytes_remaining)
+		*avail = cfdata->uncompressed_bytes_remaining;
+	cfdata->uncompressed_avail = cfdata->uncompressed_size;
+	cfdata->unconsumed = *avail;
+	cfdata->sum_ptr = d;
 	return (d);
 }
 
@@ -1489,7 +1487,7 @@ cab_read_ahead_cfdata_deflate(struct archive_read *a, ssize_t *avail)
 		 * cast to remove 'const'.
 		 */
 		cab->stream.next_in = (Bytef *)(uintptr_t)d;
-		cab->stream.avail_in = bytes_avail;
+		cab->stream.avail_in = (uInt)bytes_avail;
 		cab->stream.total_in = 0;
 
 		/* Cut out a tow-byte MSZIP signature(0x43, 0x4b). */
@@ -1510,7 +1508,7 @@ cab_read_ahead_cfdata_deflate(struct archive_read *a, ssize_t *avail)
 					*avail = ARCHIVE_FATAL;
 					return (NULL);
 				}
-				mszip -= bytes_avail;
+				mszip -= (int)bytes_avail;
 				continue;
 			}
 			if (mszip == 1 && cab->stream.next_in[0] != 0x4b)
@@ -1541,7 +1539,7 @@ cab_read_ahead_cfdata_deflate(struct archive_read *a, ssize_t *avail)
 			return (NULL);
 		}
 	}
-	uavail = cab->stream.total_out;
+	uavail = (uint16_t)cab->stream.total_out;
 
 	if (uavail < cfdata->uncompressed_size) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
@@ -1719,7 +1717,7 @@ cab_read_ahead_cfdata_lzx(struct archive_read *a, ssize_t *avail)
 		}
 	}
 
-	uavail = cab->xstrm.total_out;
+	uavail = (uint16_t)cab->xstrm.total_out;
 	/*
 	 * Make sure a read pointer advances to next CFDATA.
 	 */
@@ -1791,9 +1789,8 @@ cab_consume_cfdata(struct archive_read *a, int64_t consumed_bytes)
 		rbytes -= cbytes;
 
 		if (cfdata->uncompressed_avail == 0 &&
-		    (cab->entry_cffolder->comptype == COMPTYPE_NONE ||
-		     cab->entry_cffile->folder == iFoldCONTINUED_PREV_AND_NEXT ||
-			 cab->entry_cffile->folder == iFoldCONTINUED_FROM_PREV)) {
+		   (cab->entry_cffile->folder == iFoldCONTINUED_PREV_AND_NEXT ||
+		    cab->entry_cffile->folder == iFoldCONTINUED_FROM_PREV)) {
 			/* We have not read any data yet. */
 			if (cbytes == cfdata->uncompressed_bytes_remaining) {
 				/* Skip whole current CFDATA. */
@@ -1819,8 +1816,8 @@ cab_consume_cfdata(struct archive_read *a, int64_t consumed_bytes)
 				}
 				continue;
 			}
-			cfdata->read_offset += cbytes;
-			cfdata->uncompressed_bytes_remaining -= cbytes;
+			cfdata->read_offset += (uint16_t)cbytes;
+			cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
 			break;
 		} else if (cbytes == 0) {
 			err = cab_next_cfdata(a);
@@ -1844,7 +1841,7 @@ cab_consume_cfdata(struct archive_read *a, int64_t consumed_bytes)
 			if (avail <= 0)
 				return (ARCHIVE_FATAL);
 			if (avail > cbytes)
-				avail = cbytes;
+				avail = (ssize_t)cbytes;
 			if (cab_minimum_consume_cfdata(a, avail) < 0)
 				return (ARCHIVE_FATAL);
 			cbytes -= avail;
@@ -1873,17 +1870,17 @@ cab_minimum_consume_cfdata(struct archive_read *a, int64_t consumed_bytes)
 		else
 			cbytes = cfdata->unconsumed;
 		rbytes -= cbytes; 
-		cfdata->read_offset += cbytes;
-		cfdata->uncompressed_bytes_remaining -= cbytes;
+		cfdata->read_offset += (uint16_t)cbytes;
+		cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
 		cfdata->unconsumed -= cbytes;
 	} else {
 		cbytes = cfdata->uncompressed_avail - cfdata->read_offset;
 		if (cbytes > 0) {
 			if (consumed_bytes < cbytes)
 				cbytes = consumed_bytes;
 			rbytes -= cbytes;
-			cfdata->read_offset += cbytes;
-			cfdata->uncompressed_bytes_remaining -= cbytes;
+			cfdata->read_offset += (uint16_t)cbytes;
+			cfdata->uncompressed_bytes_remaining -= (uint16_t)cbytes;
 		}
 
 		if (cfdata->unconsumed) {
@@ -1894,12 +1891,12 @@ cab_minimum_consume_cfdata(struct archive_read *a, int64_t consumed_bytes)
 	}
 	if (cbytes) {
 		/* Compute the sum. */
-		cab_checksum_update(a, cbytes);
+		cab_checksum_update(a, (size_t)cbytes);
 
 		/* Consume as much as the compressor actually used. */
 		__archive_read_consume(a, cbytes);
 		cab->cab_offset += cbytes;
-		cfdata->compressed_bytes_remaining -= cbytes;
+		cfdata->compressed_bytes_remaining -= (uint16_t)cbytes;
 		if (cfdata->compressed_bytes_remaining == 0) {
 			err = cab_checksum_finish(a);
 			if (err < 0)
@@ -1940,10 +1937,10 @@ cab_read_data(struct archive_read *a, const void **buff,
 			    ARCHIVE_ERRNO_FILE_FORMAT, "Invalid CFDATA");
 			return (ARCHIVE_FATAL);
 		} else
-			return (bytes_avail);
+			return ((int)bytes_avail);
 	}
 	if (bytes_avail > cab->entry_bytes_remaining)
-		bytes_avail = cab->entry_bytes_remaining;
+		bytes_avail = (ssize_t)cab->entry_bytes_remaining;
 
 	*size = bytes_avail;
 	*offset = cab->entry_offset;
@@ -1952,6 +1949,11 @@ cab_read_data(struct archive_read *a, const void **buff,
 	if (cab->entry_bytes_remaining == 0)
 		cab->end_of_entry = 1;
 	cab->entry_unconsumed = bytes_avail;
+	if (cab->entry_cffolder->comptype == COMPTYPE_NONE) {
+		/* Don't consume more than current entry used. */
+		if (cab->entry_cfdata->unconsumed > cab->entry_unconsumed)
+			cab->entry_cfdata->unconsumed = cab->entry_unconsumed;
+	}
 	return (ARCHIVE_OK);
 }
 
@@ -1967,9 +1969,17 @@ archive_read_format_cab_read_data_skip(struct archive_read *a)
 	if (cab->end_of_archive)
 		return (ARCHIVE_EOF);
 
+	if (!cab->read_data_invoked) {
+		cab->bytes_skipped += cab->entry_bytes_remaining;
+		cab->entry_bytes_remaining = 0;
+		/* This entry is finished and done. */
+		cab->end_of_entry_cleanup = cab->end_of_entry = 1;
+		return (ARCHIVE_OK);
+	}
+
 	if (cab->entry_unconsumed) {
 		/* Consume as much as the compressor actually used. */
-		r = cab_consume_cfdata(a, cab->entry_unconsumed);
+		r = (int)cab_consume_cfdata(a, cab->entry_unconsumed);
 		cab->entry_unconsumed = 0;
 		if (r < 0)
 			return (r);
@@ -1991,6 +2001,12 @@ archive_read_format_cab_read_data_skip(struct archive_read *a)
 	if (bytes_skipped < 0)
 		return (ARCHIVE_FATAL);
 
+	/* If the compression type is none(uncompressed), we've already
+	 * consumed data as much as the current entry size. */
+	if (cab->entry_cffolder->comptype == COMPTYPE_NONE &&
+	    cab->entry_cfdata != NULL)
+		cab->entry_cfdata->unconsumed = 0;
+
 	/* This entry is finished and done. */
 	cab->end_of_entry_cleanup = cab->end_of_entry = 1;
 	return (ARCHIVE_OK);
@@ -2066,6 +2082,7 @@ lzx_decode_init(struct lzx_stream *strm, int w_bits)
 	struct lzx_dec *ds;
 	int slot, w_size, w_slot;
 	int base, footer;
+	int base_inc[18];
 
 	if (strm->ds == NULL) {
 		strm->ds = calloc(1, sizeof(*strm->ds));
@@ -2100,13 +2117,15 @@ lzx_decode_init(struct lzx_stream *strm, int w_bits)
 		lzx_huffman_free(&(ds->mt));
 	}
 
+	for (footer = 0; footer < 18; footer++)
+		base_inc[footer] = 1 << footer;
 	base = footer = 0;
 	for (slot = 0; slot < w_slot; slot++) {
 		int n;
 		if (footer == 0)
 			base = slot;
 		else
-			base += 1 << footer;
+			base += base_inc[footer];
 		if (footer < 17) {
 			footer = -2;
 			for (n = base; n; n >>= 1)
@@ -2180,11 +2199,11 @@ lzx_translation(struct lzx_stream *strm, void *p, size_t size, uint32_t offset)
 	end = b + size - 10;
 	while (b < end && (b = memchr(b, 0xE8, end - b)) != NULL) {
 		size_t i = b - (unsigned char *)p;
-		long cp, displacement, value;
+		int32_t cp, displacement, value;
 
-		cp = offset + i;
+		cp = (int32_t)(offset + (uint32_t)i);
 		value = archive_le32dec(&b[1]);
-		if (value >= -cp && value < (long)ds->translation_size) {
+		if (value >= -cp && value < (int32_t)ds->translation_size) {
 			if (value >= 0)
 				displacement = value - cp;
 			else
@@ -2222,7 +2241,9 @@ lzx_translation(struct lzx_stream *strm, void *p, size_t size, uint32_t offset)
 
 /* Notify how many bits we consumed. */
 #define lzx_br_consume(br, n)	((br)->cache_avail -= (n))
-#define lzx_br_consume_unalined_bits(br) ((br)->cache_avail &= ~0x0f)
+#define lzx_br_consume_unaligned_bits(br) ((br)->cache_avail &= ~0x0f)
+
+#define lzx_br_is_unaligned(br)	((br)->cache_avail & 0x0f)
 
 static const uint32_t cache_masks[] = {
 	0x00000000, 0x00000001, 0x00000003, 0x00000007,
@@ -2349,24 +2370,25 @@ lzx_cleanup_bitstream(struct lzx_stream *strm)
 #define ST_RD_TRANSLATION_SIZE	1
 #define ST_RD_BLOCK_TYPE	2
 #define ST_RD_BLOCK_SIZE	3
-#define ST_RD_R0		4
-#define ST_RD_R1		5
-#define ST_RD_R2		6
-#define ST_COPY_UNCOMP1		7
-#define ST_COPY_UNCOMP2		8
-#define ST_RD_ALIGNED_OFFSET	9
-#define ST_RD_VERBATIM		10
-#define ST_RD_PRE_MAIN_TREE_256	11
-#define ST_MAIN_TREE_256	12
-#define ST_RD_PRE_MAIN_TREE_REM	13
-#define ST_MAIN_TREE_REM	14
-#define ST_RD_PRE_LENGTH_TREE	15
-#define ST_LENGTH_TREE		16
-#define ST_MAIN			17
-#define ST_LENGTH		18
-#define ST_OFFSET		19
-#define ST_REAL_POS		20
-#define ST_COPY			21
+#define ST_RD_ALIGNMENT		4
+#define ST_RD_R0		5
+#define ST_RD_R1		6
+#define ST_RD_R2		7
+#define ST_COPY_UNCOMP1		8
+#define ST_COPY_UNCOMP2		9
+#define ST_RD_ALIGNED_OFFSET	10
+#define ST_RD_VERBATIM		11
+#define ST_RD_PRE_MAIN_TREE_256	12
+#define ST_MAIN_TREE_256	13
+#define ST_RD_PRE_MAIN_TREE_REM	14
+#define ST_MAIN_TREE_REM	15
+#define ST_RD_PRE_LENGTH_TREE	16
+#define ST_LENGTH_TREE		17
+#define ST_MAIN			18
+#define ST_LENGTH		19
+#define ST_OFFSET		20
+#define ST_REAL_POS		21
+#define ST_COPY			22
 
 static int
 lzx_decode(struct lzx_stream *strm, int last)
@@ -2470,12 +2492,25 @@ lzx_read_blocks(struct lzx_stream *strm, int last)
 					ds->state = ST_RD_ALIGNED_OFFSET;
 				break;
 			}
+			/* FALL THROUGH */
+		case ST_RD_ALIGNMENT:
 			/*
 			 * Handle an Uncompressed Block.
 			 */
 			/* Skip padding to align following field on
 			 * 16-bit boundary. */
-			lzx_br_consume_unalined_bits(br);
+			if (lzx_br_is_unaligned(br))
+				lzx_br_consume_unaligned_bits(br);
+			else {
+				if (lzx_br_read_ahead(strm, br, 16))
+					lzx_br_consume(br, 16);
+				else {
+					ds->state = ST_RD_ALIGNMENT;
+					if (last)
+						goto failed;
+					return (ARCHIVE_OK);
+				}
+			}
 			/* Preparation to read repeated offsets R0,R1 and R2. */
 			ds->rbytes_avail = 0;
 			ds->state = ST_RD_R0;
@@ -2500,8 +2535,7 @@ lzx_read_blocks(struct lzx_stream *strm, int last)
 					lzx_br_consume(br, 16);
 					archive_le16enc(ds->rbytes, u16);
 					ds->rbytes_avail = 2;
-				} else
-					ds->rbytes_avail = 0;
+				}
 				if (ds->rbytes_avail < 4 && ds->br.have_odd) {
 					ds->rbytes[ds->rbytes_avail++] =
 					    ds->br.odd;
@@ -2517,6 +2551,7 @@ lzx_read_blocks(struct lzx_stream *strm, int last)
 					    *strm->next_in++;
 					strm->avail_in--;
 				}
+				ds->rbytes_avail = 0;
 				if (ds->state == ST_RD_R0) {
 					ds->r0 = archive_le32dec(ds->rbytes);
 					if (ds->r0 < 0)
@@ -2541,8 +2576,7 @@ lzx_read_blocks(struct lzx_stream *strm, int last)
 			 * Copy bytes form next_in to next_out directly.
 			 */
 			while (ds->block_bytes_avail) {
-				unsigned char *d;
-				int l,ll;
+				int l;
 
 				if (strm->avail_out <= 0)
 					/* Output buffer is empty. */
@@ -2553,24 +2587,23 @@ lzx_read_blocks(struct lzx_stream *strm, int last)
 						goto failed;
 					return (ARCHIVE_OK);
 				}
-				l = ds->block_bytes_avail;
+				l = (int)ds->block_bytes_avail;
 				if (l > ds->w_size - ds->w_pos)
 					l = ds->w_size - ds->w_pos;
 				if (l > strm->avail_out)
 					l = (int)strm->avail_out;
 				if (l > strm->avail_in)
 					l = (int)strm->avail_in;
-				ll = l;
-				d = &(ds->w_buff[ds->w_pos]);
-				while (--l >= 0) {
-					*strm->next_out++ = *strm->next_in;
-					*d++ = *strm->next_in++;
-				}
-				strm->avail_out -= ll;
-				strm->total_out += ll;
-				strm->avail_in -= ll;
-				ds->w_pos = (ds->w_pos + ll) & ds->w_mask;
-				ds->block_bytes_avail -= ll;
+				memcpy(strm->next_out, strm->next_in, l);
+				memcpy(&(ds->w_buff[ds->w_pos]),
+				    strm->next_in, l);
+				strm->next_in += l;
+				strm->avail_in -= l;
+				strm->next_out += l;
+				strm->avail_out -= l;
+				strm->total_out += l;
+				ds->w_pos = (ds->w_pos + l) & ds->w_mask;
+				ds->block_bytes_avail -= l;
 			}
 			/* FALL THROUGH */
 		case ST_COPY_UNCOMP2:
@@ -2716,8 +2749,8 @@ lzx_decode_blocks(struct lzx_stream *strm, int last)
 	struct lzx_br bre = ds->br;
 	struct huffman *at = &(ds->at), *lt = &(ds->lt), *mt = &(ds->mt);
 	const struct lzx_pos_tbl *pos_tbl = ds->pos_tbl;
-	unsigned char *outp = strm->next_out;
-	unsigned char *endp = outp + strm->avail_out;
+	unsigned char *noutp = strm->next_out;
+	unsigned char *endp = noutp + strm->avail_out;
 	unsigned char *w_buff = ds->w_buff;
 	unsigned char *at_bitlen = at->bitlen;
 	unsigned char *lt_bitlen = lt->bitlen;
@@ -2751,10 +2784,10 @@ lzx_decode_blocks(struct lzx_stream *strm, int last)
 					ds->position_slot = position_slot;
 					ds->r0 = r0; ds->r1 = r1; ds->r2 = r2;
 					ds->w_pos = w_pos;
-					strm->avail_out = endp - outp;
+					strm->avail_out = endp - noutp;
 					return (ARCHIVE_EOF);
 				}
-				if (outp >= endp)
+				if (noutp >= endp)
 					/* Output buffer is empty. */
 					goto next_data;
 
@@ -2788,7 +2821,7 @@ lzx_decode_blocks(struct lzx_stream *strm, int last)
 				w_buff[w_pos] = c;
 				w_pos = (w_pos + 1) & w_mask;
 				/* Store the decoded code to output buffer. */
-				*outp++ = c;
+				*noutp++ = c;
 				block_bytes_avail--;
 			}
 			/*
@@ -2933,30 +2966,30 @@ lzx_decode_blocks(struct lzx_stream *strm, int last)
 					if (l > w_size - w_pos)
 						l = w_size - w_pos;
 				}
-				if (outp + l >= endp)
-					l = endp - outp;
+				if (noutp + l >= endp)
+					l = (int)(endp - noutp);
 				s = w_buff + copy_pos;
 				if (l >= 8 && ((copy_pos + l < w_pos)
 				  || (w_pos + l < copy_pos))) {
 					memcpy(w_buff + w_pos, s, l);
-					memcpy(outp, s, l);
+					memcpy(noutp, s, l);
 				} else {
 					unsigned char *d;
 					int li;
 
 					d = w_buff + w_pos;
 					for (li = 0; li < l; li++)
-						outp[li] = d[li] = s[li];
+						noutp[li] = d[li] = s[li];
 				}
-				outp += l;
+				noutp += l;
 				copy_pos = (copy_pos + l) & w_mask;
 				w_pos = (w_pos + l) & w_mask;
 				block_bytes_avail -= l;
 				if (copy_len <= l)
 					/* A copy of current pattern ended. */
 					break;
 				copy_len -= l;
-				if (outp >= endp) {
+				if (noutp >= endp) {
 					/* Output buffer is empty. */
 					state = ST_COPY;
 					goto next_data;
@@ -2979,7 +3012,7 @@ lzx_decode_blocks(struct lzx_stream *strm, int last)
 	ds->r0 = r0; ds->r1 = r1; ds->r2 = r2;
 	ds->state = state;
 	ds->w_pos = w_pos;
-	strm->avail_out = endp - outp;
+	strm->avail_out = endp - noutp;
 	return (ARCHIVE_OK);
 }
 
@@ -3096,15 +3129,15 @@ lzx_huffman_init(struct huffman *hf, size_t len_size, int tbl_bits)
 		hf->bitlen = calloc(len_size,  sizeof(hf->bitlen[0]));
 		if (hf->bitlen == NULL)
 			return (ARCHIVE_FATAL);
-		hf->len_size = len_size;
+		hf->len_size = (int)len_size;
 	} else
 		memset(hf->bitlen, 0, len_size *  sizeof(hf->bitlen[0]));
 	if (hf->tbl == NULL) {
 		if (tbl_bits < HTBL_BITS)
 			bits = tbl_bits;
 		else
 			bits = HTBL_BITS;
-		hf->tbl = malloc((1 << bits) * sizeof(hf->tbl[0]));
+		hf->tbl = malloc(((size_t)1 << bits) * sizeof(hf->tbl[0]));
 		if (hf->tbl == NULL)
 			return (ARCHIVE_FATAL);
 		hf->tbl_bits = tbl_bits;