static int write_shallow_commits_1(struct strbuf *out, int use_pack_protocol,
				   const struct sha1_array *extra,
				   unsigned flags)
{
	struct write_shallow_data data;
	int i;
	data.out = out;
	data.use_pack_protocol = use_pack_protocol;
	data.count = 0;
	data.flags = flags;
	for_each_commit_graft(write_one_shallow, &data);
	if (!extra)
		return data.count;
	for (i = 0; i < extra->nr; i++) {
		strbuf_addstr(out, sha1_to_hex(extra->sha1[i]));
		strbuf_addch(out, '\n');
		data.count++;
	}
	return data.count;
}