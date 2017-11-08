static struct entry *lookup_entry(unsigned char *sha1)
{
	int low = 0, high = nr_convert;

	while (low < high) {
		int next = (low + high) / 2;
		struct entry *n = convert[next];
		int cmp = hashcmp(sha1, n->old_sha1);
		if (!cmp)
			return n;
		if (cmp < 0) {
			high = next;
			continue;
		}
		low = next+1;
	}
	return insert_new(sha1, low);
}