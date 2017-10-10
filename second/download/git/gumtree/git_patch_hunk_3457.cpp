 	struct strbuf sb = STRBUF_INIT;
 
 	switch (st->st_mode & S_IFMT) {
 	case S_IFREG:
 		fd = open(path, O_RDONLY);
 		if (fd < 0)
-			return error("open(\"%s\"): %s", path,
-				     strerror(errno));
+			return error_errno("open(\"%s\")", path);
 		if (index_fd(sha1, fd, st, OBJ_BLOB, path, flags) < 0)
 			return error("%s: failed to insert into database",
 				     path);
 		break;
 	case S_IFLNK:
-		if (strbuf_readlink(&sb, path, st->st_size)) {
-			char *errstr = strerror(errno);
-			return error("readlink(\"%s\"): %s", path,
-			             errstr);
-		}
+		if (strbuf_readlink(&sb, path, st->st_size))
+			return error_errno("readlink(\"%s\")", path);
 		if (!(flags & HASH_WRITE_OBJECT))
 			hash_sha1_file(sb.buf, sb.len, blob_type, sha1);
 		else if (write_sha1_file(sb.buf, sb.len, blob_type, sha1))
 			return error("%s: failed to insert into database",
 				     path);
 		strbuf_release(&sb);
