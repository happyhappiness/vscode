write_file(file_name.buf, 1, "gitdir: %s\n",
		   relative_path(git_dir, real_work_tree, &rel_path));