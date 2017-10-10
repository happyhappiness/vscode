 		die("corrupt tree file");
 	len = strlen(path) + 1;
 
 	/* Initialize the descriptor entry */
 	desc->entry.path = path;
 	desc->entry.mode = canon_mode(mode);
-	desc->entry.sha1 = (const unsigned char *)(path + len);
+	desc->entry.oid  = (const struct object_id *)(path + len);
 }
 
 void init_tree_desc(struct tree_desc *desc, const void *buffer, unsigned long size)
 {
 	desc->buffer = buffer;
 	desc->size = size;
