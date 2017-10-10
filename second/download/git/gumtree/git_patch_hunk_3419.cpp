 	init_tree_desc(&desc, buf, sz);
 
 	rewrite_here = NULL;
 	while (desc.size) {
 		const char *name;
 		unsigned mode;
-		const unsigned char *sha1;
+		const struct object_id *oid;
 
-		sha1 = tree_entry_extract(&desc, &name, &mode);
+		oid = tree_entry_extract(&desc, &name, &mode);
 		if (strlen(name) == toplen &&
 		    !memcmp(name, prefix, toplen)) {
 			if (!S_ISDIR(mode))
 				die("entry %s in tree %s is not a tree",
 				    name, sha1_to_hex(hash1));
-			rewrite_here = (unsigned char *) sha1;
+			rewrite_here = (unsigned char *) oid->hash;
 			break;
 		}
 		update_tree_entry(&desc);
 	}
 	if (!rewrite_here)
 		die("entry %.*s not found in tree %s",
