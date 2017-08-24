{
	unsigned i;

	if (ids->count + 1 >= ids->size) {
		void *p;

		if (ids->size == 0)
			ids->size = 8;
		else
			ids->size *= 2;
		p = realloc(ids->ids, sizeof(*ids->ids) * ids->size);
		if (p == NULL)
			return (error_nomem(a));
		ids->ids = (int64_t *)p;
	}

	/* Find an insert point. */
	for (i = 0; i < ids->count; i++) {
		if (ids->ids[i] >= id)
			break;
	}

	/* Add owner id. */
	if (i == ids->count)
		ids->ids[ids->count++] = id;
	else if (ids->ids[i] != id) {
		memmove(&(ids->ids[i+1]), &(ids->ids[i]),
		    (ids->count - i) * sizeof(ids->ids[0]));
		ids->ids[i] = id;
		ids->count++;
	}
	a->setflag |= ID_IS_SET;
	return (ARCHIVE_OK);
}