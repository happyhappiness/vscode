int do_lchown(const char *path, uid_t owner, gid_t group)
{
	if (dry_run) return 0;
	return lchown(path, owner, group);
}