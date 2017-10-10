 	result = get_merge_bases_many_dirty(rev[0], rev_nr - 1, rev + 1);
 
 	if (!result)
 		return 1;
 
 	while (result) {
-		printf("%s\n", sha1_to_hex(result->item->object.sha1));
+		printf("%s\n", oid_to_hex(&result->item->object.oid));
 		if (!show_all)
 			return 0;
 		result = result->next;
 	}
 
 	return 0;
