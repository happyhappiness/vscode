 {
 	int i, j;
 	struct strbuf sb = STRBUF_INIT;
 
 	if (log->sort_by_number)
 		qsort(log->list.items, log->list.nr, sizeof(struct string_list_item),
-			compare_by_number);
+		      log->summary ? compare_by_counter : compare_by_list);
 	for (i = 0; i < log->list.nr; i++) {
-		struct string_list *onelines = log->list.items[i].util;
-
+		const struct string_list_item *item = &log->list.items[i];
 		if (log->summary) {
-			printf("%6d\t%s\n", onelines->nr, log->list.items[i].string);
+			printf("%6d\t%s\n", (int)UTIL_TO_INT(item), item->string);
 		} else {
-			printf("%s (%d):\n", log->list.items[i].string, onelines->nr);
+			struct string_list *onelines = item->util;
+			printf("%s (%d):\n", item->string, onelines->nr);
 			for (j = onelines->nr - 1; j >= 0; j--) {
 				const char *msg = onelines->items[j].string;
 
 				if (log->wrap_lines) {
 					strbuf_reset(&sb);
 					add_wrapped_shortlog_msg(&sb, msg, log);
 					fwrite(sb.buf, sb.len, 1, stdout);
 				}
 				else
 					printf("      %s\n", msg);
 			}
 			putchar('\n');
+			onelines->strdup_strings = 1;
+			string_list_clear(onelines, 0);
+			free(onelines);
 		}
 
-		onelines->strdup_strings = 1;
-		string_list_clear(onelines, 0);
-		free(onelines);
 		log->list.items[i].util = NULL;
 	}
 
 	strbuf_release(&sb);
 	log->list.strdup_strings = 1;
 	string_list_clear(&log->list, 1);
