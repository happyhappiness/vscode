 
 	if (read_cache() < 0)
 		die(_("index file corrupt"));
 
 	parse_pathspec(pathspec, 0,
 		       PATHSPEC_PREFER_FULL |
-		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP |
 		       (patch_mode ? PATHSPEC_PREFIX_ORIGIN : 0),
 		       prefix, argv);
 }
 
 static int reset_refs(const char *rev, const struct object_id *oid)
 {
