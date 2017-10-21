 #ifdef SUPPORT_LINKS
 	linkname_len = S_ISLNK(st.st_mode) ? strlen(linkname) + 1 : 0;
 #else
 	linkname_len = 0;
 #endif
 
-	sum_len = always_checksum && S_ISREG(st.st_mode) ? MD4_SUM_LENGTH : 0;
+	sum_len = always_checksum && am_sender && S_ISREG(st.st_mode)
+	        ? MD4_SUM_LENGTH : 0;
 
 	alloc_len = file_struct_len + dirname_len + basename_len
 	    + linkname_len + sum_len;
-	if (flist) {
-		bp = pool_alloc(flist->file_pool, alloc_len,
-		    "receive_file_entry");
-	} else {
+	if (flist)
+		bp = pool_alloc(flist->file_pool, alloc_len, "make_file");
+	else {
 		if (!(bp = new_array(char, alloc_len)))
-			out_of_memory("receive_file_entry");
+			out_of_memory("make_file");
 	}
 
 	file = (struct file_struct *)bp;
 	memset(bp, 0, file_struct_len);
 	bp += file_struct_len;
 
