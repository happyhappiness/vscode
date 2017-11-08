struct ht_int64_node *idev_find(int64 dev, int64 ino)
{
	static struct ht_int64_node *dev_node = NULL;
	struct hashtable *tbl;

	if (!dev_node || dev_node->key != dev) {
		/* We keep a separate hash table of inodes for every device. */
		dev_node = hashtable_find(dev_tbl, dev, 1);
		if (!(tbl = dev_node->data))
			tbl = dev_node->data = hashtable_create(512, SIZEOF_INT64 == 8);
	} else
		tbl = dev_node->data;

	return hashtable_find(tbl, ino, 1);
}