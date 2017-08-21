@@ -924,6 +924,9 @@ lha_read_file_header_1(struct archive_read *a, struct lha *lha)
 	/* Get a real compressed file size. */
 	lha->compsize -= extdsize - 2;
 
+	if (lha->compsize < 0)
+		goto invalid;	/* Invalid compressed file size */
+
 	if (sum_calculated != headersum) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "LHa header sum error");
@@ -1711,11 +1714,15 @@ lha_crc16(uint16_t crc, const void *pp, size_t len)
 	 */
 	for (;len >= 8; len -= 8) {
 		/* This if statement expects compiler optimization will
-		 * remove the stament which will not be executed. */
+		 * remove the statement which will not be executed. */
+#undef bswap16
 #if defined(_MSC_VER) && _MSC_VER >= 1400  /* Visual Studio */
 #  define bswap16(x) _byteswap_ushort(x)
-#elif (defined(__GNUC__) && __GNUC__ >= 4 && __GNUC_MINOR__ >= 8) \
-      || defined(__clang__)
+#elif defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || __GNUC__ > 4)
+/* GCC 4.8 and later has __builtin_bswap16() */
+#  define bswap16(x) __builtin_bswap16(x)
+#elif defined(__clang__)
+/* All clang versions have __builtin_bswap16() */
 #  define bswap16(x) __builtin_bswap16(x)
 #else
 #  define bswap16(x) ((((x) >> 8) & 0xff) | ((x) << 8))