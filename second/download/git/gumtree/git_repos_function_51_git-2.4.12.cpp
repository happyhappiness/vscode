struct sha1file *create_tmp_packfile(char **pack_tmp_name)
{
	char tmpname[PATH_MAX];
	int fd;

	fd = odb_mkstemp(tmpname, sizeof(tmpname), "pack/tmp_pack_XXXXXX");
	*pack_tmp_name = xstrdup(tmpname);
	return sha1fd(fd, *pack_tmp_name);
}