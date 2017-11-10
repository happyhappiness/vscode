int cmd_merge_tree(int argc, const char **argv, const char *prefix)
{
	struct tree_desc t[3];
	void *buf1, *buf2, *buf3;

	if (argc != 4)
		usage(merge_tree_usage);

	buf1 = get_tree_descriptor(t+0, argv[1]);
	buf2 = get_tree_descriptor(t+1, argv[2]);
	buf3 = get_tree_descriptor(t+2, argv[3]);
	merge_trees(t, "");
	free(buf1);
	free(buf2);
	free(buf3);

	show_result();
	return 0;
}