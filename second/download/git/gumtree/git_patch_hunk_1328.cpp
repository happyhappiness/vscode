 	void *buf;
 	struct git_istream *st = NULL;
 
 	if (!usable_delta) {
 		if (entry->type == OBJ_BLOB &&
 		    entry->size > big_file_threshold &&
-		    (st = open_istream(entry->idx.sha1, &type, &size, NULL)) != NULL)
+		    (st = open_istream(entry->idx.oid.hash, &type, &size, NULL)) != NULL)
 			buf = NULL;
 		else {
-			buf = read_sha1_file(entry->idx.sha1, &type, &size);
+			buf = read_sha1_file(entry->idx.oid.hash, &type,
+					     &size);
 			if (!buf)
-				die(_("unable to read %s"), sha1_to_hex(entry->idx.sha1));
+				die(_("unable to read %s"),
+				    oid_to_hex(&entry->idx.oid));
 		}
 		/*
 		 * make sure no cached delta data remains from a
 		 * previous attempt before a pack split occurred.
 		 */
-		free(entry->delta_data);
-		entry->delta_data = NULL;
+		FREE_AND_NULL(entry->delta_data);
 		entry->z_delta_size = 0;
 	} else if (entry->delta_data) {
 		size = entry->delta_size;
 		buf = entry->delta_data;
 		entry->delta_data = NULL;
 		type = (allow_ofs_delta && entry->delta->idx.offset) ?
