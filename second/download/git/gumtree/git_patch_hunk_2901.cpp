 	struct pack_idx_entry *idx = NULL;
 
 	seekback = lseek(fd, 0, SEEK_CUR);
 	if (seekback == (off_t) -1)
 		return error("cannot find the current offset");
 
-	header_len = sprintf((char *)obuf, "%s %" PRIuMAX,
-			     typename(type), (uintmax_t)size) + 1;
+	header_len = xsnprintf((char *)obuf, sizeof(obuf), "%s %" PRIuMAX,
+			       typename(type), (uintmax_t)size) + 1;
 	git_SHA1_Init(&ctx);
 	git_SHA1_Update(&ctx, obuf, header_len);
 
 	/* Note: idx is non-NULL when we are writing */
 	if ((flags & HASH_WRITE_OBJECT) != 0)
 		idx = xcalloc(1, sizeof(*idx));
