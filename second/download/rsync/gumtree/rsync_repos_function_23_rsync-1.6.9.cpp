static gid_t name_to_gid(char *name)
{
	struct group *grp;
	if (!name || !*name) return 0;
	grp = getgrnam(name);
	if (grp) return(grp->gr_gid);
	return 0;
}