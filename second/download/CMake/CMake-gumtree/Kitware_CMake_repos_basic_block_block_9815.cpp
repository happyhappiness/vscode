{
#ifdef HAVE_FSTATAT
		if (fstatat(tree_current_dir_fd(t),
		    tree_current_access_path(t), &t->st, 0) != 0)
#else
		if (tree_enter_working_dir(t) != 0)
			return NULL;
		if (stat(tree_current_access_path(t), &t->st) != 0)
#endif
			return NULL;
		t->flags |= hasStat;
	}