@@ -47,7 +47,7 @@ __FBSDID("$FreeBSD$");
 #endif
 
 #include "archive.h"
-#include "archive_crypto_private.h"
+#include "archive_digest_private.h"
 #include "archive_endian.h"
 #include "archive_entry.h"
 #include "archive_entry_locale.h"
@@ -114,7 +114,7 @@ enum sumalg {
 #define MAX_SUM_SIZE	20
 #define MD5_NAME	"md5"
 #define SHA1_NAME	"sha1"
- 
+
 enum enctype {
 	NONE,
 	GZIP,
@@ -242,6 +242,7 @@ struct xar {
 	enum sumalg		 opt_sumalg;
 	enum enctype		 opt_compression;
 	int			 opt_compression_level;
+	uint32_t		 opt_threads;
 
 	struct chksumwork	 a_sumwrk;	/* archived checksum.	*/
 	struct chksumwork	 e_sumwrk;	/* extracted checksum.	*/
@@ -317,7 +318,7 @@ static int	compression_end_bzip2(struct archive *, struct la_zstream *);
 static int	compression_init_encoder_lzma(struct archive *,
 		    struct la_zstream *, int);
 static int	compression_init_encoder_xz(struct archive *,
-		    struct la_zstream *, int);
+		    struct la_zstream *, int, int);
 #if defined(HAVE_LZMA_H)
 static int	compression_code_lzma(struct archive *,
 		    struct la_zstream *, enum la_zaction);
@@ -380,9 +381,10 @@ archive_write_set_format_xar(struct archive *_a)
 	/* Set default checksum type. */
 	xar->opt_toc_sumalg = CKSUM_SHA1;
 	xar->opt_sumalg = CKSUM_SHA1;
-	/* Set default compression type and level. */
+	/* Set default compression type, level, and number of threads. */
 	xar->opt_compression = GZIP;
 	xar->opt_compression_level = 6;
+	xar->opt_threads = 1;
 
 	a->format_data = xar;
 
@@ -493,6 +495,26 @@ xar_options(struct archive_write *a, const char *key, const char *value)
 		}
 		return (ARCHIVE_OK);
 	}
+	if (strcmp(key, "threads") == 0) {
+		if (value == NULL)
+			return (ARCHIVE_FAILED);
+		xar->opt_threads = (int)strtoul(value, NULL, 10);
+		if (xar->opt_threads == 0 && errno != 0) {
+			xar->opt_threads = 1;
+			archive_set_error(&(a->archive),
+			    ARCHIVE_ERRNO_MISC,
+			    "Illegal value `%s'",
+			    value);
+			return (ARCHIVE_FAILED);
+		}
+		if (xar->opt_threads == 0) {
+#ifdef HAVE_LZMA_STREAM_ENCODER_MT
+			xar->opt_threads = lzma_cputhreads();
+#else
+			xar->opt_threads = 1;
+#endif
+		}
+	}
 
 	/* Note: The "warn" return is just to inform the options
 	 * supervisor that we didn't handle it.  It will generate
@@ -805,7 +827,7 @@ xmlwrite_string(struct archive_write *a, xmlTextWriterPtr writer,
 
 	if (value == NULL)
 		return (ARCHIVE_OK);
-	
+
 	r = xmlTextWriterStartElement(writer, BAD_CAST_CONST(key));
 	if (r < 0) {
 		archive_set_error(&a->archive,
@@ -1875,7 +1897,7 @@ file_cmp_node(const struct archive_rb_node *n1,
 
 	return (strcmp(f1->basename.s, f2->basename.s));
 }
-        
+
 static int
 file_cmp_key(const struct archive_rb_node *n, const void *key)
 {
@@ -2154,7 +2176,7 @@ file_gen_utility_names(struct archive_write *a, struct file *file)
 		file->parentdir.length = len;
 		archive_string_copy(&(file->basename), &(file->parentdir));
 		archive_string_empty(&(file->parentdir));
-		file->parentdir.s = '\0';
+		*file->parentdir.s = '\0';
 		return (r);
 	}
 
@@ -2494,7 +2516,7 @@ file_init_hardlinks(struct xar *xar)
 	static const struct archive_rb_tree_ops rb_ops = {
 		file_hd_cmp_node, file_hd_cmp_key,
 	};
- 
+
 	__archive_rb_tree_init(&(xar->hardlink_rbtree), &rb_ops);
 }
 
@@ -2848,13 +2870,18 @@ compression_init_encoder_lzma(struct archive *a,
 
 static int
 compression_init_encoder_xz(struct archive *a,
-    struct la_zstream *lastrm, int level)
+    struct la_zstream *lastrm, int level, int threads)
 {
 	static const lzma_stream lzma_init_data = LZMA_STREAM_INIT;
 	lzma_stream *strm;
 	lzma_filter *lzmafilters;
 	lzma_options_lzma lzma_opt;
 	int r;
+#ifdef HAVE_LZMA_STREAM_ENCODER_MT
+	lzma_mt mt_options;
+#endif
+
+	(void)threads; /* UNUSED (if multi-threaded LZMA library not avail) */
 
 	if (lastrm->valid)
 		compression_end(a, lastrm);
@@ -2879,7 +2906,17 @@ compression_init_encoder_xz(struct archive *a,
 	lzmafilters[1].id = LZMA_VLI_UNKNOWN;/* Terminate */
 
 	*strm = lzma_init_data;
-	r = lzma_stream_encoder(strm, lzmafilters, LZMA_CHECK_CRC64);
+#ifdef HAVE_LZMA_STREAM_ENCODER_MT
+	if (threads > 1) {
+		bzero(&mt_options, sizeof(mt_options));
+		mt_options.threads = threads;
+		mt_options.timeout = 300;
+		mt_options.filters = lzmafilters;
+		mt_options.check = LZMA_CHECK_CRC64;
+		r = lzma_stream_encoder_mt(strm, &mt_options);
+	} else
+#endif
+		r = lzma_stream_encoder(strm, lzmafilters, LZMA_CHECK_CRC64);
 	switch (r) {
 	case LZMA_OK:
 		lastrm->real_stream = strm;
@@ -2979,10 +3016,11 @@ compression_init_encoder_lzma(struct archive *a,
 }
 static int
 compression_init_encoder_xz(struct archive *a,
-    struct la_zstream *lastrm, int level)
+    struct la_zstream *lastrm, int level, int threads)
 {
 
 	(void) level; /* UNUSED */
+	(void) threads; /* UNUSED */
 	if (lastrm->valid)
 		compression_end(a, lastrm);
 	return (compression_unsupported_encoder(a, lastrm, "xz"));
@@ -3015,7 +3053,7 @@ xar_compression_init_encoder(struct archive_write *a)
 	case XZ:
 		r = compression_init_encoder_xz(
 		    &(a->archive), &(xar->stream),
-		    xar->opt_compression_level);
+		    xar->opt_compression_level, xar->opt_threads);
 		break;
 	default:
 		r = ARCHIVE_OK;
@@ -3178,4 +3216,3 @@ getalgname(enum sumalg sumalg)
 }
 
 #endif /* Support xar format */
-