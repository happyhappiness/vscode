{
			archive_set_error(&a->archive, errno,
			    "Couldn't open %s", tree_current_path(t));
			r = ARCHIVE_FAILED;
			tree_enter_initial_dir(t);
			goto abort_read_data;
		}