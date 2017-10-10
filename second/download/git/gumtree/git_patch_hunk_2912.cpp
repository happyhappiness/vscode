 void print_commit_list(struct commit_list *list,
 		       const char *format_cur,
 		       const char *format_last)
 {
 	for ( ; list; list = list->next) {
 		const char *format = list->next ? format_cur : format_last;
-		printf(format, sha1_to_hex(list->item->object.sha1));
+		printf(format, oid_to_hex(&list->item->object.oid));
 	}
 }
 
 const char *find_commit_header(const char *msg, const char *key, size_t *out_len)
 {
 	int key_len = strlen(key);
