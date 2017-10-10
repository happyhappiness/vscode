 void shortlog_output(struct shortlog *log)
 {
 	int i, j;
 	struct strbuf sb = STRBUF_INIT;
 
 	if (log->sort_by_number)
-		qsort(log->list.items, log->list.nr, sizeof(struct string_list_item),
+		QSORT(log->list.items, log->list.nr,
 		      log->summary ? compare_by_counter : compare_by_list);
 	for (i = 0; i < log->list.nr; i++) {
 		const struct string_list_item *item = &log->list.items[i];
 		if (log->summary) {
 			fprintf(log->file, "%6d\t%s\n",
 				(int)UTIL_TO_INT(item), item->string);
