 	ce = xcalloc(1, ce_size);
 	memcpy(ce->name, path, namelen);
 	ce->ce_mode = create_ce_mode(mode);
 	ce->ce_flags = create_ce_flags(0);
 	ce->ce_namelen = namelen;
 	if (S_ISGITLINK(mode)) {
-		const char *s = buf;
+		const char *s;
 
-		if (get_sha1_hex(s + strlen("Subproject commit "), ce->sha1))
+		if (!skip_prefix(buf, "Subproject commit ", &s) ||
+		    get_sha1_hex(s, ce->sha1))
 			die(_("corrupt patch for submodule %s"), path);
 	} else {
 		if (!cached) {
 			if (lstat(path, &st) < 0)
 				die_errno(_("unable to stat newly created file '%s'"),
 					  path);
