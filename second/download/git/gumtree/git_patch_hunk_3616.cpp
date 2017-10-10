 			return;
 	}
 
 	pos = cache_name_pos(path, strlen(path));
 	if (pos >= 0)
 		; /* path is in the index */
-	else if (!strcmp(active_cache[-1 - pos]->name, path))
+	else if (-1 - pos < active_nr &&
+		 !strcmp(active_cache[-1 - pos]->name, path))
 		; /* path is in the index, unmerged */
 	else
 		die("no such path '%s' in HEAD", path);
 }
 
 static struct commit_list **append_parent(struct commit_list **tail, const unsigned char *sha1)
