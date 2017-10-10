 				die("early EOF '%s'", elem->path);
 
 			/* If not a fake symlink, apply filters, e.g. autocrlf */
 			if (is_file) {
 				struct strbuf buf = STRBUF_INIT;
 
-				if (convert_to_git(elem->path, result, len, &buf, safe_crlf)) {
+				if (convert_to_git(&the_index, elem->path, result, len, &buf, safe_crlf)) {
 					free(result);
 					result = strbuf_detach(&buf, &len);
 					result_size = len;
 				}
 			}
 		}
