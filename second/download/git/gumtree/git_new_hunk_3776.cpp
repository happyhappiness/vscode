		other_branch = ci->branch1;
	}

	add = filespec_from_entry(&other, dst_entry, stage ^ 1);
	if (add) {
		char *add_name = unique_path(o, rename->path, other_branch);
		if (update_file(o, 0, &add->oid, add->mode, add_name))
			return -1;

		remove_file(o, 0, rename->path, 0);
		dst_name = unique_path(o, rename->path, cur_branch);
	} else {
		if (dir_in_way(rename->path, !o->call_depth)) {
			dst_name = unique_path(o, rename->path, cur_branch);
			output(o, 1, _("%s is a directory in %s adding as %s instead"),
			       rename->path, other_branch, dst_name);
		}
	}
	if ((ret = update_file(o, 0, &rename->oid, rename->mode, dst_name)))
		; /* fall through, do allow dst_name to be released */
	else if (stage == 2)
		ret = update_stages(o, rename->path, NULL, rename, add);
	else
		ret = update_stages(o, rename->path, NULL, add, rename);

	if (dst_name != rename->path)
		free(dst_name);

	return ret;
}

static int conflict_rename_rename_1to2(struct merge_options *o,
					struct rename_conflict_info *ci)
{
	/* One file was renamed in both branches, but to different names. */
	struct diff_filespec *one = ci->pair1->one;
	struct diff_filespec *a = ci->pair1->two;
	struct diff_filespec *b = ci->pair2->two;
