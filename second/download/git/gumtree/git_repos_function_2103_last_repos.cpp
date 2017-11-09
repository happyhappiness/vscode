void bitmap_writer_finish(struct pack_idx_entry **index,
			  uint32_t index_nr,
			  const char *filename,
			  uint16_t options)
{
	static uint16_t default_version = 1;
	static uint16_t flags = BITMAP_OPT_FULL_DAG;
	struct strbuf tmp_file = STRBUF_INIT;
	struct sha1file *f;

	struct bitmap_disk_header header;

	int fd = odb_mkstemp(&tmp_file, "pack/tmp_bitmap_XXXXXX");

	f = sha1fd(fd, tmp_file.buf);

	memcpy(header.magic, BITMAP_IDX_SIGNATURE, sizeof(BITMAP_IDX_SIGNATURE));
	header.version = htons(default_version);
	header.options = htons(flags | options);
	header.entry_count = htonl(writer.selected_nr);
	hashcpy(header.checksum, writer.pack_checksum);

	sha1write(f, &header, sizeof(header));
	dump_bitmap(f, writer.commits);
	dump_bitmap(f, writer.trees);
	dump_bitmap(f, writer.blobs);
	dump_bitmap(f, writer.tags);
	write_selected_commits_v1(f, index, index_nr);

	if (options & BITMAP_OPT_HASH_CACHE)
		write_hash_cache(f, index, index_nr);

	sha1close(f, NULL, CSUM_FSYNC);

	if (adjust_shared_perm(tmp_file.buf))
		die_errno("unable to make temporary bitmap file readable");

	if (rename(tmp_file.buf, filename))
		die_errno("unable to rename temporary bitmap file to '%s'", filename);

	strbuf_release(&tmp_file);
}