 
 void set_object_name_for_intent_to_add_entry(struct cache_entry *ce)
 {
 	unsigned char sha1[20];
 	if (write_sha1_file("", 0, blob_type, sha1))
 		die("cannot create an empty blob in the object database");
-	hashcpy(ce->sha1, sha1);
+	hashcpy(ce->oid.hash, sha1);
 }
 
 int add_to_index(struct index_state *istate, const char *path, struct stat *st, int flags)
 {
 	int size, namelen, was_same;
 	mode_t st_mode = st->st_mode;
