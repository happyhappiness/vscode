 			mid = (lo + hi)/2;
 			if (base_offset < obj_list[mid].offset) {
 				hi = mid;
 			} else if (base_offset > obj_list[mid].offset) {
 				lo = mid + 1;
 			} else {
-				hashcpy(base_sha1, obj_list[mid].sha1);
-				base_found = !is_null_sha1(base_sha1);
+				oidcpy(&base_oid, &obj_list[mid].oid);
+				base_found = !is_null_oid(&base_oid);
 				break;
 			}
 		}
 		if (!base_found) {
 			/*
 			 * The delta base object is itself a delta that
 			 * has not been resolved yet.
 			 */
-			hashclr(obj_list[nr].sha1);
-			add_delta_to_list(nr, null_sha1, base_offset, delta_data, delta_size);
+			oidclr(&obj_list[nr].oid);
+			add_delta_to_list(nr, &null_oid, base_offset, delta_data, delta_size);
 			return;
 		}
 	}
 
-	if (resolve_against_held(nr, base_sha1, delta_data, delta_size))
+	if (resolve_against_held(nr, &base_oid, delta_data, delta_size))
 		return;
 
-	base = read_sha1_file(base_sha1, &type, &base_size);
+	base = read_sha1_file(base_oid.hash, &type, &base_size);
 	if (!base) {
 		error("failed to read delta-pack base object %s",
-		      sha1_to_hex(base_sha1));
+		      oid_to_hex(&base_oid));
 		if (!recover)
 			exit(1);
 		has_errors = 1;
 		return;
 	}
 	resolve_delta(nr, type, base, base_size, delta_data, delta_size);
