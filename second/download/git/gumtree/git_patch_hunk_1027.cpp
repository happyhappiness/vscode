 
 	if (opts->flags & WRITE_IDX_VERIFY) {
 		assert(index_name);
 		f = sha1fd_check(index_name);
 	} else {
 		if (!index_name) {
-			static char tmp_file[PATH_MAX];
-			fd = odb_mkstemp(tmp_file, sizeof(tmp_file), "pack/tmp_idx_XXXXXX");
-			index_name = xstrdup(tmp_file);
+			struct strbuf tmp_file = STRBUF_INIT;
+			fd = odb_mkstemp(&tmp_file, "pack/tmp_idx_XXXXXX");
+			index_name = strbuf_detach(&tmp_file, NULL);
 		} else {
 			unlink(index_name);
 			fd = open(index_name, O_CREAT|O_EXCL|O_WRONLY, 0600);
+			if (fd < 0)
+				die_errno("unable to create '%s'", index_name);
 		}
-		if (fd < 0)
-			die_errno("unable to create '%s'", index_name);
 		f = sha1fd(fd, index_name);
 	}
 
 	/* if last object's offset is >= 2^31 we should use index V2 */
 	index_version = need_large_offset(last_obj_offset, opts) ? 2 : opts->version;
 
