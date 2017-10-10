 	strbuf_release(&dir);
 
 	if (verify_repository_format(&candidate, &err) < 0) {
 		warning("ignoring git dir '%s': %s",
 			gitdir->buf + gitdir_offset, err.buf);
 		strbuf_release(&err);
+		strbuf_setlen(gitdir, gitdir_offset);
 		return NULL;
 	}
 
 	return gitdir->buf + gitdir_offset;
 }
 
