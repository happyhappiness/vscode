
		if (!(tbl->nodes = new_array0(char, size * tbl->node_size)))
			out_of_memory("hashtable_node");
		tbl->size = size;
		tbl->entries = 0;

		for (i = size / 2; i-- > 0; ) {
			struct ht_int32_node *move_node = HT_NODE(tbl, old_nodes, i);
			int64 move_key = HT_KEY(move_node, key64);
			if (move_key == 0)
				continue;
			node = hashtable_find(tbl, move_key, 1);
