		if (update_file(o, 0, &add->oid, add->mode, add_name))
			return -1;

		remove_file(o, 0, rename->path, 0);
		dst_name = unique_path(o, rename->path, cur_branch);
	} else {
		if (dir_in_way(rename->path, !o->call_depth, 0)) {
			dst_name = unique_path(o, rename->path, cur_branch);
			output(o, 1, _("%s is a directory in %s adding as %s instead"),
			       rename->path, other_branch, dst_name);
		}
	}
	if ((ret = update_file(o, 0, &rename->oid, rename->mode, dst_name)))
