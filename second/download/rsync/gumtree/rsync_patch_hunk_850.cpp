 	if (result)
 		free(result);
 
 	if (*fn == '/')
 		p1 = p2 = "";
 	else {
-		p1 = curr_dir;
+		p1 = curr_dir + module_dirlen;
 		for (p2 = p1; *p2 == '/'; p2++) {}
 		if (*p2)
 			p2 = "/";
 	}
 	if (module_id >= 0) {
 		m1 = " (in ";
 		m2 = lp_name(module_id);
 		m3 = ")";
-		if (p1 == curr_dir) {
-			if (!lp_use_chroot(module_id)) {
-				char *p = lp_path(module_id);
-				if (*p != '/' || p[1])
-					p1 += strlen(p);
-			}
-		}
 	} else
 		m1 = m2 = m3 = "";
 
-	asprintf(&result, "\"%s%s%s\"%s%s%s", p1, p2, fn, m1, m2, m3);
+	if (asprintf(&result, "\"%s%s%s\"%s%s%s", p1, p2, fn, m1, m2, m3) <= 0)
+		out_of_memory("full_fname");
 
 	return result;
 }
 
 static char partial_fname[MAXPATHLEN];
 
