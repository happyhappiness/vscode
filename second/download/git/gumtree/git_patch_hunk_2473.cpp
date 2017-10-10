 #include "revision.h"
 #include "list-objects.h"
 
 static void process_blob(struct rev_info *revs,
 			 struct blob *blob,
 			 show_object_fn show,
-			 struct name_path *path,
+			 struct strbuf *path,
 			 const char *name,
 			 void *cb_data)
 {
 	struct object *obj = &blob->object;
+	size_t pathlen;
 
 	if (!revs->blob_objects)
 		return;
 	if (!obj)
 		die("bad blob object");
 	if (obj->flags & (UNINTERESTING | SEEN))
 		return;
 	obj->flags |= SEEN;
-	show(obj, path, name, cb_data);
+
+	pathlen = path->len;
+	strbuf_addstr(path, name);
+	show(obj, path->buf, cb_data);
+	strbuf_setlen(path, pathlen);
 }
 
 /*
  * Processing a gitlink entry currently does nothing, since
  * we do not recurse into the subproject.
  *
