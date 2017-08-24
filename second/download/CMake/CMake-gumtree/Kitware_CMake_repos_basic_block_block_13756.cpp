{
		/* Get next entry in local header offset order. */
		zip->entry = (struct zip_entry *)__archive_rb_tree_iterate(
		    &zip->tree, &zip->entry->node, ARCHIVE_RB_DIR_RIGHT);
	}