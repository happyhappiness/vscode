 	struct string_list merge_rr = STRING_LIST_INIT_DUP;
 
 	if (read_cache() < 0)
 		return error("Could not read index");
 
 	fd = setup_rerere(&merge_rr, RERERE_NOAUTOUPDATE);
+	if (fd < 0)
+		return 0;
 
 	unmerge_cache(pathspec);
 	find_conflict(&conflict);
 	for (i = 0; i < conflict.nr; i++) {
 		struct string_list_item *it = &conflict.items[i];
 		if (!match_pathspec(pathspec, it->string,
