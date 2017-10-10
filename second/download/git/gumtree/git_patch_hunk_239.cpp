 static void link_alt_odb_entries(const char *alt, int len, int sep,
 				 const char *relative_base, int depth)
 {
 	struct string_list entries = STRING_LIST_INIT_NODUP;
 	char *alt_copy;
 	int i;
+	struct strbuf objdirbuf = STRBUF_INIT;
 
 	if (depth > 5) {
 		error("%s: ignoring alternate object stores, nesting too deep.",
 				relative_base);
 		return;
 	}
 
+	strbuf_addstr(&objdirbuf, absolute_path(get_object_directory()));
+	normalize_path_copy(objdirbuf.buf, objdirbuf.buf);
+
 	alt_copy = xmemdupz(alt, len);
 	string_list_split_in_place(&entries, alt_copy, sep, -1);
 	for (i = 0; i < entries.nr; i++) {
 		const char *entry = entries.items[i].string;
 		if (entry[0] == '\0' || entry[0] == '#')
 			continue;
 		if (!is_absolute_path(entry) && depth) {
 			error("%s: ignoring relative alternate object store %s",
 					relative_base, entry);
 		} else {
-			link_alt_odb_entry(entry, relative_base, depth);
+			link_alt_odb_entry(entry, relative_base, depth, objdirbuf.buf);
 		}
 	}
 	string_list_clear(&entries, 0);
 	free(alt_copy);
+	strbuf_release(&objdirbuf);
 }
 
 void read_info_alternates(const char * relative_base, int depth)
 {
 	char *map;
 	size_t mapsz;
