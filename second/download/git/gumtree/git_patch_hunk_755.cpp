 	int depth, const char *normalized_objdir)
 {
 	struct alternate_object_database *ent;
 	struct strbuf pathbuf = STRBUF_INIT;
 
 	if (!is_absolute_path(entry) && relative_base) {
-		strbuf_addstr(&pathbuf, real_path(relative_base));
+		strbuf_realpath(&pathbuf, relative_base, 1);
 		strbuf_addch(&pathbuf, '/');
 	}
 	strbuf_addstr(&pathbuf, entry);
 
 	if (strbuf_normalize_path(&pathbuf) < 0 && relative_base) {
 		error("unable to normalize alternate object path: %s",
