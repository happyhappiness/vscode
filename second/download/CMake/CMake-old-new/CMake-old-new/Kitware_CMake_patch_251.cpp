@@ -1,5 +1,5 @@
 /*-
- * Copyright (c) 2008-2012 Michihiro NAKAJIMA
+ * Copyright (c) 2008-2014 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -82,9 +82,6 @@ struct lzh_dec {
 	/* The length how many bytes we can copy decoded code from
 	 * the window. */
 	int     		 copy_len;
-	/* The remaining bytes that we have not copied decoded data from
-	 * the window to an output buffer. */
-	int			 w_remaining;
 
 	/*
 	 * Bit stream reader.
@@ -140,10 +137,10 @@ struct lzh_dec {
 
 struct lzh_stream {
 	const unsigned char	*next_in;
-	int64_t			 avail_in;
+	int			 avail_in;
 	int64_t			 total_in;
-	unsigned char		*next_out;
-	int64_t			 avail_out;
+	const unsigned char	*ref_ptr;
+	int			 avail_out;
 	int64_t			 total_out;
 	struct lzh_dec		*ds;
 };
@@ -198,9 +195,6 @@ struct lha {
 	char			 end_of_entry_cleanup;
 	char			 entry_is_compressed;
 
-	unsigned char		*uncompressed_buffer;
-	size_t			 uncompressed_buffer_size;
-
 	char			 format_name[64];
 
 	struct lzh_stream	 strm;
@@ -214,41 +208,6 @@ struct lha {
 #define H_LEVEL_OFFSET	20	/* Header Level.  */
 #define H_SIZE		22	/* Minimum header size. */
 
-static const uint16_t crc16tbl[256] = {
-	0x0000,0xC0C1,0xC181,0x0140,0xC301,0x03C0,0x0280,0xC241,
-	0xC601,0x06C0,0x0780,0xC741,0x0500,0xC5C1,0xC481,0x0440,
-	0xCC01,0x0CC0,0x0D80,0xCD41,0x0F00,0xCFC1,0xCE81,0x0E40,
-	0x0A00,0xCAC1,0xCB81,0x0B40,0xC901,0x09C0,0x0880,0xC841,
-	0xD801,0x18C0,0x1980,0xD941,0x1B00,0xDBC1,0xDA81,0x1A40,
-	0x1E00,0xDEC1,0xDF81,0x1F40,0xDD01,0x1DC0,0x1C80,0xDC41,
-	0x1400,0xD4C1,0xD581,0x1540,0xD701,0x17C0,0x1680,0xD641,
-	0xD201,0x12C0,0x1380,0xD341,0x1100,0xD1C1,0xD081,0x1040,
-	0xF001,0x30C0,0x3180,0xF141,0x3300,0xF3C1,0xF281,0x3240,
-	0x3600,0xF6C1,0xF781,0x3740,0xF501,0x35C0,0x3480,0xF441,
-	0x3C00,0xFCC1,0xFD81,0x3D40,0xFF01,0x3FC0,0x3E80,0xFE41,
-	0xFA01,0x3AC0,0x3B80,0xFB41,0x3900,0xF9C1,0xF881,0x3840,
-	0x2800,0xE8C1,0xE981,0x2940,0xEB01,0x2BC0,0x2A80,0xEA41,
-	0xEE01,0x2EC0,0x2F80,0xEF41,0x2D00,0xEDC1,0xEC81,0x2C40,
-	0xE401,0x24C0,0x2580,0xE541,0x2700,0xE7C1,0xE681,0x2640,
-	0x2200,0xE2C1,0xE381,0x2340,0xE101,0x21C0,0x2080,0xE041,
-	0xA001,0x60C0,0x6180,0xA141,0x6300,0xA3C1,0xA281,0x6240,
-	0x6600,0xA6C1,0xA781,0x6740,0xA501,0x65C0,0x6480,0xA441,
-	0x6C00,0xACC1,0xAD81,0x6D40,0xAF01,0x6FC0,0x6E80,0xAE41,
-	0xAA01,0x6AC0,0x6B80,0xAB41,0x6900,0xA9C1,0xA881,0x6840,
-	0x7800,0xB8C1,0xB981,0x7940,0xBB01,0x7BC0,0x7A80,0xBA41,
-	0xBE01,0x7EC0,0x7F80,0xBF41,0x7D00,0xBDC1,0xBC81,0x7C40,
-	0xB401,0x74C0,0x7580,0xB541,0x7700,0xB7C1,0xB681,0x7640,
-	0x7200,0xB2C1,0xB381,0x7340,0xB101,0x71C0,0x7080,0xB041,
-	0x5000,0x90C1,0x9181,0x5140,0x9301,0x53C0,0x5280,0x9241,
-	0x9601,0x56C0,0x5780,0x9741,0x5500,0x95C1,0x9481,0x5440,
-	0x9C01,0x5CC0,0x5D80,0x9D41,0x5F00,0x9FC1,0x9E81,0x5E40,
-	0x5A00,0x9AC1,0x9B81,0x5B40,0x9901,0x59C0,0x5880,0x9841,
-	0x8801,0x48C0,0x4980,0x8941,0x4B00,0x8BC1,0x8A81,0x4A40,
-	0x4E00,0x8EC1,0x8F81,0x4F40,0x8D01,0x4DC0,0x4C80,0x8C41,
-	0x4400,0x84C1,0x8581,0x4540,0x8701,0x47C0,0x4680,0x8641,
-	0x8201,0x42C0,0x4380,0x8341,0x4100,0x81C1,0x8081,0x4040
-};
-
 static int      archive_read_format_lha_bid(struct archive_read *, int);
 static int      archive_read_format_lha_options(struct archive_read *,
 		    const char *, const char *);
@@ -279,6 +238,7 @@ static int	lha_read_data_none(struct archive_read *, const void **,
 		    size_t *, int64_t *);
 static int	lha_read_data_lzh(struct archive_read *, const void **,
 		    size_t *, int64_t *);
+static void	lha_crc16_init(void);
 static uint16_t lha_crc16(uint16_t, const void *, size_t);
 static int	lzh_decode_init(struct lzh_stream *, const char *);
 static void	lzh_decode_free(struct lzh_stream *);
@@ -520,6 +480,8 @@ archive_read_format_lha_read_header(struct archive_read *a,
 	const char *signature;
 	int err;
 	
+	lha_crc16_init();
+
 	a->archive.archive_format = ARCHIVE_FORMAT_LHA;
 	if (a->archive.archive_format_name == NULL)
 		a->archive.archive_format_name = "lha";
@@ -1232,13 +1194,15 @@ lha_read_file_extended_header(struct archive_read *a, struct lha *lha,
 				archive_string_empty(&lha->filename);
 				break;
 			}
+			if (extdheader[0] == '\0')
+				goto invalid;
 			archive_strncpy(&lha->filename,
 			    (const char *)extdheader, datasize);
 			break;
 		case EXT_DIRECTORY:
-			if (datasize == 0)
+			if (datasize == 0 || extdheader[0] == '\0')
 				/* no directory name data. exit this case. */
-				break;
+				goto invalid;
 
 			archive_strncpy(&lha->dirname,
 		  	    (const char *)extdheader, datasize);
@@ -1378,6 +1342,26 @@ lha_read_file_extended_header(struct archive_read *a, struct lha *lha,
 }
 
 static int
+lha_end_of_entry(struct archive_read *a)
+{
+	struct lha *lha = (struct lha *)(a->format->data);
+	int r = ARCHIVE_EOF;
+
+	if (!lha->end_of_entry_cleanup) {
+		if ((lha->setflag & CRC_IS_SET) &&
+		    lha->crc != lha->entry_crc_calculated) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "LHa data CRC error");
+			r = ARCHIVE_WARN;
+		}
+
+		/* End-of-entry cleanup done. */
+		lha->end_of_entry_cleanup = 1;
+	}
+	return (r);
+}
+
+static int
 archive_read_format_lha_read_data(struct archive_read *a,
     const void **buff, size_t *size, int64_t *offset)
 {
@@ -1390,22 +1374,10 @@ archive_read_format_lha_read_data(struct archive_read *a,
 		lha->entry_unconsumed = 0;
 	}
 	if (lha->end_of_entry) {
-		if (!lha->end_of_entry_cleanup) {
-			if ((lha->setflag & CRC_IS_SET) &&
-			    lha->crc != lha->entry_crc_calculated) {
-				archive_set_error(&a->archive,
-				    ARCHIVE_ERRNO_MISC,
-				    "LHa data CRC error");
-				return (ARCHIVE_WARN);
-			}
-
-			/* End-of-entry cleanup done. */
-			lha->end_of_entry_cleanup = 1;
-		}
 		*offset = lha->entry_offset;
 		*size = 0;
 		*buff = NULL;
-		return (ARCHIVE_EOF);
+		return (lha_end_of_entry(a));
 	}
 
 	if (lha->entry_is_compressed)
@@ -1477,18 +1449,6 @@ lha_read_data_lzh(struct archive_read *a, const void **buff,
 	ssize_t bytes_avail;
 	int r;
 
-	/* If the buffer hasn't been allocated, allocate it now. */
-	if (lha->uncompressed_buffer == NULL) {
-		lha->uncompressed_buffer_size = 64 * 1024;
-		lha->uncompressed_buffer
-		    = (unsigned char *)malloc(lha->uncompressed_buffer_size);
-		if (lha->uncompressed_buffer == NULL) {
-			archive_set_error(&a->archive, ENOMEM,
-			    "No memory for lzh decompression");
-			return (ARCHIVE_FATAL);
-		}
-	}
-
 	/* If we haven't yet read any data, initialize the decompressor. */
 	if (!lha->decompress_init) {
 		r = lzh_decode_init(&(lha->strm), lha->method);
@@ -1534,12 +1494,9 @@ lha_read_data_lzh(struct archive_read *a, const void **buff,
 	if (bytes_avail > lha->entry_bytes_remaining)
 		bytes_avail = (ssize_t)lha->entry_bytes_remaining;
 
-	lha->strm.avail_in = bytes_avail;
+	lha->strm.avail_in = (int)bytes_avail;
 	lha->strm.total_in = 0;
-	if (lha->strm.avail_out == 0) {
-		lha->strm.next_out = lha->uncompressed_buffer;
-		lha->strm.avail_out = lha->uncompressed_buffer_size;
-	}
+	lha->strm.avail_out = 0;
 
 	r = lzh_decode(&(lha->strm), bytes_avail == lha->entry_bytes_remaining);
 	switch (r) {
@@ -1556,17 +1513,19 @@ lha_read_data_lzh(struct archive_read *a, const void **buff,
 	lha->entry_unconsumed = lha->strm.total_in;
 	lha->entry_bytes_remaining -= lha->strm.total_in;
 
-	if (lha->strm.avail_out == 0 || lha->end_of_entry) {
+	if (lha->strm.avail_out) {
 		*offset = lha->entry_offset;
-		*size = lha->strm.next_out - lha->uncompressed_buffer;
-		*buff = lha->uncompressed_buffer;
+		*size = lha->strm.avail_out;
+		*buff = lha->strm.ref_ptr;
 		lha->entry_crc_calculated =
 		    lha_crc16(lha->entry_crc_calculated, *buff, *size);
 		lha->entry_offset += *size;
 	} else {
 		*offset = lha->entry_offset;
 		*size = 0;
 		*buff = NULL;
+		if (lha->end_of_entry)
+			return (lha_end_of_entry(a));
 	}
 	return (ARCHIVE_OK);
 }
@@ -1611,7 +1570,6 @@ archive_read_format_lha_cleanup(struct archive_read *a)
 	struct lha *lha = (struct lha *)(a->format->data);
 
 	lzh_decode_free(&(lha->strm));
-	free(lha->uncompressed_buffer);
 	archive_string_free(&(lha->dirname));
 	archive_string_free(&(lha->filename));
 	archive_string_free(&(lha->uname));
@@ -1702,50 +1660,87 @@ lha_calcsum(unsigned char sum, const void *pp, int offset, size_t size)
 	return (sum);
 }
 
-#define CRC16(crc, v)	do {	\
-	(crc) = crc16tbl[((crc) ^ v) & 0xFF] ^ ((crc) >> 8);	\
-} while (0)
+static uint16_t crc16tbl[2][256];
+static void
+lha_crc16_init(void)
+{
+	unsigned int i;
+	static int crc16init = 0;
+
+	if (crc16init)
+		return;
+	crc16init = 1;
+
+	for (i = 0; i < 256; i++) {
+		unsigned int j;
+		uint16_t crc = (uint16_t)i;
+		for (j = 8; j; j--)
+			crc = (crc >> 1) ^ ((crc & 1) * 0xA001);
+		crc16tbl[0][i] = crc;
+	}
+
+	for (i = 0; i < 256; i++) {
+		crc16tbl[1][i] = (crc16tbl[0][i] >> 8)
+			^ crc16tbl[0][crc16tbl[0][i] & 0xff];
+	}
+}
 
 static uint16_t
 lha_crc16(uint16_t crc, const void *pp, size_t len)
 {
-	const unsigned char *buff = (const unsigned char *)pp;
-
-	while (len >= 8) {
-		CRC16(crc, *buff++); CRC16(crc, *buff++);
-		CRC16(crc, *buff++); CRC16(crc, *buff++);
-		CRC16(crc, *buff++); CRC16(crc, *buff++);
-		CRC16(crc, *buff++); CRC16(crc, *buff++);
-		len -= 8;
+	const unsigned char *p = (const unsigned char *)pp;
+	const uint16_t *buff;
+	const union {
+		uint32_t i;
+		char c[4];
+	} u = { 0x01020304 };
+
+	if (len == 0)
+		return crc;
+
+	/* Process unaligned address. */
+	if (((uintptr_t)p) & (uintptr_t)0x1) {
+		crc = (crc >> 8) ^ crc16tbl[0][(crc ^ *p++) & 0xff];
+		len--;
 	}
-	switch (len) {
-	case 7:
-		CRC16(crc, *buff++);
-		/* FALL THROUGH */
-	case 6:
-		CRC16(crc, *buff++);
-		/* FALL THROUGH */
-	case 5:
-		CRC16(crc, *buff++);
-		/* FALL THROUGH */
-	case 4:
-		CRC16(crc, *buff++);
-		/* FALL THROUGH */
-	case 3:
-		CRC16(crc, *buff++);
-		/* FALL THROUGH */
-	case 2:
-		CRC16(crc, *buff++);
-		/* FALL THROUGH */
-	case 1:
-		CRC16(crc, *buff);
-		/* FALL THROUGH */
-	case 0:
-		break;
+	buff = (const uint16_t *)p;
+	/*
+	 * Modern C compiler such as GCC does not unroll automatically yet
+	 * without unrolling pragma, and Clang is so. So we should
+	 * unroll this loop for its performance.
+	 */
+	for (;len >= 8; len -= 8) {
+		/* This if statement expects compiler optimization will
+		 * remove the stament which will not be executed. */
+#ifdef _MSC_VER  /* Visual Studio */
+#  define bswap16(x) _byteswap_ushort(x)
+#elif (defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 8) \
+      || defined(__clang__)
+#  define bswap16(x) __builtin_bswap16(x)
+#else
+#  define bswap16(x) ((((x) >> 8) & 0xff) | ((x) << 8))
+#endif
+#define CRC16W	do { 	\
+		if(u.c[0] == 1) { /* Big endian */		\
+			crc ^= bswap16(*buff); buff++;		\
+		} else						\
+			crc ^= *buff++;				\
+		crc = crc16tbl[1][crc & 0xff] ^ crc16tbl[0][crc >> 8];\
+} while (0)
+		CRC16W;
+		CRC16W;
+		CRC16W;
+		CRC16W;
+#undef CRC16W
+#undef bswap16
 	}
-	return (crc);
-}
 
+	p = (const unsigned char *)buff;
+	for (;len; len--) {
+		crc = (crc >> 8) ^ crc16tbl[0][(crc ^ *p++) & 0xff];
+	}
+	return crc;
+}
 
 /*
  * Initialize LZHUF decoder.
@@ -1784,18 +1779,18 @@ lzh_decode_init(struct lzh_stream *strm, const char *method)
 		return (ARCHIVE_FAILED);/* Not supported. */
 	}
 	ds->error = ARCHIVE_FATAL;
-	w_size = ds->w_size;
-	ds->w_size = 1U << w_bits;
+	/* Expand a window size up to 128 KiB for decompressing process
+	 * performance whatever its original window size is. */
+	ds->w_size = 1U << 17;
 	ds->w_mask = ds->w_size -1;
-	if (ds->w_buff == NULL || w_size != ds->w_size) {
-		free(ds->w_buff);
+	if (ds->w_buff == NULL) {
 		ds->w_buff = malloc(ds->w_size);
 		if (ds->w_buff == NULL)
 			return (ARCHIVE_FATAL);
 	}
-	memset(ds->w_buff, 0x20, ds->w_size);
+	w_size = 1U << w_bits;
+	memset(ds->w_buff + ds->w_size - w_size, 0x20, w_size);
 	ds->w_pos = 0;
-	ds->w_remaining = 0;
 	ds->state = 0;
 	ds->pos_pt_len_size = w_bits + 1;
 	ds->pos_pt_len_bits = (w_bits == 15 || w_bits == 16)? 5: 4;
@@ -1882,9 +1877,10 @@ lzh_br_fillup(struct lzh_stream *strm, struct lzh_br *br)
 	int n = CACHE_BITS - br->cache_avail;
 
 	for (;;) {
-		switch (n >> 3) {
-		case 8:
-			if (strm->avail_in >= 8) {
+		const int x = n >> 3;
+		if (strm->avail_in >= x) {
+			switch (x) {
+			case 8:
 				br->cache_buffer =
 				    ((uint64_t)strm->next_in[0]) << 56 |
 				    ((uint64_t)strm->next_in[1]) << 48 |
@@ -1898,10 +1894,7 @@ lzh_br_fillup(struct lzh_stream *strm, struct lzh_br *br)
 				strm->avail_in -= 8;
 				br->cache_avail += 8 * 8;
 				return (1);
-			}
-			break;
-		case 7:
-			if (strm->avail_in >= 7) {
+			case 7:
 				br->cache_buffer =
 		 		   (br->cache_buffer << 56) |
 				    ((uint64_t)strm->next_in[0]) << 48 |
@@ -1915,10 +1908,7 @@ lzh_br_fillup(struct lzh_stream *strm, struct lzh_br *br)
 				strm->avail_in -= 7;
 				br->cache_avail += 7 * 8;
 				return (1);
-			}
-			break;
-		case 6:
-			if (strm->avail_in >= 6) {
+			case 6:
 				br->cache_buffer =
 		 		   (br->cache_buffer << 48) |
 				    ((uint64_t)strm->next_in[0]) << 40 |
@@ -1931,14 +1921,13 @@ lzh_br_fillup(struct lzh_stream *strm, struct lzh_br *br)
 				strm->avail_in -= 6;
 				br->cache_avail += 6 * 8;
 				return (1);
+			case 0:
+				/* We have enough compressed data in
+				 * the cache buffer.*/
+				return (1);
+			default:
+				break;
 			}
-			break;
-		case 0:
-			/* We have enough compressed data in
-			 * the cache buffer.*/ 
-			return (1);
-		default:
-			break;
 		}
 		if (strm->avail_in == 0) {
 			/* There is not enough compressed data to fill up the
@@ -1993,7 +1982,7 @@ static int
 lzh_decode(struct lzh_stream *strm, int last)
 {
 	struct lzh_dec *ds = strm->ds;
-	int64_t avail_in;
+	int avail_in;
 	int r;
 
 	if (ds->error)
@@ -2010,35 +1999,12 @@ lzh_decode(struct lzh_stream *strm, int last)
 	return (r);
 }
 
-static int
-lzh_copy_from_window(struct lzh_stream *strm, struct lzh_dec *ds)
+static void
+lzh_emit_window(struct lzh_stream *strm, size_t s)
 {
-	size_t copy_bytes;
-
-	if (ds->w_remaining == 0 && ds->w_pos > 0) {
-		if (ds->w_pos - ds->copy_pos <= strm->avail_out)
-			copy_bytes = ds->w_pos - ds->copy_pos;
-		else
-			copy_bytes = (size_t)strm->avail_out;
-		memcpy(strm->next_out,
-		    ds->w_buff + ds->copy_pos, copy_bytes);
-		ds->copy_pos += (int)copy_bytes;
-	} else {
-		if (ds->w_remaining <= strm->avail_out)
-			copy_bytes = ds->w_remaining;
-		else
-			copy_bytes = (size_t)strm->avail_out;
-		memcpy(strm->next_out,
-		    ds->w_buff + ds->w_size - ds->w_remaining, copy_bytes);
-		ds->w_remaining -= (int)copy_bytes;
-	}
-	strm->next_out += copy_bytes;
-	strm->avail_out -= copy_bytes;
-	strm->total_out += copy_bytes;
-	if (strm->avail_out == 0)
-		return (0);
-	else
-		return (1);
+	strm->ref_ptr = strm->ds->w_buff;
+	strm->avail_out = (int)s;
+	strm->total_out += s;
 }
 
 static int
@@ -2073,8 +2039,9 @@ lzh_read_blocks(struct lzh_stream *strm, int last)
 					goto failed;
 				}
 				if (ds->w_pos > 0) {
-					if (!lzh_copy_from_window(strm, ds))
-						return (ARCHIVE_OK);
+					lzh_emit_window(strm, ds->w_pos);
+					ds->w_pos = 0;
+					return (ARCHIVE_OK);
 				}
 				/* End of compressed data; we have completely
 				 * handled all compressed data. */
@@ -2291,10 +2258,6 @@ lzh_decode_blocks(struct lzh_stream *strm, int last)
 	int lt_max_bits = lt->max_bits, pt_max_bits = pt->max_bits;
 	int state = ds->state;
 
-	if (ds->w_remaining > 0) {
-		if (!lzh_copy_from_window(strm, ds))
-			goto next_data;
-	}
 	for (;;) {
 		switch (state) {
 		case ST_GET_LITERAL:
@@ -2349,9 +2312,8 @@ lzh_decode_blocks(struct lzh_stream *strm, int last)
 				w_buff[w_pos] = c;
 				if (++w_pos >= w_size) {
 					w_pos = 0;
-					ds->w_remaining = w_size;
-					if (!lzh_copy_from_window(strm, ds))
-						goto next_data;
+					lzh_emit_window(strm, w_size);
+					goto next_data;
 				}
 			}
 			/* 'c' is the length of a match pattern we have
@@ -2429,25 +2391,26 @@ lzh_decode_blocks(struct lzh_stream *strm, int last)
 
 					d = w_buff + w_pos;
 					s = w_buff + copy_pos;
-					for (li = 0; li < l; li++)
+					for (li = 0; li < l-1;) {
+						d[li] = s[li];li++;
+						d[li] = s[li];li++;
+					}
+					if (li < l)
 						d[li] = s[li];
 				}
-				w_pos = (w_pos + l) & w_mask;
-				if (w_pos == 0) {
-					ds->w_remaining = w_size;
-					if (!lzh_copy_from_window(strm, ds)) {
-						if (copy_len <= l)
-							state = ST_GET_LITERAL;
-						else {
-							state = ST_COPY_DATA;
-							ds->copy_len =
-							    copy_len - l;
-							ds->copy_pos =
-							    (copy_pos + l)
-							    & w_mask;
-						}
-						goto next_data;
+				w_pos += l;
+				if (w_pos == w_size) {
+					w_pos = 0;
+					lzh_emit_window(strm, w_size);
+					if (copy_len <= l)
+						state = ST_GET_LITERAL;
+					else {
+						state = ST_COPY_DATA;
+						ds->copy_len = copy_len - l;
+						ds->copy_pos =
+						    (copy_pos + l) & w_mask;
 					}
+					goto next_data;
 				}
 				if (copy_len <= l)
 					/* A copy of current pattern ended. */
@@ -2507,14 +2470,80 @@ lzh_huffman_free(struct huffman *hf)
 	free(hf->tree);
 }
 
+static char bitlen_tbl[0x400] = {
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
+	10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
+	10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
+	10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
+	10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
+	11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
+	11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
+	12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
+	13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 16,  0
+};
 static int
 lzh_read_pt_bitlen(struct lzh_stream *strm, int start, int end)
 {
 	struct lzh_dec *ds = strm->ds;
-	struct lzh_br * br = &(ds->br);
+	struct lzh_br *br = &(ds->br);
 	int c, i;
 
-	for (i = start; i < end;) {
+	for (i = start; i < end; ) {
 		/*
 		 *  bit pattern     the number we need
 		 *     000           ->  0
@@ -2530,17 +2559,13 @@ lzh_read_pt_bitlen(struct lzh_stream *strm, int start, int end)
 		if (!lzh_br_read_ahead(strm, br, 3))
 			return (i);
 		if ((c = lzh_br_bits(br, 3)) == 7) {
-			int d;
 			if (!lzh_br_read_ahead(strm, br, 13))
 				return (i);
-			d = lzh_br_bits(br, 13);
-			while (d & 0x200) {
-				c++;
-				d <<= 1;
-			}
-			if (c > 16)
+			c = bitlen_tbl[lzh_br_bits(br, 13) & 0x3FF];
+			if (c)
+				lzh_br_consume(br, c - 3);
+			else
 				return (-1);/* Invalid data. */
-			lzh_br_consume(br, c - 3);
 		} else
 			lzh_br_consume(br, 3);
 		ds->pt.bitlen[i++] = c;
@@ -2603,7 +2628,7 @@ lzh_make_huffman_table(struct huffman *hf)
 		}
 	}
 	if (maxbits > HTBL_BITS) {
-		int htbl_max;
+		unsigned htbl_max;
 		uint16_t *p;
 
 		diffbits = maxbits - HTBL_BITS;
@@ -2647,8 +2672,40 @@ lzh_make_huffman_table(struct huffman *hf)
 				return (0);/* Invalid */
 			/* Update the table */
 			p = &(tbl[ptn]);
-			while (--cnt >= 0)
-				p[cnt] = (uint16_t)i;
+			if (cnt > 7) {
+				uint16_t *pc;
+
+				cnt -= 8;
+				pc = &p[cnt];
+				pc[0] = (uint16_t)i;
+				pc[1] = (uint16_t)i;
+				pc[2] = (uint16_t)i;
+				pc[3] = (uint16_t)i;
+				pc[4] = (uint16_t)i;
+				pc[5] = (uint16_t)i;
+				pc[6] = (uint16_t)i;
+				pc[7] = (uint16_t)i;
+				if (cnt > 7) {
+					cnt -= 8;
+					memcpy(&p[cnt], pc,
+						8 * sizeof(uint16_t));
+					pc = &p[cnt];
+					while (cnt > 15) {
+						cnt -= 16;
+						memcpy(&p[cnt], pc,
+							16 * sizeof(uint16_t));
+					}
+				}
+				if (cnt)
+					memcpy(p, pc, cnt * sizeof(uint16_t));
+			} else {
+				while (cnt > 1) {
+					p[--cnt] = (uint16_t)i;
+					p[--cnt] = (uint16_t)i;
+				}
+				if (cnt)
+					p[--cnt] = (uint16_t)i;
+			}
 			continue;
 		}
 
@@ -2742,7 +2799,7 @@ lzh_decode_huffman(struct huffman *hf, unsigned rbits)
 	 * If it fails, search a huffman tree for.
 	 */
 	c = hf->tbl[rbits >> hf->shift_bits];
-	if (c < hf->len_avail)
+	if (c < hf->len_avail || hf->len_avail == 0)
 		return (c);
 	/* This bit pattern needs to be found out at a huffman tree. */
 	return (lzh_decode_huffman_tree(hf, rbits, c));