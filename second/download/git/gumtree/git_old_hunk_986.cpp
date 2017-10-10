		}
		strbuf_release(&unquoted);
		strbuf_release(&buf);
	}

	if (split_index > 0) {
		init_split_index(&the_index);
		the_index.cache_changed |= SPLIT_INDEX_ORDERED;
	} else if (!split_index && the_index.split_index) {
		/*
		 * can't discard_split_index(&the_index); because that
		 * will destroy split_index->base->cache[], which may
		 * be shared with the_index.cache[]. So yeah we're
		 * leaking a bit here.
		 */
		the_index.split_index = NULL;
		the_index.cache_changed |= SOMETHING_CHANGED;
	}

	switch (untracked_cache) {
	case UC_UNSPECIFIED:
		break;
	case UC_DISABLE:
