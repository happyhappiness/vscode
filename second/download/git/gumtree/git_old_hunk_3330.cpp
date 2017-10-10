	for (i = 0; worktrees[i]; i++) {
		if (worktrees[i]->is_detached)
			continue;
		if (strcmp(oldref, worktrees[i]->head_ref))
			continue;

		if (set_worktree_head_symref(worktrees[i]->git_dir, newref)) {
			ret = -1;
			error(_("HEAD of working tree %s is not updated"),
			      worktrees[i]->path);
		}
	}

