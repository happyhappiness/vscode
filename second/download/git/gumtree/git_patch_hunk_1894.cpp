 
 	fprintf(out, "%s ", sha1_to_hex(obj->sha1));
 	show_path_truncated(out, &leaf);
 	fputc('\n', out);
 }
 
-void add_object(struct object *obj,
-		struct object_array *p,
-		struct name_path *path,
-		const char *name)
-{
-	char *pn = path_name(path, name);
-	add_object_array(obj, pn, p);
-	free(pn);
-}
-
 static void mark_blob_uninteresting(struct blob *blob)
 {
 	if (!blob)
 		return;
 	if (blob->object.flags & UNINTERESTING)
 		return;
