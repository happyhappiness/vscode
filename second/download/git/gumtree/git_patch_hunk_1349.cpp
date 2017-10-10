 
 	for_each_string_list_item(item, &states.stale)
 		string_list_append(&refs_to_prune, item->util);
 	string_list_sort(&refs_to_prune);
 
 	if (!dry_run)
-		result |= delete_refs(&refs_to_prune, 0);
+		result |= delete_refs("remote: prune", &refs_to_prune, 0);
 
 	for_each_string_list_item(item, &states.stale) {
 		const char *refname = item->util;
 
 		if (dry_run)
 			printf_ln(_(" * [would prune] %s"),
