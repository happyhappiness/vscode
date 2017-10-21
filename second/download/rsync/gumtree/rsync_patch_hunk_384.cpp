 		}
 		lnk[l] = 0;
 		file->link = strdup(lnk);
 	}
 #endif
 
-	if (always_checksum && S_ISREG(st.st_mode)) {
+	if (always_checksum) {
 		file->sum = (char *)malloc(MD4_SUM_LENGTH);
 		if (!file->sum) out_of_memory("md4 sum");
-		file_checksum(fname,file->sum,st.st_size);
+		/* drat. we have to provide a null checksum for non-regular
+		   files in order to be compatible with earlier versions
+		   of rsync */
+		if (S_ISREG(st.st_mode)) {
+			file_checksum(fname,file->sum,st.st_size);
+		} else {
+			memset(file->sum, 0, MD4_SUM_LENGTH);
+		}
 	}       
 
 	if (flist_dir) {
 		static char *lastdir;
 		if (lastdir && strcmp(lastdir, flist_dir)==0) {
 			file->basedir = lastdir;
