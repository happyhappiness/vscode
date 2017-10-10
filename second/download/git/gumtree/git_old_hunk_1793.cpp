	size_t section_len;

	switch (store.state) {
	case KEY_SEEN:
		if (matches(key, value)) {
			if (store.seen == 1 && store.multi_replace == 0) {
				warning("%s has multiple values", key);
			}

			ALLOC_GROW(store.offset, store.seen + 1,
				   store.offset_alloc);

			store.offset[store.seen] = cf->do_ftell(cf);
