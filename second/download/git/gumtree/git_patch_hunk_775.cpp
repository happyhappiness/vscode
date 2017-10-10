 		return;
 	if (remove_or_warn(ce->ce_mode, ce->name))
 		return;
 	schedule_dir_for_removal(ce->name, ce_namelen(ce));
 }
 
-static int check_updates(struct unpack_trees_options *o,
-			 const struct checkout *state)
+static struct progress *get_progress(struct unpack_trees_options *o)
 {
 	unsigned cnt = 0, total = 0;
+	struct index_state *index = &o->result;
+
+	if (!o->update || !o->verbose_update)
+		return NULL;
+
+	for (; cnt < index->cache_nr; cnt++) {
+		const struct cache_entry *ce = index->cache[cnt];
+		if (ce->ce_flags & (CE_UPDATE | CE_WT_REMOVE))
+			total++;
+	}
+
+	return start_progress_delay(_("Checking out files"),
+				    total, 50, 1);
+}
+
+static int check_updates(struct unpack_trees_options *o)
+{
+	unsigned cnt = 0;
+	int errs = 0;
 	struct progress *progress = NULL;
 	struct index_state *index = &o->result;
+	struct checkout state = CHECKOUT_INIT;
 	int i;
-	int errs = 0;
 
-	if (o->update && o->verbose_update) {
-		for (total = cnt = 0; cnt < index->cache_nr; cnt++) {
-			const struct cache_entry *ce = index->cache[cnt];
-			if (ce->ce_flags & (CE_UPDATE | CE_WT_REMOVE))
-				total++;
-		}
+	state.force = 1;
+	state.quiet = 1;
+	state.refresh_cache = 1;
+	state.istate = index;
 
-		progress = start_progress_delay(_("Checking out files"),
-						total, 50, 1);
-		cnt = 0;
-	}
+	progress = get_progress(o);
 
 	if (o->update)
-		git_attr_set_direction(GIT_ATTR_CHECKOUT, &o->result);
+		git_attr_set_direction(GIT_ATTR_CHECKOUT, index);
 	for (i = 0; i < index->cache_nr; i++) {
 		const struct cache_entry *ce = index->cache[i];
 
 		if (ce->ce_flags & CE_WT_REMOVE) {
 			display_progress(progress, ++cnt);
 			if (o->update && !o->dry_run)
 				unlink_entry(ce);
-			continue;
 		}
 	}
-	remove_marked_cache_entries(&o->result);
+	remove_marked_cache_entries(index);
 	remove_scheduled_dirs();
 
 	for (i = 0; i < index->cache_nr; i++) {
 		struct cache_entry *ce = index->cache[i];
 
 		if (ce->ce_flags & CE_UPDATE) {
 			if (ce->ce_flags & CE_WT_REMOVE)
 				die("BUG: both update and delete flags are set on %s",
 				    ce->name);
 			display_progress(progress, ++cnt);
 			ce->ce_flags &= ~CE_UPDATE;
 			if (o->update && !o->dry_run) {
-				errs |= checkout_entry(ce, state, NULL);
+				errs |= checkout_entry(ce, &state, NULL);
 			}
 		}
 	}
 	stop_progress(&progress);
 	if (o->update)
 		git_attr_set_direction(GIT_ATTR_CHECKIN, NULL);
