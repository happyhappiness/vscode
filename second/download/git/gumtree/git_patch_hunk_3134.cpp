 	for_each_string_list_item(item, &del_list) {
 		/* Ctrl-D should stop removing files */
 		if (!eof) {
 			qname = quote_path_relative(item->string, NULL, &buf);
 			/* TRANSLATORS: Make sure to keep [y/N] as is */
 			printf(_("Remove %s [y/N]? "), qname);
-			if (strbuf_getline(&confirm, stdin, '\n') != EOF) {
+			if (strbuf_getline_lf(&confirm, stdin) != EOF) {
 				strbuf_trim(&confirm);
 			} else {
 				putchar('\n');
 				eof = 1;
 			}
 		}
