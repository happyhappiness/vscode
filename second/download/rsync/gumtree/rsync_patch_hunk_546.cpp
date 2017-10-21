 #ifdef HAVE_ST_RDEV
 	file->rdev = st.st_rdev;
 #endif
 
 #if SUPPORT_LINKS
 	if (S_ISLNK(st.st_mode)) {
-		int l;
-		char lnk[MAXPATHLEN];
-		if ((l=readlink(fname,lnk,MAXPATHLEN-1)) == -1) {
-			io_error=1;
-			rprintf(FERROR,"readlink %s : %s\n",
-				fname,strerror(errno));
-			return NULL;
-		}
-		lnk[l] = 0;
-		file->link = strdup(lnk);
+		file->link = strdup(linkbuf);
 	}
 #endif
 
 	if (always_checksum) {
 		file->sum = (char *)malloc(MD4_SUM_LENGTH);
 		if (!file->sum) out_of_memory("md4 sum");
