 	if (state->update_index && state->newfd < 0) {
 		if (state->index_file)
 			state->newfd = hold_lock_file_for_update(state->lock_file,
 								 state->index_file,
 								 LOCK_DIE_ON_ERROR);
 		else
-			state->newfd = hold_locked_index(state->lock_file, 1);
+			state->newfd = hold_locked_index(state->lock_file, LOCK_DIE_ON_ERROR);
 	}
 
 	if (state->check_index && read_apply_cache(state) < 0) {
 		error(_("unable to read index file"));
 		res = -128;
 		goto end;
