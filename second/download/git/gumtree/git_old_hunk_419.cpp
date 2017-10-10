
		match_ref_pattern = av;
		match_ref_slash = count_slash(av);
		for_each_ref(append_matching_ref, NULL);
		if (saved_matches == ref_name_cnt &&
		    ref_name_cnt < MAX_REVS)
			error("no matching refs with %s", av);
		if (saved_matches + 1 < ref_name_cnt)
			sort_ref_range(saved_matches, ref_name_cnt);
		return;
	}
	die("bad sha1 reference %s", av);
}

static int git_show_branch_config(const char *var, const char *value, void *cb)
