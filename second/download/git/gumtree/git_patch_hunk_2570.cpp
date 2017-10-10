 	if (!buf)
 		return error("%s: unable to read file.", name);
 	if (type != OBJ_COMMIT)
 		return error("%s: cannot verify a non-commit object of type %s.",
 				name, typename(type));
 
-	ret = run_gpg_verify(sha1, buf, size, verbose);
+	ret = run_gpg_verify(sha1, buf, size, flags);
 
 	free(buf);
 	return ret;
 }
 
 static int git_verify_commit_config(const char *var, const char *value, void *cb)
