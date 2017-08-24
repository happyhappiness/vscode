@@ -1,5 +1,5 @@
 /*-
- * Copyright (c) 2008-2011 Michihiro NAKAJIMA
+ * Copyright (c) 2008-2012 Michihiro NAKAJIMA
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -272,7 +272,7 @@ static int	lha_skip_sfx(struct archive_read *);
 static time_t	lha_dos_time(const unsigned char *);
 static time_t	lha_win_time(uint64_t, long *);
 static unsigned char	lha_calcsum(unsigned char, const void *,
-		    int, int);
+		    int, size_t);
 static int	lha_parse_linkname(struct archive_string *,
 		    struct archive_string *);
 static int	lha_read_data_none(struct archive_read *, const void **,
@@ -289,7 +289,7 @@ static void	lzh_huffman_free(struct huffman *);
 static int	lzh_read_pt_bitlen(struct lzh_stream *, int start, int end);
 static int	lzh_make_fake_table(struct huffman *, uint16_t);
 static int	lzh_make_huffman_table(struct huffman *);
-static int inline lzh_decode_huffman(struct huffman *, unsigned);
+static inline int lzh_decode_huffman(struct huffman *, unsigned);
 static int	lzh_decode_huffman_tree(struct huffman *, unsigned, int);
 
 
@@ -319,6 +319,7 @@ archive_read_support_format_lha(struct archive *_a)
 	    archive_read_format_lha_read_header,
 	    archive_read_format_lha_read_data,
 	    archive_read_format_lha_read_data_skip,
+	    NULL,
 	    archive_read_format_lha_cleanup);
 
 	if (r != ARCHIVE_OK)
@@ -445,11 +446,13 @@ archive_read_format_lha_options(struct archive_read *a,
 			else
 				ret = ARCHIVE_FATAL;
 		}
-	} else
-		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-		    "lha: unknown keyword ``%s''", key);
+		return (ret);
+	}
 
-	return (ret);
+	/* Note: The "warn" return is just to inform the options
+	 * supervisor that we didn't handle it.  It will generate
+	 * a suitable error if no one used this option. */
+	return (ARCHIVE_WARN);
 }
 
 static int
@@ -696,7 +699,7 @@ archive_read_format_lha_read_header(struct archive_read *a,
 		archive_entry_set_symlink(entry, NULL);
 	archive_string_free(&linkname);
 	/*
-	 * When a header level is 0, there is a possibilty that
+	 * When a header level is 0, there is a possibility that
 	 * a pathname and a symlink has '\' character, a directory
 	 * separator in DOS/Windows. So we should convert it to '/'.
 	 */
@@ -949,7 +952,7 @@ lha_read_file_header_1(struct archive_read *a, struct lha *lha)
 
 	/* Read extended headers */
 	err2 = lha_read_file_extended_header(a, lha, NULL, 2,
-	    lha->compsize + 2, &extdsize);
+	    (size_t)(lha->compsize + 2), &extdsize);
 	if (err2 < ARCHIVE_WARN)
 		return (err2);
 	if (err2 < err)
@@ -1444,7 +1447,7 @@ lha_read_data_none(struct archive_read *a, const void **buff,
 		return (ARCHIVE_FATAL);
 	}
 	if (bytes_avail > lha->entry_bytes_remaining)
-		bytes_avail = lha->entry_bytes_remaining;
+		bytes_avail = (ssize_t)lha->entry_bytes_remaining;
 	lha->entry_crc_calculated =
 	    lha_crc16(lha->entry_crc_calculated, *buff, bytes_avail);
 	*size = bytes_avail;
@@ -1527,7 +1530,7 @@ lha_read_data_lzh(struct archive_read *a, const void **buff,
 		return (ARCHIVE_FATAL);
 	}
 	if (bytes_avail > lha->entry_bytes_remaining)
-		bytes_avail = lha->entry_bytes_remaining;
+		bytes_avail = (ssize_t)lha->entry_bytes_remaining;
 
 	lha->strm.avail_in = bytes_avail;
 	lha->strm.total_in = 0;
@@ -1573,7 +1576,7 @@ static int
 archive_read_format_lha_read_data_skip(struct archive_read *a)
 {
 	struct lha *lha;
-	off_t bytes_skipped;
+	int64_t bytes_skipped;
 
 	lha = (struct lha *)(a->format->data);
 
@@ -1632,7 +1635,7 @@ lha_parse_linkname(struct archive_string *linkname,
     struct archive_string *pathname)
 {
 	char *	linkptr;
-	int 	symlen;
+	size_t 	symlen;
 
 	linkptr = strchr(pathname->s, '|');
 	if (linkptr != NULL) {
@@ -1687,12 +1690,12 @@ lha_win_time(uint64_t wintime, long *ns)
 }
 
 static unsigned char
-lha_calcsum(unsigned char sum, const void *pp, int offset, int size)
+lha_calcsum(unsigned char sum, const void *pp, int offset, size_t size)
 {
 	unsigned char const *p = (unsigned char const *)pp;
 
 	p += offset;
-	while (--size >= 0)
+	for (;size > 0; --size)
 		sum += *p++;
 	return (sum);
 }
@@ -2014,18 +2017,18 @@ lzh_copy_from_window(struct lzh_stream *strm, struct lzh_dec *ds)
 		if (ds->w_pos - ds->copy_pos <= strm->avail_out)
 			copy_bytes = ds->w_pos - ds->copy_pos;
 		else
-			copy_bytes = strm->avail_out;
+			copy_bytes = (size_t)strm->avail_out;
 		memcpy(strm->next_out,
 		    ds->w_buff + ds->copy_pos, copy_bytes);
-		ds->copy_pos += copy_bytes;
+		ds->copy_pos += (int)copy_bytes;
 	} else {
 		if (ds->w_remaining <= strm->avail_out)
 			copy_bytes = ds->w_remaining;
 		else
-			copy_bytes = strm->avail_out;
+			copy_bytes = (size_t)strm->avail_out;
 		memcpy(strm->next_out,
 		    ds->w_buff + ds->w_size - ds->w_remaining, copy_bytes);
-		ds->w_remaining -= copy_bytes;
+		ds->w_remaining -= (int)copy_bytes;
 	}
 	strm->next_out += copy_bytes;
 	strm->avail_out -= copy_bytes;
@@ -2479,7 +2482,7 @@ lzh_huffman_init(struct huffman *hf, size_t len_size, int tbl_bits)
 			bits = tbl_bits;
 		else
 			bits = HTBL_BITS;
-		hf->tbl = malloc((1 << bits) * sizeof(hf->tbl[0]));
+		hf->tbl = malloc(((size_t)1 << bits) * sizeof(hf->tbl[0]));
 		if (hf->tbl == NULL)
 			return (ARCHIVE_FATAL);
 	}
@@ -2489,7 +2492,7 @@ lzh_huffman_init(struct huffman *hf, size_t len_size, int tbl_bits)
 		if (hf->tree == NULL)
 			return (ARCHIVE_FATAL);
 	}
-	hf->len_size = len_size;
+	hf->len_size = (int)len_size;
 	hf->tbl_bits = tbl_bits;
 	return (ARCHIVE_OK);
 }