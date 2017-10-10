 	}
 	fclose(f);
 	ptr->size = sz;
 	return 0;
 }
 
-void read_mmblob(mmfile_t *ptr, const unsigned char *sha1)
+void read_mmblob(mmfile_t *ptr, const struct object_id *oid)
 {
 	unsigned long size;
 	enum object_type type;
 
-	if (!hashcmp(sha1, null_sha1)) {
+	if (!oidcmp(oid, &null_oid)) {
 		ptr->ptr = xstrdup("");
 		ptr->size = 0;
 		return;
 	}
 
-	ptr->ptr = read_sha1_file(sha1, &type, &size);
+	ptr->ptr = read_sha1_file(oid->hash, &type, &size);
 	if (!ptr->ptr || type != OBJ_BLOB)
-		die("unable to read blob object %s", sha1_to_hex(sha1));
+		die("unable to read blob object %s", oid_to_hex(oid));
 	ptr->size = size;
 }
 
 #define FIRST_FEW_BYTES 8000
 int buffer_is_binary(const char *ptr, unsigned long size)
 {
