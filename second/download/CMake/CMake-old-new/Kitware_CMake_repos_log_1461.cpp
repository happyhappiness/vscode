archive_set_error(&a->archive, errno,
			    "Couldn't open %ls", tree_current_path(a->tree));