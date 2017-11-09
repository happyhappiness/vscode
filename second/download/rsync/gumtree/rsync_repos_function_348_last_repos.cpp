void idev_destroy(void)
{
	int i;

	for (i = 0; i < dev_tbl->size; i++) {
		struct ht_int32_node *node = HT_NODE(dev_tbl, dev_tbl->nodes, i);
		if (node->data)
			hashtable_destroy(node->data);
	}

	hashtable_destroy(dev_tbl);
}