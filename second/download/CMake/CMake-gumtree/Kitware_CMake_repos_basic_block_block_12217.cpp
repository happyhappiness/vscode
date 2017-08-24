{
		while (ht_iter->hashtable_next)
			ht_iter = ht_iter->hashtable_next;
		ht_iter->hashtable_next = entry;
	}