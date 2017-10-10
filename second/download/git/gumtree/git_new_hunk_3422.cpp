		if (dir_in_way(path, !o->call_depth)) {
			char *new_path = unique_path(o, path, add_branch);
			clean_merge = 0;
			output(o, 1, _("CONFLICT (%s): There is a directory with name %s in %s. "
			       "Adding %s as %s"),
			       conf, path, other_branch, path, new_path);
			update_file(o, 0, sha, mode, new_path);
			if (o->call_depth)
				remove_file_from_cache(path);
			free(new_path);
		} else {
			output(o, 2, _("Adding %s"), path);
