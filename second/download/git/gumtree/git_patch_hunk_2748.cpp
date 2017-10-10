 				    (uintmax_t)entries[i].offset);
 		else if (check_sha1_signature(entries[i].sha1, data, size, typename(type)))
 			err = error("packed %s from %s is corrupt",
 				    sha1_to_hex(entries[i].sha1), p->pack_name);
 		else if (fn) {
 			int eaten = 0;
-			fn(entries[i].sha1, type, size, data, &eaten);
+			err |= fn(entries[i].sha1, type, size, data, &eaten);
 			if (eaten)
 				data = NULL;
 		}
 		if (((base_count + i) & 1023) == 0)
 			display_progress(progress, base_count + i);
 		free(data);
