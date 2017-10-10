		other_branch = ci->branch1;
	}

	add = filespec_from_entry(&other, dst_entry, stage ^ 1);
	if (add) {
		char *add_name = unique_path(o, rename->path, other_branch);
		update_file(o, 0, add->sha1, add->mode, add_name);

		remove_file(o, 0, rename->path, 0);
		dst_name = unique_path(o, rename->path, cur_branch);
	} else {
		if (dir_in_way(rename->path, !o->call_depth)) {
			dst_name = unique_path(o, rename->path, cur_branch);
			output(o, 1, _("%s is a directory in %s adding as %s instead"),
			       rename->path, other_branch, dst_name);
		}
	}
	update_file(o, 0, rename->sha1, rename->mode, dst_name);
	if (stage == 2)
		update_stages(rename->path, NULL, rename, add);
	else
		update_stages(rename->path, NULL, add, rename);

	if (dst_name != rename->path)
		free(dst_name);
}

static void conflict_rename_rename_1to2(struct merge_options *o,
					struct rename_conflict_info *ci)
{
	/* One file was renamed in both branches, but to different names. */
	struct diff_filespec *one = ci->pair1->one;
	struct diff_filespec *a = ci->pair1->two;
	struct diff_filespec *b = ci->pair2->two;
