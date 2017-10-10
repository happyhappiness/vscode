 	if (write_locked_index(&result, &lock, COMMIT_LOCK))
 		die ("Could not write temporary index to %s", filename);
 
 	discard_index(&result);
 }
 
-static void stat_patch_list(struct patch *patch)
+static void stat_patch_list(struct apply_state *state, struct patch *patch)
 {
 	int files, adds, dels;
 
 	for (files = adds = dels = 0 ; patch ; patch = patch->next) {
 		files++;
 		adds += patch->lines_added;
 		dels += patch->lines_deleted;
-		show_stats(patch);
+		show_stats(state, patch);
 	}
 
 	print_stat_summary(stdout, files, adds, dels);
 }
 
-static void numstat_patch_list(struct patch *patch)
+static void numstat_patch_list(struct apply_state *state,
+			       struct patch *patch)
 {
 	for ( ; patch; patch = patch->next) {
 		const char *name;
 		name = patch->new_name ? patch->new_name : patch->old_name;
 		if (patch->is_binary)
 			printf("-\t-\t");
 		else
 			printf("%d\t%d\t", patch->lines_added, patch->lines_deleted);
-		write_name_quoted(name, stdout, line_termination);
+		write_name_quoted(name, stdout, state->line_termination);
 	}
 }
 
 static void show_file_mode_name(const char *newdelete, unsigned int mode, const char *name)
 {
 	if (mode)
