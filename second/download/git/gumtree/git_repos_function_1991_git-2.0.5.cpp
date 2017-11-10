void load_ref_decorations(int flags)
{
	static int loaded;
	if (!loaded) {
		loaded = 1;
		for_each_ref(add_ref_decoration, &flags);
		head_ref(add_ref_decoration, &flags);
		for_each_commit_graft(add_graft_decoration, NULL);
	}
}