 	 */
 	item = string_list_insert(rr, path);
 	free_rerere_id(item);
 	item->util = id;
 	fprintf(stderr, "Forgot resolution for %s\n", path);
 	return 0;
+
+fail_exit:
+	free(id);
+	return -1;
 }
 
 int rerere_forget(struct pathspec *pathspec)
 {
 	int i, fd;
 	struct string_list conflict = STRING_LIST_INIT_DUP;
