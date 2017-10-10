 		const char *s;
 
 		if (!skip_prefix(buf, "Subproject commit ", &s) ||
 		    get_sha1_hex(s, ce->sha1))
 			die(_("corrupt patch for submodule %s"), path);
 	} else {
-		if (!cached) {
+		if (!state->cached) {
 			if (lstat(path, &st) < 0)
 				die_errno(_("unable to stat newly created file '%s'"),
 					  path);
 			fill_stat_cache_info(ce, &st);
 		}
 		if (write_sha1_file(buf, size, blob_type, ce->sha1) < 0)
