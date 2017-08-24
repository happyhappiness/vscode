{
		hl = (struct hardlink *)__archive_rb_tree_find_node(
		    &(xar->hardlink_rbtree), pathname);
		if (hl != NULL) {
			/* Insert `file` entry into the tail. */
			file->hlnext = NULL;
			*hl->file_list.last = file;
			hl->file_list.last = &(file->hlnext);
			hl->nlink++;
		}
		archive_entry_unset_size(file->entry);
	}