static void append_one_rev(const char *av)
{
	struct object_id revkey;
	if (!get_sha1(av, revkey.hash)) {
		append_ref(av, &revkey, 0);
		return;
	}
	if (strchr(av, '*') || strchr(av, '?') || strchr(av, '[')) {
		/* glob style match */
		int saved_matches = ref_name_cnt;

		match_ref_pattern = av;
		match_ref_slash = count_slashes(av);
		for_each_ref(append_matching_ref, NULL);
		if (saved_matches == ref_name_cnt &&
		    ref_name_cnt < MAX_REVS)
			error(_("no matching refs with %s"), av);
		sort_ref_range(saved_matches, ref_name_cnt);
		return;
	}
	die("bad sha1 reference %s", av);
}