 	fputc('\n', stdout);
 }
 
 void fast_export_data(uint32_t mode, off_t len, struct line_buffer *input)
 {
 	assert(len >= 0);
-	if (mode == REPO_MODE_LNK) {
+	if (mode == S_IFLNK) {
 		/* svn symlink blobs start with "link " */
 		if (len < 5)
 			die("invalid dump: symlink too short for \"link\" prefix");
 		len -= 5;
 		if (buffer_skip_bytes(input, 5) != 5)
 			die_short_read(input);
