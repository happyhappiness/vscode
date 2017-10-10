 		die("Failed to write bitmap index");
 }
 
 static const unsigned char *sha1_access(size_t pos, void *table)
 {
 	struct pack_idx_entry **index = table;
-	return index[pos]->sha1;
+	return index[pos]->oid.hash;
 }
 
 static void write_selected_commits_v1(struct sha1file *f,
 				      struct pack_idx_entry **index,
 				      uint32_t index_nr)
 {
