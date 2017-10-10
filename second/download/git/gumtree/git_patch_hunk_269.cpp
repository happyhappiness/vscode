 	if ((stages & seen) != stages)
 		return error(_("path '%s' does not have all necessary versions"),
 			     name);
 	return 0;
 }
 
-static int checkout_stage(int stage, struct cache_entry *ce, int pos,
-			  struct checkout *state)
+static int checkout_stage(int stage, const struct cache_entry *ce, int pos,
+			  const struct checkout *state)
 {
 	while (pos < active_nr &&
 	       !strcmp(active_cache[pos]->name, ce->name)) {
 		if (ce_stage(active_cache[pos]) == stage)
 			return checkout_entry(active_cache[pos], state, NULL);
 		pos++;
