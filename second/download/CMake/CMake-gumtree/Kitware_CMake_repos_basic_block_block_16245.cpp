{
		/* This `file` is a hardlink target. */
		hl = malloc(sizeof(*hl));
		if (hl == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
			return (ARCHIVE_FATAL);
		}
		hl->nlink = 1;
		/* A hardlink target must be the first position. */
		file->hlnext = NULL;
		hl->file_list.first = file;
		hl->file_list.last = &(file->hlnext);
		__archive_rb_tree_insert_node(&(iso9660->hardlink_rbtree),
		    (struct archive_rb_node *)hl);
	}