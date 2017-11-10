static char *keep_pack(const char *curr_index_name)
{
	static const char *keep_msg = "fast-import";
	struct strbuf name = STRBUF_INIT;
	int keep_fd;

	odb_pack_name(&name, pack_data->sha1, "keep");
	keep_fd = odb_pack_keep(name.buf);
	if (keep_fd < 0)
		die_errno("cannot create keep file");
	write_or_die(keep_fd, keep_msg, strlen(keep_msg));
	if (close(keep_fd))
		die_errno("failed to write keep file");

	odb_pack_name(&name, pack_data->sha1, "pack");
	if (finalize_object_file(pack_data->pack_name, name.buf))
		die("cannot store pack file");

	odb_pack_name(&name, pack_data->sha1, "idx");
	if (finalize_object_file(curr_index_name, name.buf))
		die("cannot store index file");
	free((void *)curr_index_name);
	return strbuf_detach(&name, NULL);
}