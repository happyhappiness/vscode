(tree_current_is_dir(t)) {
		tree_push(t, t->basename, t->full_path.s,
		    t->current_filesystem_id,
		    bhfi_dev(&(t->st)), bhfi_ino(&(t->st)),
		    &t->restore_time);
		t->stack->flags |= isDirLink;
	}