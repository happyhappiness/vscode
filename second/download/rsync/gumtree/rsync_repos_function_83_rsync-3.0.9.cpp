static const char *gid_to_name(gid_t gid)
{
	struct group *grp = getgrgid(gid);
	if (grp)
		return strdup(grp->gr_name);
	return NULL;
}