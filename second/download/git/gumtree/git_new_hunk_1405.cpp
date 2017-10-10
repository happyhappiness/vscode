		} else {
			/*
			 * Something went wrong with the protocol filter.
			 * Force shutdown and restart if another blob requires filtering.
			 */
			error("external filter '%s' failed", cmd);
			subprocess_stop(&subprocess_map, &entry->subprocess);
			free(entry);
		}
	} else {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return !err;
