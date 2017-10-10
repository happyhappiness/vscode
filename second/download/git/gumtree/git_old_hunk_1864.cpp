		fprintf(stderr, "ignoring %.4s extension\n", ext);
		break;
	}
	return 0;
}

int read_index(struct index_state *istate)
{
	return read_index_from(istate, get_index_file());
}

static struct cache_entry *cache_entry_from_ondisk(struct ondisk_cache_entry *ondisk,
