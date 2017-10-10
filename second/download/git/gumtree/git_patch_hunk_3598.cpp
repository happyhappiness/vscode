 	costate.istate = istate;
 	if (checkout_entry(ce, &costate, NULL) || lstat(ce->name, st))
 		return error(_("cannot checkout %s"), ce->name);
 	return 0;
 }
 
-static struct patch *previous_patch(struct patch *patch, int *gone)
+static struct patch *previous_patch(struct apply_state *state,
+				    struct patch *patch,
+				    int *gone)
 {
 	struct patch *previous;
 
 	*gone = 0;
 	if (patch->is_copy || patch->is_rename)
 		return NULL; /* "git" patches do not depend on the order */
 
-	previous = in_fn_table(patch->old_name);
+	previous = in_fn_table(state, patch->old_name);
 	if (!previous)
 		return NULL;
 
 	if (to_be_deleted(previous))
 		return NULL; /* the deletion hasn't happened yet */
 
