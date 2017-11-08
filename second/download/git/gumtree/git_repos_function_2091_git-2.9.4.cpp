static int read_one_dir(struct untracked_cache_dir **untracked_,
			struct read_data *rd)
{
	struct untracked_cache_dir ud, *untracked;
	const unsigned char *next, *data = rd->data, *end = rd->end;
	unsigned int value;
	int i, len;

	memset(&ud, 0, sizeof(ud));

	next = data;
	value = decode_varint(&next);
	if (next > end)
		return -1;
	ud.recurse	   = 1;
	ud.untracked_alloc = value;
	ud.untracked_nr	   = value;
	if (ud.untracked_nr)
		ALLOC_ARRAY(ud.untracked, ud.untracked_nr);
	data = next;

	next = data;
	ud.dirs_alloc = ud.dirs_nr = decode_varint(&next);
	if (next > end)
		return -1;
	ALLOC_ARRAY(ud.dirs, ud.dirs_nr);
	data = next;

	len = strlen((const char *)data);
	next = data + len + 1;
	if (next > rd->end)
		return -1;
	*untracked_ = untracked = xmalloc(st_add(sizeof(*untracked), len));
	memcpy(untracked, &ud, sizeof(ud));
	memcpy(untracked->name, data, len + 1);
	data = next;

	for (i = 0; i < untracked->untracked_nr; i++) {
		len = strlen((const char *)data);
		next = data + len + 1;
		if (next > rd->end)
			return -1;
		untracked->untracked[i] = xstrdup((const char*)data);
		data = next;
	}

	rd->ucd[rd->index++] = untracked;
	rd->data = data;

	for (i = 0; i < untracked->dirs_nr; i++) {
		len = read_one_dir(untracked->dirs + i, rd);
		if (len < 0)
			return -1;
	}
	return 0;
}