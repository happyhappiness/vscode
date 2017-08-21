@@ -43,8 +43,6 @@ __FBSDID("$FreeBSD$");
 #endif
 #if HAVE_LZMA_H
 #include <cm_lzma.h>
-#elif HAVE_LZMADEC_H
-#include <lzmadec.h>
 #endif
 #ifdef HAVE_ZLIB_H
 #include <cm_zlib.h>
@@ -334,9 +332,6 @@ struct xar {
 #if HAVE_LZMA_H && HAVE_LIBLZMA
 	lzma_stream		 lzstream;
 	int			 lzstream_valid;
-#elif HAVE_LZMADEC_H && HAVE_LIBLZMADEC
-	lzmadec_stream		 lzstream;
-	int			 lzstream_valid;
 #endif
 	/*
 	 * For Checksum data.
@@ -399,6 +394,7 @@ static void	checksum_update(struct archive_read *, const void *,
 		    size_t, const void *, size_t);
 static int	checksum_final(struct archive_read *, const void *,
 		    size_t, const void *, size_t);
+static void	checksum_cleanup(struct archive_read *);
 static int	decompression_init(struct archive_read *, enum enctype);
 static int	decompress(struct archive_read *, const void **,
 		    size_t *, const void *, size_t *);
@@ -928,6 +924,7 @@ xar_cleanup(struct archive_read *a)
 	int r;
 
 	xar = (struct xar *)(a->format->data);
+	checksum_cleanup(a);
 	r = decompression_cleanup(a);
 	hdlink = xar->hdlink_list;
 	while (hdlink != NULL) {
@@ -938,6 +935,7 @@ xar_cleanup(struct archive_read *a)
 	}
 	for (i = 0; i < xar->file_queue.used; i++)
 		file_free(xar->file_queue.files[i]);
+	free(xar->file_queue.files);
 	while (xar->unknowntags != NULL) {
 		struct unknown_tag *tag;
 
@@ -1526,34 +1524,6 @@ decompression_init(struct archive_read *a, enum enctype encoding)
 		xar->lzstream.total_in = 0;
 		xar->lzstream.total_out = 0;
 		break;
-#elif defined(HAVE_LZMADEC_H) && defined(HAVE_LIBLZMADEC)
-	case LZMA:
-		if (xar->lzstream_valid)
-			lzmadec_end(&(xar->lzstream));
-		r = lzmadec_init(&(xar->lzstream));
-		if (r != LZMADEC_OK) {
-			switch (r) {
-			case LZMADEC_HEADER_ERROR:
-				archive_set_error(&a->archive,
-				    ARCHIVE_ERRNO_MISC,
-				    "Internal error initializing "
-				    "compression library: "
-				    "invalid header");
-				break;
-			case LZMADEC_MEM_ERROR:
-				archive_set_error(&a->archive,
-				    ENOMEM,
-				    "Internal error initializing "
-				    "compression library: "
-				    "out of memory");
-				break;
-			}
-			return (ARCHIVE_FATAL);
-		}
-		xar->lzstream_valid = 1;
-		xar->lzstream.total_in = 0;
-		xar->lzstream.total_out = 0;
-		break;
 #endif
 	/*
 	 * Unsupported compression.
@@ -1563,9 +1533,7 @@ decompression_init(struct archive_read *a, enum enctype encoding)
 	case BZIP2:
 #endif
 #if !defined(HAVE_LZMA_H) || !defined(HAVE_LIBLZMA)
-#if !defined(HAVE_LZMADEC_H) || !defined(HAVE_LIBLZMADEC)
 	case LZMA:
-#endif
 	case XZ:
 #endif
 		switch (xar->entry_encoding) {
@@ -1685,46 +1653,12 @@ decompress(struct archive_read *a, const void **buff, size_t *outbytes,
 		*used = avail_in - xar->lzstream.avail_in;
 		*outbytes = avail_out - xar->lzstream.avail_out;
 		break;
-#elif defined(HAVE_LZMADEC_H) && defined(HAVE_LIBLZMADEC)
-	case LZMA:
-		xar->lzstream.next_in = (unsigned char *)(uintptr_t)b;
-		xar->lzstream.avail_in = avail_in;
-		xar->lzstream.next_out = (unsigned char *)outbuff;
-		xar->lzstream.avail_out = avail_out;
-		r = lzmadec_decode(&(xar->lzstream), 0);
-		switch (r) {
-		case LZMADEC_STREAM_END: /* Found end of stream. */
-			switch (lzmadec_end(&(xar->lzstream))) {
-			case LZMADEC_OK:
-				break;
-			default:
-				archive_set_error(&(a->archive),
-				    ARCHIVE_ERRNO_MISC,
-				    "Failed to clean up lzmadec decompressor");
-				return (ARCHIVE_FATAL);
-			}
-			xar->lzstream_valid = 0;
-			/* FALLTHROUGH */
-		case LZMADEC_OK: /* Decompressor made some progress. */
-			break;
-		default:
-			archive_set_error(&(a->archive),
-			    ARCHIVE_ERRNO_MISC,
-			    "lzmadec decompression failed(%d)",
-			    r);
-			return (ARCHIVE_FATAL);
-		}
-		*used = avail_in - xar->lzstream.avail_in;
-		*outbytes = avail_out - xar->lzstream.avail_out;
-		break;
 #endif
 #if !defined(HAVE_BZLIB_H) || !defined(BZ_CONFIG_ERROR)
 	case BZIP2:
 #endif
 #if !defined(HAVE_LZMA_H) || !defined(HAVE_LIBLZMA)
-#if !defined(HAVE_LZMADEC_H) || !defined(HAVE_LIBLZMADEC)
 	case LZMA:
-#endif
 	case XZ:
 #endif
 	case NONE:
@@ -1788,6 +1722,16 @@ decompression_cleanup(struct archive_read *a)
 }
 
 static void
+checksum_cleanup(struct archive_read *a) {
+	struct xar *xar;
+
+	xar = (struct xar *)(a->format->data);
+
+	_checksum_final(&(xar->a_sumwrk), NULL, 0);
+	_checksum_final(&(xar->e_sumwrk), NULL, 0);
+}
+
+static void
 xmlattr_cleanup(struct xmlattr_list *list)
 {
 	struct xmlattr *attr, *next;
@@ -3116,7 +3060,7 @@ xml2_read_cb(void *context, char *buffer, int len)
 	struct xar *xar;
 	const void *d;
 	size_t outbytes;
-	size_t used;
+	size_t used = 0;
 	int r;
 
 	a = (struct archive_read *)context;
@@ -3240,6 +3184,9 @@ expat_xmlattr_setup(struct archive_read *a,
 		value = strdup(atts[1]);
 		if (attr == NULL || name == NULL || value == NULL) {
 			archive_set_error(&a->archive, ENOMEM, "Out of memory");
+			free(attr);
+			free(name);
+			free(value);
 			return (ARCHIVE_FATAL);
 		}
 		attr->name = name;