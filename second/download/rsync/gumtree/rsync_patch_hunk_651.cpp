 	if (preserve_links && S_ISLNK(file->mode)) {
 		int l = read_int(f);
 		if (l < 0) {
 			rprintf(FERROR, "overflow: l=%d\n", l);
 			overflow("receive_file_entry");
 		}
-		file->link = (char *) malloc(l + 1);
+		file->link = new_array(char, l + 1);
 		if (!file->link)
 			out_of_memory("receive_file_entry 2");
 		read_sbuf(f, file->link, l);
 		if (sanitize_paths) {
 			sanitize_path(file->link, file->dirname);
 		}
