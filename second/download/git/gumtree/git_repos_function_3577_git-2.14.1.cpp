static int handle_cache(const char *path, unsigned char *sha1, const char *output)
{
	mmfile_t mmfile[3] = {{NULL}};
	mmbuffer_t result = {NULL, 0};
	const struct cache_entry *ce;
	int pos, len, i, hunk_no;
	struct rerere_io_mem io;
	int marker_size = ll_merge_marker_size(path);

	/*
	 * Reproduce the conflicted merge in-core
	 */
	len = strlen(path);
	pos = cache_name_pos(path, len);
	if (0 <= pos)
		return -1;
	pos = -pos - 1;

	while (pos < active_nr) {
		enum object_type type;
		unsigned long size;

		ce = active_cache[pos++];
		if (ce_namelen(ce) != len || memcmp(ce->name, path, len))
			break;
		i = ce_stage(ce) - 1;
		if (!mmfile[i].ptr) {
			mmfile[i].ptr = read_sha1_file(ce->oid.hash, &type,
						       &size);
			mmfile[i].size = size;
		}
	}
	for (i = 0; i < 3; i++)
		if (!mmfile[i].ptr && !mmfile[i].size)
			mmfile[i].ptr = xstrdup("");

	/*
	 * NEEDSWORK: handle conflicts from merges with
	 * merge.renormalize set, too?
	 */
	ll_merge(&result, path, &mmfile[0], NULL,
		 &mmfile[1], "ours",
		 &mmfile[2], "theirs", NULL);
	for (i = 0; i < 3; i++)
		free(mmfile[i].ptr);

	memset(&io, 0, sizeof(io));
	io.io.getline = rerere_mem_getline;
	if (output)
		io.io.output = fopen(output, "w");
	else
		io.io.output = NULL;
	strbuf_init(&io.input, 0);
	strbuf_attach(&io.input, result.ptr, result.size, result.size);

	/*
	 * Grab the conflict ID and optionally write the original
	 * contents with conflict markers out.
	 */
	hunk_no = handle_path(sha1, (struct rerere_io *)&io, marker_size);
	strbuf_release(&io.input);
	if (io.io.output)
		fclose(io.io.output);
	return hunk_no;
}