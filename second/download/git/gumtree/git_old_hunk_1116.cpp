	}

	hold_lock_file_for_update(&lock, state->fake_ancestor, LOCK_DIE_ON_ERROR);
	res = write_locked_index(&result, &lock, COMMIT_LOCK);
	discard_index(&result);

	 if (res)
		 return error(_("could not write temporary index to %s"),
			      state->fake_ancestor);

	 return 0;
 }

 static void stat_patch_list(struct apply_state *state, struct patch *patch)
 {
	 int files, adds, dels;

	 for (files = adds = dels = 0 ; patch ; patch = patch->next) {
		 files++;
		 adds += patch->lines_added;
		 dels += patch->lines_deleted;
		 show_stats(state, patch);
	 }

	 print_stat_summary(stdout, files, adds, dels);
 }

 static void numstat_patch_list(struct apply_state *state,
				struct patch *patch)
 {
	 for ( ; patch; patch = patch->next) {
		 const char *name;
		 name = patch->new_name ? patch->new_name : patch->old_name;
		 if (patch->is_binary)
			 printf("-\t-\t");
		 else
			 printf("%d\t%d\t", patch->lines_added, patch->lines_deleted);
		 write_name_quoted(name, stdout, state->line_termination);
	 }
 }

 static void show_file_mode_name(const char *newdelete, unsigned int mode, const char *name)
 {
	 if (mode)
		 printf(" %s mode %06o %s\n", newdelete, mode, name);
	 else
		 printf(" %s %s\n", newdelete, name);
 }

 static void show_mode_change(struct patch *p, int show_name)
 {
	 if (p->old_mode && p->new_mode && p->old_mode != p->new_mode) {
		 if (show_name)
			 printf(" mode change %06o => %06o %s\n",
				p->old_mode, p->new_mode, p->new_name);
		 else
			 printf(" mode change %06o => %06o\n",
				p->old_mode, p->new_mode);
	 }
 }

 static void show_rename_copy(struct patch *p)
 {
	 const char *renamecopy = p->is_rename ? "rename" : "copy";
	 const char *old, *new;

	 /* Find common prefix */
	 old = p->old_name;
	 new = p->new_name;
	 while (1) {
		 const char *slash_old, *slash_new;
		 slash_old = strchr(old, '/');
		 slash_new = strchr(new, '/');
		 if (!slash_old ||
		     !slash_new ||
		     slash_old - old != slash_new - new ||
		     memcmp(old, new, slash_new - new))
			 break;
		 old = slash_old + 1;
		 new = slash_new + 1;
	 }
	 /* p->old_name thru old is the common prefix, and old and new
	  * through the end of names are renames
	  */
	 if (old != p->old_name)
		 printf(" %s %.*s{%s => %s} (%d%%)\n", renamecopy,
			(int)(old - p->old_name), p->old_name,
			old, new, p->score);
	 else
		 printf(" %s %s => %s (%d%%)\n", renamecopy,
			p->old_name, p->new_name, p->score);
	 show_mode_change(p, 0);
 }

 static void summary_patch_list(struct patch *patch)
 {
	 struct patch *p;

	 for (p = patch; p; p = p->next) {
		 if (p->is_new)
			 show_file_mode_name("create", p->new_mode, p->new_name);
		 else if (p->is_delete)
			 show_file_mode_name("delete", p->old_mode, p->old_name);
		 else {
			 if (p->is_rename || p->is_copy)
				 show_rename_copy(p);
			 else {
				 if (p->score) {
					 printf(" rewrite %s (%d%%)\n",
						p->new_name, p->score);
					 show_mode_change(p, 0);
				 }
				 else
					 show_mode_change(p, 1);
			 }
		 }
	 }
 }

 static void patch_stats(struct apply_state *state, struct patch *patch)
 {
	 int lines = patch->lines_added + patch->lines_deleted;

	 if (lines > state->max_change)
		 state->max_change = lines;
	 if (patch->old_name) {
		 int len = quote_c_style(patch->old_name, NULL, NULL, 0);
		 if (!len)
			 len = strlen(patch->old_name);
		 if (len > state->max_len)
			 state->max_len = len;
	 }
	 if (patch->new_name) {
		 int len = quote_c_style(patch->new_name, NULL, NULL, 0);
		 if (!len)
			 len = strlen(patch->new_name);
		 if (len > state->max_len)
			 state->max_len = len;
	 }
 }

 static int remove_file(struct apply_state *state, struct patch *patch, int rmdir_empty)
 {
	 if (state->update_index) {
		 if (remove_file_from_cache(patch->old_name) < 0)
			 return error(_("unable to remove %s from index"), patch->old_name);
	 }
	 if (!state->cached) {
		 if (!remove_or_warn(patch->old_mode, patch->old_name) && rmdir_empty) {
			 remove_path(patch->old_name);
		 }
	 }
	 return 0;
 }

 static int add_index_file(struct apply_state *state,
			   const char *path,
			   unsigned mode,
			   void *buf,
			   unsigned long size)
 {
	 struct stat st;
	 struct cache_entry *ce;
	 int namelen = strlen(path);
	 unsigned ce_size = cache_entry_size(namelen);

	 if (!state->update_index)
		 return 0;

	 ce = xcalloc(1, ce_size);
	 memcpy(ce->name, path, namelen);
	 ce->ce_mode = create_ce_mode(mode);
	 ce->ce_flags = create_ce_flags(0);
	 ce->ce_namelen = namelen;
	 if (S_ISGITLINK(mode)) {
		 const char *s;

		 if (!skip_prefix(buf, "Subproject commit ", &s) ||
		     get_oid_hex(s, &ce->oid)) {
			free(ce);
			return error(_("corrupt patch for submodule %s"), path);
		}
	} else {
		if (!state->cached) {
			if (lstat(path, &st) < 0) {
				free(ce);
				return error_errno(_("unable to stat newly "
