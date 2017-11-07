static int store_aux(const char *key, const char *value, void *cb)
{
	const char *ep;
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
			store.seen++;
		}
		break;
	case SECTION_SEEN:
		/*
		 * What we are looking for is in store.key (both
		 * section and var), and its section part is baselen
		 * long.  We found key (again, both section and var).
		 * We would want to know if this key is in the same
		 * section as what we are looking for.  We already
		 * know we are in the same section as what should
		 * hold store.key.
		 */
		ep = strrchr(key, '.');
		section_len = ep - key;

		if ((section_len != store.baselen) ||
		    memcmp(key, store.key, section_len+1)) {
			store.state = SECTION_END_SEEN;
			break;
		}

		/*
		 * Do not increment matches: this is no match, but we
		 * just made sure we are in the desired section.
		 */
		ALLOC_GROW(store.offset, store.seen + 1,
			   store.offset_alloc);
		store.offset[store.seen] = cf->do_ftell(cf);
		/* fallthru */
	case SECTION_END_SEEN:
	case START:
		if (matches(key, value)) {
			ALLOC_GROW(store.offset, store.seen + 1,
				   store.offset_alloc);
			store.offset[store.seen] = cf->do_ftell(cf);
			store.state = KEY_SEEN;
			store.seen++;
		} else {
			if (strrchr(key, '.') - key == store.baselen &&
			      !strncmp(key, store.key, store.baselen)) {
					store.state = SECTION_SEEN;
					ALLOC_GROW(store.offset,
						   store.seen + 1,
						   store.offset_alloc);
					store.offset[store.seen] = cf->do_ftell(cf);
			}
		}
	}
	return 0;
}