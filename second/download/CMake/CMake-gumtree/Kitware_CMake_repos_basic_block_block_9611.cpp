(path == NULL || (a->tree != NULL &&
		    a->tree_enter_working_dir(a->tree) != 0))
			path = archive_entry_pathname(entry)