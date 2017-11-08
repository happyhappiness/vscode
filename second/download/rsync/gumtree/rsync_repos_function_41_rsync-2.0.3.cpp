static char *gid_to_name(gid_t gid)
{
	struct group *grp = getgrgid(gid);
	if (grp) return(grp->gr_name);
	return NULL;
}