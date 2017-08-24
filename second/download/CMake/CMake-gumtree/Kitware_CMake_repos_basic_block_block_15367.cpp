(file->size == 0 && file->dir) {
		if (!__archive_rb_tree_insert_node(&(zip->rbtree),
		    (struct archive_rb_node *)file)) {
			/* We have already had the same file. */
			file_free(file);
			return (ARCHIVE_OK);
		}
	}