 	if (final_pack_name != curr_pack_name) {
 		if (!final_pack_name) {
 			snprintf(name, sizeof(name), "%s/pack/pack-%s.pack",
 				 get_object_directory(), sha1_to_hex(sha1));
 			final_pack_name = name;
 		}
-		if (move_temp_to_file(curr_pack_name, final_pack_name))
+		if (finalize_object_file(curr_pack_name, final_pack_name))
 			die(_("cannot store pack file"));
 	} else if (from_stdin)
 		chmod(final_pack_name, 0444);
 
 	if (final_index_name != curr_index_name) {
 		if (!final_index_name) {
 			snprintf(name, sizeof(name), "%s/pack/pack-%s.idx",
 				 get_object_directory(), sha1_to_hex(sha1));
 			final_index_name = name;
 		}
-		if (move_temp_to_file(curr_index_name, final_index_name))
+		if (finalize_object_file(curr_index_name, final_index_name))
 			die(_("cannot store index file"));
 	} else
 		chmod(final_index_name, 0444);
 
 	if (!from_stdin) {
 		printf("%s\n", sha1_to_hex(sha1));
