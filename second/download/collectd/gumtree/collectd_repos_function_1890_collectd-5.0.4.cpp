static struct list_head *
iptcc_bsearch_chain_index(const char *name, unsigned int *idx, TC_HANDLE_T handle)
{
	unsigned int pos, end;
	int res;

	struct list_head *list_pos;
	list_pos=&handle->chains;

	/* Check for empty array, e.g. no user defined chains */
	if (handle->chain_index_sz == 0) {
		debug("WARNING: handle->chain_index_sz == 0\n");
		return list_pos;
	}

	/* Init */
	end = handle->chain_index_sz;
	pos = end / 2;

	debug("bsearch Find chain:%s (pos:%d end:%d)\n", name, pos, end);

	/* Loop */
 loop:
	if (!handle->chain_index[pos]) {
		fprintf(stderr, "ERROR: NULL pointer chain_index[%d]\n", pos);
		return &handle->chains; /* Be safe, return orig start pos */
	}

	res = strcmp(name, handle->chain_index[pos]->name);
	list_pos = &handle->chain_index[pos]->list;
	*idx = pos;

	debug("bsearch Index[%d] name:%s res:%d ",
	      pos, handle->chain_index[pos]->name, res);

	if (res == 0) { /* Found element, by direct hit */
		debug("[found] Direct hit pos:%d end:%d\n", pos, end);
		return list_pos;
	} else if (res < 0) { /* Too far, jump back */
		end = pos;
		pos = pos / 2;

		/* Exit case: First element of array */
		if (end == 0) {
			debug("[found] Reached first array elem (end%d)\n",end);
			return list_pos;
		}
		debug("jump back to pos:%d (end:%d)\n", pos, end);
		goto loop;
	} else if (res > 0 ){ /* Not far enough, jump forward */

		/* Exit case: Last element of array */
		if (pos == handle->chain_index_sz-1) {
			debug("[found] Last array elem (end:%d)\n", end);
			return list_pos;
		}

		/* Exit case: Next index less, thus elem in this list section */
		res = strcmp(name, handle->chain_index[pos+1]->name);
		if (res < 0) {
			debug("[found] closest list (end:%d)\n", end);
			return list_pos;
		}

		pos = (pos+end)/2;
		debug("jump forward to pos:%d (end:%d)\n", pos, end);
		goto loop;
	}

	return list_pos;
}