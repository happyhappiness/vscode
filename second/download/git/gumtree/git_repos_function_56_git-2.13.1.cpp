struct sha1file *create_tmp_packfile(char **pack_tmp_name)
{
	struct strbuf tmpname = STRBUF_INIT;
	int fd;

	fd = odb_mkstemp(&tmpname, "pack/tmp_pack_XXXXXX");
	*pack_tmp_name = strbuf_detach(&tmpname, NULL);
	return sha1fd(fd, *pack_tmp_name);
}