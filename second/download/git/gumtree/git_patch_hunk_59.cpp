 	if (pos < 0)
 		return error(_("%s: does not exist in index"), name);
 	ce = active_cache[pos];
 	if (lstat(name, &st)) {
 		if (errno != ENOENT)
 			return error(_("%s: %s"), name, strerror(errno));
-		if (checkout_target(ce, &st))
+		if (checkout_target(&the_index, ce, &st))
 			return -1;
 	}
 	if (verify_index_match(ce, &st))
 		return error(_("%s: does not match index"), name);
 
 	status = load_patch_target(&buf, ce, &st, name, mode);
