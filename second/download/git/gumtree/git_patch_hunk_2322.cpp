 		free(repl_obj);
 		warning("bad replace ref name: %s", refname);
 		return 0;
 	}
 
 	/* Copy sha1 from the read ref */
-	hashcpy(repl_obj->replacement, sha1);
+	hashcpy(repl_obj->replacement, oid->hash);
 
 	/* Register new object */
 	if (register_replace_object(repl_obj, 1))
 		die("duplicate replace ref: %s", refname);
 
 	return 0;
