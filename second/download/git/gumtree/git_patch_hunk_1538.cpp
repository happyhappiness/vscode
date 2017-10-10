 {
 	add_pending_object_with_mode(revs, obj, name, S_IFINVALID);
 }
 
 void add_head_to_pending(struct rev_info *revs)
 {
-	unsigned char sha1[20];
+	struct object_id oid;
 	struct object *obj;
-	if (get_sha1("HEAD", sha1))
+	if (get_oid("HEAD", &oid))
 		return;
-	obj = parse_object(sha1);
+	obj = parse_object(&oid);
 	if (!obj)
 		return;
 	add_pending_object(revs, obj, "HEAD");
 }
 
 static struct object *get_reference(struct rev_info *revs, const char *name,
-				    const unsigned char *sha1,
+				    const struct object_id *oid,
 				    unsigned int flags)
 {
 	struct object *object;
 
-	object = parse_object(sha1);
+	object = parse_object(oid);
 	if (!object) {
 		if (revs->ignore_missing)
 			return object;
 		die("bad object %s", name);
 	}
 	object->flags |= flags;
 	return object;
 }
 
-void add_pending_sha1(struct rev_info *revs, const char *name,
-		      const unsigned char *sha1, unsigned int flags)
+void add_pending_oid(struct rev_info *revs, const char *name,
+		      const struct object_id *oid, unsigned int flags)
 {
-	struct object *object = get_reference(revs, name, sha1, flags);
+	struct object *object = get_reference(revs, name, oid, flags);
 	add_pending_object(revs, object, name);
 }
 
 static struct commit *handle_commit(struct rev_info *revs,
 				    struct object_array_entry *entry)
 {
