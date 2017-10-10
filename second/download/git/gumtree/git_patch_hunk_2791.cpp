 			warning(_(msg_warn_remove_failed), quoted.buf);
 			*dir_gone = 0;
 		}
 		return res;
 	}
 
-	if (path->buf[original_len - 1] != '/')
-		strbuf_addch(path, '/');
+	strbuf_complete(path, '/');
 
 	len = path->len;
 	while ((e = readdir(dir)) != NULL) {
 		struct stat st;
 		if (is_dot_or_dotdot(e->d_name))
 			continue;
