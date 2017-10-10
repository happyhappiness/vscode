 {
 	int mode1 = 0, mode2 = 0;
 
 	if (get_mode(name1, &mode1) || get_mode(name2, &mode2))
 		return -1;
 
-	if (mode1 && mode2 && S_ISDIR(mode1) != S_ISDIR(mode2)) {
-		struct diff_filespec *d1, *d2;
-
-		if (S_ISDIR(mode1)) {
-			/* 2 is file that is created */
-			d1 = noindex_filespec(NULL, 0);
-			d2 = noindex_filespec(name2, mode2);
-			name2 = NULL;
-			mode2 = 0;
-		} else {
-			/* 1 is file that is deleted */
-			d1 = noindex_filespec(name1, mode1);
-			d2 = noindex_filespec(NULL, 0);
-			name1 = NULL;
-			mode1 = 0;
-		}
-		/* emit that file */
-		diff_queue(&diff_queued_diff, d1, d2);
-
-		/* and then let the entire directory be created or deleted */
-	}
+	if (mode1 && mode2 && S_ISDIR(mode1) != S_ISDIR(mode2))
+		return error("file/directory conflict: %s, %s", name1, name2);
 
 	if (S_ISDIR(mode1) || S_ISDIR(mode2)) {
 		struct strbuf buffer1 = STRBUF_INIT;
 		struct strbuf buffer2 = STRBUF_INIT;
 		struct string_list p1 = STRING_LIST_INIT_DUP;
 		struct string_list p2 = STRING_LIST_INIT_DUP;
