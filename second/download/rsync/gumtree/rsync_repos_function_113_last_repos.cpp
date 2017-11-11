int group_to_gid(const char *name, gid_t *gid_p, BOOL num_ok)
{
	struct group *grp;
	if (!name || !*name)
		return 0;
	if (num_ok && name[strspn(name, "0123456789")] == '\0') {
		*gid_p = id_parse(name);
		return 1;
	}
	if (!(grp = getgrnam(name)))
		return 0;
	*gid_p = grp->gr_gid;
	return 1;
}