int name_to_gid(const char *name, gid_t *gid_p)
{
	struct group *grp;
	if (!name || !*name)
		return 0;
	if (!(grp = getgrnam(name)))
		return 0;
	*gid_p = grp->gr_gid;
	return 1;
}