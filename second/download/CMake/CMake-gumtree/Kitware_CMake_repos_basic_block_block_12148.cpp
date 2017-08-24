(i = 0; keys[i] != NULL; i++) {
		int l = bid_keycmp(p, keys[i], len);
		if (l > 0)
			return (l);
	}