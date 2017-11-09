struct ht_int64_node *idev_find(int64 dev, int64 ino)
{
	static struct ht_int64_node *dev_node = NULL;
	struct hashtable *tbl;

	/* Note that some OSes have a dev == 0, so increment to avoid storing a 0. */
	if (!dev_node || dev_node->key != dev+1) {
		/* We keep a separate hash table of inodes for every device. */
		dev_node = hashtable_find(dev_tbl, dev+1, 1);
		if (!(tbl = dev_node->data)) {
			tbl = dev_node->data = hashtable_create(512, 1);
			if (DEBUG_GTE(HLINK, 3)) {
				rprintf(FINFO,
				    "[%s] created hashtable for dev %s\n",
				    who_am_i(), big_num(dev));
			}
		}
	} else
		tbl = dev_node->data;

	return hashtable_find(tbl, ino, 1);
}