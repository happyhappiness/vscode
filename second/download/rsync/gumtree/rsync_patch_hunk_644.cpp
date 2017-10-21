 	static char *buf1;
 	static int len1;
 	struct mdfour m;
 
 	if (len > len1) {
 		if (buf1) free(buf1);
-		buf1 = (char *)malloc(len+4);
+		buf1 = new_array(char, len+4);
 		len1 = len;
 		if (!buf1) out_of_memory("get_checksum2");
 	}
 	
 	mdfour_begin(&m);
 	
