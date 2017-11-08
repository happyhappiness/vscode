int name_to_gid(char *name, gid_t *gid)
{
	struct group *grp;
	if (!name || !*name)
		return 0;
	grp = getgrnam(name);
	if (grp) {
		*gid = grp->gr_gid;
		return 1;
	}
	return 0;
}