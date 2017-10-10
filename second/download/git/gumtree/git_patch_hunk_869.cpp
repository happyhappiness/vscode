 		} else {
 			res = dry_run ? 0 : unlink(path->buf);
 			if (!res) {
 				quote_path_relative(path->buf, prefix, &quoted);
 				string_list_append(&dels, quoted.buf);
 			} else {
+				int saved_errno = errno;
 				quote_path_relative(path->buf, prefix, &quoted);
-				warning(_(msg_warn_remove_failed), quoted.buf);
+				errno = saved_errno;
+				warning_errno(_(msg_warn_remove_failed), quoted.buf);
 				*dir_gone = 0;
 				ret = 1;
 			}
 			continue;
 		}
 
