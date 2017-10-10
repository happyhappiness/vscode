 		return error("unable to load config blob object '%s'", name);
 	if (type != OBJ_BLOB) {
 		free(buf);
 		return error("reference '%s' does not point to a blob", name);
 	}
 
-	ret = git_config_from_buf(fn, name, buf, size, data);
+	ret = git_config_from_mem(fn, "blob", name, buf, size, data);
 	free(buf);
 
 	return ret;
 }
 
 static int git_config_from_blob_ref(config_fn_t fn,
