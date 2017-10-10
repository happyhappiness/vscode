 		die(_("staging updated .gitmodules failed"));
 }
 
 static int add_submodule_odb(const char *path)
 {
 	struct strbuf objects_directory = STRBUF_INIT;
-	struct alternate_object_database *alt_odb;
 	int ret = 0;
-	size_t alloc;
 
-	strbuf_git_path_submodule(&objects_directory, path, "objects/");
+	ret = strbuf_git_path_submodule(&objects_directory, path, "objects/");
+	if (ret)
+		goto done;
 	if (!is_directory(objects_directory.buf)) {
 		ret = -1;
 		goto done;
 	}
-	/* avoid adding it twice */
-	prepare_alt_odb();
-	for (alt_odb = alt_odb_list; alt_odb; alt_odb = alt_odb->next)
-		if (alt_odb->name - alt_odb->base == objects_directory.len &&
-				!strncmp(alt_odb->base, objects_directory.buf,
-					objects_directory.len))
-			goto done;
-
-	alloc = st_add(objects_directory.len, 42); /* for "12/345..." sha1 */
-	alt_odb = xmalloc(st_add(sizeof(*alt_odb), alloc));
-	alt_odb->next = alt_odb_list;
-	xsnprintf(alt_odb->base, alloc, "%s", objects_directory.buf);
-	alt_odb->name = alt_odb->base + objects_directory.len;
-	alt_odb->name[2] = '/';
-	alt_odb->name[40] = '\0';
-	alt_odb->name[41] = '\0';
-	alt_odb_list = alt_odb;
-
-	/* add possible alternates from the submodule */
-	read_info_alternates(objects_directory.buf, 0);
+	add_to_alternates_memory(objects_directory.buf);
 done:
 	strbuf_release(&objects_directory);
 	return ret;
 }
 
 void set_diffopt_flags_from_submodule_config(struct diff_options *diffopt,
