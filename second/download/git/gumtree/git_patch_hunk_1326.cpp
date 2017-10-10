 
 #define IGNORE_MISSING 1
 
 static int remove_one_note(struct notes_tree *t, const char *name, unsigned flag)
 {
 	int status;
-	unsigned char sha1[20];
-	if (get_sha1(name, sha1))
+	struct object_id oid;
+	if (get_oid(name, &oid))
 		return error(_("Failed to resolve '%s' as a valid ref."), name);
-	status = remove_note(t, sha1);
+	status = remove_note(t, oid.hash);
 	if (status)
 		fprintf(stderr, _("Object %s has no note\n"), name);
 	else
 		fprintf(stderr, _("Removing note for object %s\n"), name);
 	return (flag & IGNORE_MISSING) ? 0 : status;
 }
