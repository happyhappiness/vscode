
	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");
	mark_edges_uninteresting(&revs, show_edge);
	traverse_commit_list(&revs, show_commit, show_object, NULL);

	if (keep_unreachable)
		add_objects_in_unpacked_packs(&revs);
	if (unpack_unreachable)
		loosen_unused_packed_objects(&revs);
}

static int option_parse_index_version(const struct option *opt,
				      const char *arg, int unset)
{
	char *c;
