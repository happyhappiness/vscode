 	for (i = 0; i < nr_objects; i++) {
 		struct pack_idx_entry *obj = *list++;
 		if (index_version < 2) {
 			uint32_t offset = htonl(obj->offset);
 			sha1write(f, &offset, 4);
 		}
-		sha1write(f, obj->sha1, 20);
+		sha1write(f, obj->oid.hash, 20);
 		if ((opts->flags & WRITE_IDX_STRICT) &&
-		    (i && !hashcmp(list[-2]->sha1, obj->sha1)))
+		    (i && !oidcmp(&list[-2]->oid, &obj->oid)))
 			die("The same object %s appears twice in the pack",
-			    sha1_to_hex(obj->sha1));
+			    oid_to_hex(&obj->oid));
 	}
 
 	if (index_version >= 2) {
 		unsigned int nr_large_offset = 0;
 
 		/* write the crc32 table */
