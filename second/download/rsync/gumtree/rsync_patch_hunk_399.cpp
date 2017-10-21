 	int l;
 	char *p;
 
 	d = opendir(dir);
 	if (!d) {
 		io_error = 1;
-		fprintf(FERROR,"%s: %s\n",
+		rprintf(FERROR,"%s: %s\n",
 			dir,strerror(errno));
 		return;
 	}
 
-	strncpy(fname,dir,MAXPATHLEN-1);
-	fname[MAXPATHLEN-1]=0;
+	strlcpy(fname,dir,MAXPATHLEN-1);
 	l = strlen(fname);
 	if (fname[l-1] != '/') {
 		if (l == MAXPATHLEN-1) {
 			io_error = 1;
-			fprintf(FERROR,"skipping long-named directory %s\n",fname);
+			rprintf(FERROR,"skipping long-named directory %s\n",fname);
 			closedir(d);
 			return;
 		}
 		strcat(fname,"/");
 		l++;
 	}
