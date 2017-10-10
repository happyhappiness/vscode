 			    "Did you mean ':%d:%s'?",
 			    filename, stage,
 			    ce_stage(ce), filename);
 	}
 
 	/* Confusion between relative and absolute filenames? */
-	fullnamelen = namelen + strlen(prefix);
-	fullname = xmalloc(fullnamelen + 1);
-	strcpy(fullname, prefix);
-	strcat(fullname, filename);
-	pos = cache_name_pos(fullname, fullnamelen);
+	strbuf_addstr(&fullname, prefix);
+	strbuf_addstr(&fullname, filename);
+	pos = cache_name_pos(fullname.buf, fullname.len);
 	if (pos < 0)
 		pos = -pos - 1;
 	if (pos < active_nr) {
 		ce = active_cache[pos];
-		if (ce_namelen(ce) == fullnamelen &&
-		    !memcmp(ce->name, fullname, fullnamelen))
+		if (ce_namelen(ce) == fullname.len &&
+		    !memcmp(ce->name, fullname.buf, fullname.len))
 			die("Path '%s' is in the index, but not '%s'.\n"
 			    "Did you mean ':%d:%s' aka ':%d:./%s'?",
-			    fullname, filename,
-			    ce_stage(ce), fullname,
+			    fullname.buf, filename,
+			    ce_stage(ce), fullname.buf,
 			    ce_stage(ce), filename);
 	}
 
 	if (file_exists(filename))
 		die("Path '%s' exists on disk, but not in the index.", filename);
 	if (errno == ENOENT || errno == ENOTDIR)
 		die("Path '%s' does not exist (neither on disk nor in the index).",
 		    filename);
 
-	free(fullname);
+	strbuf_release(&fullname);
 }
 
 
 static char *resolve_relative_path(const char *rel)
 {
 	if (!starts_with(rel, "./") && !starts_with(rel, "../"))
