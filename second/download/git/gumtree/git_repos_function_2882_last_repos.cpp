void load_ref_decorations(int flags)
{
	if (!decoration_loaded) {

		decoration_loaded = 1;
		decoration_flags = flags;
		for_each_ref(add_ref_decoration, NULL);
		head_ref(add_ref_decoration, NULL);
		for_each_commit_graft(add_graft_decoration, NULL);
	}
}