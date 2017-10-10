 			die("entry '%s' object %s is a %s but specified type was (%s)",
 				path, sha1_to_hex(sha1), typename(obj_type), typename(mode_type));
 		}
 	}
 
 	append_to_tree(mode, sha1, path);
+	free(to_free);
 }
 
 int cmd_mktree(int ac, const char **av, const char *prefix)
 {
 	struct strbuf sb = STRBUF_INIT;
 	unsigned char sha1[20];
