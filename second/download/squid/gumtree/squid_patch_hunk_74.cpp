     for (path = strwordtok(files, &saveptr); path; path = strwordtok(NULL, &saveptr)) {
         if (glob(path, globbuf.gl_pathc ? GLOB_APPEND : 0, NULL, &globbuf) != 0) {
             fatalf("Unable to find configuration file: %s: %s",
                    path, xstrerror());
         }
     }
-    for (i = 0; i < (int)globbuf.gl_pathc; i++) {
+    for (i = 0; i < (int)globbuf.gl_pathc; ++i) {
         error_count += parseOneConfigFile(globbuf.gl_pathv[i], depth);
     }
     globfree(&globbuf);
 #else
     char* file = strwordtok(files, &saveptr);
     while (file != NULL) {
