 #endif
 
 	sum_len = always_checksum && am_sender && S_ISREG(st.st_mode)
 	        ? MD4_SUM_LENGTH : 0;
 
 	alloc_len = file_struct_len + dirname_len + basename_len
-	    + linkname_len + sum_len;
+		  + linkname_len + sum_len;
 	if (flist)
 		bp = pool_alloc(flist->file_pool, alloc_len, "make_file");
 	else {
 		if (!(bp = new_array(char, alloc_len)))
 			out_of_memory("make_file");
 	}
