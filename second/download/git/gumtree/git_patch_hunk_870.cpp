 
 	if (*dir_gone) {
 		res = dry_run ? 0 : rmdir(path->buf);
 		if (!res)
 			*dir_gone = 1;
 		else {
+			int saved_errno = errno;
 			quote_path_relative(path->buf, prefix, &quoted);
-			warning(_(msg_warn_remove_failed), quoted.buf);
+			errno = saved_errno;
+			warning_errno(_(msg_warn_remove_failed), quoted.buf);
 			*dir_gone = 0;
 			ret = 1;
 		}
 	}
 
 	if (!*dir_gone && !quiet) {
