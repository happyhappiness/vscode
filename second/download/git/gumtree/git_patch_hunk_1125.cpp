 	while (!strbuf_getline_nul(&buf, fp)) {
 		struct path_entry *entry;
 		FLEX_ALLOC_STR(entry, path, buf.buf);
 		hashmap_entry_init(entry, strhash(buf.buf));
 		hashmap_add(result, entry);
 	}
+	fclose(fp);
 	if (finish_command(&diff_files))
 		die("diff-files did not exit properly");
 	strbuf_release(&index_env);
 	strbuf_release(&buf);
 }
 
