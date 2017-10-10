 								   filename,
 								   tree_sha1,
 								   name, len);
 				}
 			}
 			hashcpy(oc->tree, tree_sha1);
-			strlcpy(oc->path, filename, sizeof(oc->path));
+			if (flags & GET_SHA1_RECORD_PATH)
+				oc->path = xstrdup(filename);
 
 			free(new_filename);
 			return ret;
 		} else {
 			if (only_to_die)
 				die("Invalid object name '%.*s'.", len, name);
