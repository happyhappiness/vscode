 			for (i = 0; !is_file && i < num_parent; i++)
 				is_file = !S_ISLNK(elem->parent[i].mode);
 			if (!is_file)
 				elem->mode = canon_mode(S_IFLNK);
 
 			result_size = len;
-			result = xmalloc(len + 1);
+			result = xmallocz(len);
 
 			done = read_in_full(fd, result, len);
 			if (done < 0)
 				die_errno("read error '%s'", elem->path);
 			else if (done < len)
 				die("early EOF '%s'", elem->path);
 
-			result[len] = 0;
-
 			/* If not a fake symlink, apply filters, e.g. autocrlf */
 			if (is_file) {
 				struct strbuf buf = STRBUF_INIT;
 
 				if (convert_to_git(elem->path, result, len, &buf, safe_crlf)) {
 					free(result);
