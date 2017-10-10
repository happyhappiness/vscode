 			if (S_ISGITLINK(ce->ce_mode))
 				return 0;
 			if (!state->force)
 				return error("%s is a directory", path.buf);
 			remove_subtree(&path);
 		} else if (unlink(path.buf))
-			return error("unable to unlink old '%s' (%s)",
-				     path.buf, strerror(errno));
+			return error_errno("unable to unlink old '%s'", path.buf);
 	} else if (state->not_new)
 		return 0;
 
 	create_directories(path.buf, path.len, state);
 	return write_entry(ce, path.buf, state, 0);
 }
