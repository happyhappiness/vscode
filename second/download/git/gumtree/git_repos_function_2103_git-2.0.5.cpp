static int add_one_reflog(const char *path, const unsigned char *sha1, int flag, void *cb_data)
{
	for_each_reflog_ent(path, add_one_reflog_ent, cb_data);
	return 0;
}