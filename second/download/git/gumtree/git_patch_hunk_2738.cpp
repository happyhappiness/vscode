 static unsigned long garbage;
 static off_t size_garbage;
 static int verbose;
 static unsigned long loose, packed, packed_loose;
 static off_t loose_size;
 
-static void real_report_garbage(const char *desc, const char *path)
+static const char *bits_to_msg(unsigned seen_bits)
+{
+	switch (seen_bits) {
+	case 0:
+		return "no corresponding .idx or .pack";
+	case PACKDIR_FILE_GARBAGE:
+		return "garbage found";
+	case PACKDIR_FILE_PACK:
+		return "no corresponding .idx";
+	case PACKDIR_FILE_IDX:
+		return "no corresponding .pack";
+	case PACKDIR_FILE_PACK|PACKDIR_FILE_IDX:
+	default:
+		return NULL;
+	}
+}
+
+static void real_report_garbage(unsigned seen_bits, const char *path)
 {
 	struct stat st;
+	const char *desc = bits_to_msg(seen_bits);
+
+	if (!desc)
+		return;
+
 	if (!stat(path, &st))
 		size_garbage += st.st_size;
 	warning("%s: %s", desc, path);
 	garbage++;
 }
 
 static void loose_garbage(const char *path)
 {
 	if (verbose)
-		report_garbage("garbage found", path);
+		report_garbage(PACKDIR_FILE_GARBAGE, path);
 }
 
 static int count_loose(const unsigned char *sha1, const char *path, void *data)
 {
 	struct stat st;
 
