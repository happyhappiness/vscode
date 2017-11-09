void finish_tmp_packfile(struct strbuf *name_buffer,
			 const char *pack_tmp_name,
			 struct pack_idx_entry **written_list,
			 uint32_t nr_written,
			 struct pack_idx_option *pack_idx_opts,
			 unsigned char sha1[])
{
	const char *idx_tmp_name;
	int basename_len = name_buffer->len;

	if (adjust_shared_perm(pack_tmp_name))
		die_errno("unable to make temporary pack file readable");

	idx_tmp_name = write_idx_file(NULL, written_list, nr_written,
				      pack_idx_opts, sha1);
	if (adjust_shared_perm(idx_tmp_name))
		die_errno("unable to make temporary index file readable");

	strbuf_addf(name_buffer, "%s.pack", sha1_to_hex(sha1));

	if (rename(pack_tmp_name, name_buffer->buf))
		die_errno("unable to rename temporary pack file");

	strbuf_setlen(name_buffer, basename_len);

	strbuf_addf(name_buffer, "%s.idx", sha1_to_hex(sha1));
	if (rename(idx_tmp_name, name_buffer->buf))
		die_errno("unable to rename temporary index file");

	strbuf_setlen(name_buffer, basename_len);

	free((void *)idx_tmp_name);
}