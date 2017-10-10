 		entries[i].sha1 = nth_packed_object_sha1(p, i);
 		if (!entries[i].sha1)
 			die("internal error pack-check nth-packed-object");
 		entries[i].offset = nth_packed_object_offset(p, i);
 		entries[i].nr = i;
 	}
-	qsort(entries, nr_objects, sizeof(*entries), compare_entries);
+	QSORT(entries, nr_objects, compare_entries);
 
 	for (i = 0; i < nr_objects; i++) {
 		void *data;
 		enum object_type type;
 		unsigned long size;
 		off_t curpos;
