 	list.strdup_strings = 1;
 	result = for_each_remote(get_one_entry, &list);
 
 	if (!result) {
 		int i;
 
-		sort_string_list(&list);
+		string_list_sort(&list);
 		for (i = 0; i < list.nr; i++) {
 			struct string_list_item *item = list.items + i;
 			if (verbose)
 				printf("%s\t%s\n", item->string,
 					item->util ? (const char *)item->util : "");
 			else {
