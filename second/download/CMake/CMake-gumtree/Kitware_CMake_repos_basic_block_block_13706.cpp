{
		s = strrchr(str.s, '/');
		if (s == NULL)
			break;
		*s = '\0';
		/* Transfer the parent directory from zip->tree_rsrc RB
		 * tree to zip->tree RB tree to expose. */
		dir = (struct zip_entry *)
		    __archive_rb_tree_find_node(&zip->tree_rsrc, str.s);
		if (dir == NULL)
			break;
		__archive_rb_tree_remove_node(&zip->tree_rsrc, &dir->node);
		archive_string_free(&dir->rsrcname);
		__archive_rb_tree_insert_node(&zip->tree, &dir->node);
	}