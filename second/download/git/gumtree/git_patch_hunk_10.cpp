 	}
 	return 0;
 }
 
 static int remove_branches(struct string_list *branches)
 {
+	const char **branch_names;
 	int i, result = 0;
+
+	branch_names = xmalloc(branches->nr * sizeof(*branch_names));
+	for (i = 0; i < branches->nr; i++)
+		branch_names[i] = branches->items[i].string;
+	result |= repack_without_refs(branch_names, branches->nr);
+	free(branch_names);
+
 	for (i = 0; i < branches->nr; i++) {
 		struct string_list_item *item = branches->items + i;
 		const char *refname = item->string;
-		unsigned char *sha1 = item->util;
 
-		if (delete_ref(refname, sha1, 0))
+		if (delete_ref(refname, NULL, 0))
 			result |= error(_("Could not remove branch %s"), refname);
 	}
+
 	return result;
 }
 
 static int rm(int argc, const char **argv)
 {
 	struct option options[] = {
