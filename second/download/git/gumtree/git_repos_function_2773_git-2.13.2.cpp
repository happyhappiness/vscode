static int which_parent(const unsigned char *sha1, const struct commit *commit)
{
	int nth;
	const struct commit_list *parent;

	for (nth = 0, parent = commit->parents; parent; parent = parent->next) {
		if (!hashcmp(parent->item->object.oid.hash, sha1))
			return nth;
		nth++;
	}
	return -1;
}