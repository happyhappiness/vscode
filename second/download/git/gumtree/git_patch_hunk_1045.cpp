  * change this to account for multiple levels (e.g. annotated tags
  * pointing to annotated tags pointing to a commit.)
  * 2. As the refs are cached we might know what refname peels to without
  * the need to parse the object via parse_object(). peel_ref() might be a
  * more efficient alternative to obtain the pointee.
  */
-static const unsigned char *match_points_at(struct sha1_array *points_at,
-					    const unsigned char *sha1,
-					    const char *refname)
+static const struct object_id *match_points_at(struct oid_array *points_at,
+					       const struct object_id *oid,
+					       const char *refname)
 {
-	const unsigned char *tagged_sha1 = NULL;
+	const struct object_id *tagged_oid = NULL;
 	struct object *obj;
 
-	if (sha1_array_lookup(points_at, sha1) >= 0)
-		return sha1;
-	obj = parse_object(sha1);
+	if (oid_array_lookup(points_at, oid) >= 0)
+		return oid;
+	obj = parse_object(oid->hash);
 	if (!obj)
 		die(_("malformed object at '%s'"), refname);
 	if (obj->type == OBJ_TAG)
-		tagged_sha1 = ((struct tag *)obj)->tagged->oid.hash;
-	if (tagged_sha1 && sha1_array_lookup(points_at, tagged_sha1) >= 0)
-		return tagged_sha1;
+		tagged_oid = &((struct tag *)obj)->tagged->oid;
+	if (tagged_oid && oid_array_lookup(points_at, tagged_oid) >= 0)
+		return tagged_oid;
 	return NULL;
 }
 
 /* Allocate space for a new ref_array_item and copy the objectname and flag to it */
 static struct ref_array_item *new_ref_array_item(const char *refname,
 						 const unsigned char *objectname,
