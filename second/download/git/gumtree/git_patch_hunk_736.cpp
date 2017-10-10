 static struct lock_file index_lock;
 
 static void update_paths(struct string_list *update)
 {
 	int i;
 
-	hold_locked_index(&index_lock, 1);
+	hold_locked_index(&index_lock, LOCK_DIE_ON_ERROR);
 
 	for (i = 0; i < update->nr; i++) {
 		struct string_list_item *item = &update->items[i];
 		if (add_file_to_cache(item->string, 0))
 			exit(128);
 		fprintf(stderr, "Staged '%s' using previous resolution.\n",
