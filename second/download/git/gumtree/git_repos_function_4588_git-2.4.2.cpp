static void *get_tree_descriptor(struct tree_desc *desc, const char *rev)
{
	unsigned char sha1[20];
	void *buf;

	if (get_sha1(rev, sha1))
		die("unknown rev %s", rev);
	buf = fill_tree_descriptor(desc, sha1);
	if (!buf)
		die("%s is not a tree", rev);
	return buf;
}