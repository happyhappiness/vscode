
		*ent_size = (name - ((char *)ondisk)) + consumed;
	}
	return ce;
}

/* remember to discard_cache() before reading a different cache! */
int do_read_index(struct index_state *istate, const char *path, int must_exist)
{
	int fd, i;
	struct stat st;
	unsigned long src_offset;
