 void string_list_add_refs_by_glob(struct string_list *list, const char *glob)
 {
 	assert(list->strdup_strings);
 	if (has_glob_specials(glob)) {
 		for_each_glob_ref(string_list_add_one_ref, glob, list);
 	} else {
-		unsigned char sha1[20];
-		if (get_sha1(glob, sha1))
+		struct object_id oid;
+		if (get_oid(glob, &oid))
 			warning("notes ref %s is invalid", glob);
 		if (!unsorted_string_list_has_string(list, glob))
 			string_list_append(list, glob);
 	}
 }
 
