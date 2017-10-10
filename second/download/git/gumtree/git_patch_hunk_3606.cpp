 	 * to B and then rename B to A.  While applying the first one,
 	 * the presence of B should not stop A from getting renamed to
 	 * B; ask to_be_deleted() about the later rename.  Removal of
 	 * B and rename from A to B is handled the same way by asking
 	 * was_deleted().
 	 */
-	if ((tpatch = in_fn_table(new_name)) &&
+	if ((tpatch = in_fn_table(state, new_name)) &&
 	    (was_deleted(tpatch) || to_be_deleted(tpatch)))
 		ok_if_exists = 1;
 	else
 		ok_if_exists = 0;
 
 	if (new_name &&
 	    ((0 < patch->is_new) || patch->is_rename || patch->is_copy)) {
-		int err = check_to_create(new_name, ok_if_exists);
+		int err = check_to_create(state, new_name, ok_if_exists);
 
-		if (err && threeway) {
+		if (err && state->threeway) {
 			patch->direct_to_threeway = 1;
 		} else switch (err) {
 		case 0:
 			break; /* happy */
 		case EXISTS_IN_INDEX:
 			return error(_("%s: already exists in index"), new_name);
