 
 	ret->pattern = strdup(pattern);
 
 	if (!ret->pattern) out_of_memory("make_exclude");
 
 	if (strpbrk(pattern, "*[?")) {
-	    if (!ret->include && (*pattern == '*') && (*(pattern+1) == '\0')) {
-		    exclude_the_rest = ret;
-	    } else {
-		    only_included_files = 0;
-	    }
 	    ret->regular_exp = 1;
-	    ret->fnmatch_flags = strstr(pattern, "**") ? 0 : FNM_PATHNAME;
-	} else if (!ret->include) {
-		only_included_files = 0;
+	    ret->fnmatch_flags = FNM_PATHNAME;
+	    if (strstr(pattern, "**")) {
+		    static int tested;
+		    if (!tested) {
+			    tested = 1;
+			    if (fnmatch("a/b/*", "a/b/c/d", FNM_PATHNAME)==0) {
+				    rprintf(FERROR,"WARNING: fnmatch FNM_PATHNAME is broken on your system\n");
+			    }
+		    }
+		    ret->fnmatch_flags = 0;
+	    }
 	}
 
 	if (strlen(pattern) > 1 && pattern[strlen(pattern)-1] == '/') {
 		ret->pattern[strlen(pattern)-1] = 0;
 		ret->directory = 1;
 	}
