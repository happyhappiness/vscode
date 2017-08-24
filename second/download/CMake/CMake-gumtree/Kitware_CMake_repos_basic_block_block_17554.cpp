{
		next = __archive_rb_tree_iterate(&(xar->hardlink_rbtree),
		    n, ARCHIVE_RB_DIR_RIGHT);
		free(n);
		n = next;
	}