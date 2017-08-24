{
		tree_push(t, t->basename, t->current_filesystem_id,
		    t->st.st_dev, t->st.st_ino, &t->restore_time);
		t->stack->flags |= isDirLink;
	}