 #if SUPPORT_LINKS
 	if (S_ISLNK(st.st_mode)) {
 		int l;
 		char lnk[MAXPATHLEN];
 		if ((l=readlink(fname,lnk,MAXPATHLEN-1)) == -1) {
 			io_error=1;
-			fprintf(FERROR,"readlink %s : %s\n",
+			rprintf(FERROR,"readlink %s : %s\n",
 				fname,strerror(errno));
 			return NULL;
 		}
 		lnk[l] = 0;
 		file->link = strdup(lnk);
 	}
