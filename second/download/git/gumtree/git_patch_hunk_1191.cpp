 	 * - the listener can avoid doing any work if fetching failed.
 	 */
 	if (suc.quickstop)
 		return 1;
 
 	for_each_string_list_item(item, &suc.projectlines)
-		utf8_fprintf(stdout, "%s", item->string);
+		fprintf(stdout, "%s", item->string);
 
 	return 0;
 }
 
 static int resolve_relative_path(int argc, const char **argv, const char *prefix)
 {
