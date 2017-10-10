 	return 0;
 }
 
 static void *read_object(const unsigned char *sha1, enum object_type *type,
 			 unsigned long *size)
 {
-	unsigned long mapsize;
-	void *map, *buf;
-	struct cached_object *co;
-
-	co = find_cached_object(sha1);
-	if (co) {
-		*type = co->type;
-		*size = co->size;
-		return xmemdupz(co->buf, co->size);
-	}
+	struct object_info oi = OBJECT_INFO_INIT;
+	void *content;
+	oi.typep = type;
+	oi.sizep = size;
+	oi.contentp = &content;
 
-	buf = read_packed_sha1(sha1, type, size);
-	if (buf)
-		return buf;
-	map = map_sha1_file(sha1, &mapsize);
-	if (map) {
-		buf = unpack_sha1_file(map, mapsize, type, size, sha1);
-		munmap(map, mapsize);
-		return buf;
-	}
-	reprepare_packed_git();
-	return read_packed_sha1(sha1, type, size);
+	if (sha1_object_info_extended(sha1, &oi, 0) < 0)
+		return NULL;
+	return content;
 }
 
 /*
  * This function dies on corrupt objects; the callers who want to
  * deal with them should arrange to call read_object() and give error
  * messages themselves.
  */
 void *read_sha1_file_extended(const unsigned char *sha1,
 			      enum object_type *type,
 			      unsigned long *size,
-			      unsigned flag)
+			      int lookup_replace)
 {
 	void *data;
 	const struct packed_git *p;
 	const char *path;
 	struct stat st;
-	const unsigned char *repl = lookup_replace_object_extended(sha1, flag);
+	const unsigned char *repl = lookup_replace ? lookup_replace_object(sha1)
+						   : sha1;
 
 	errno = 0;
 	data = read_object(repl, type, size);
 	if (data)
 		return data;
 
