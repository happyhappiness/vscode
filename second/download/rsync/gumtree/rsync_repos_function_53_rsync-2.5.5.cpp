static int map_gid(int id, char *name)
{
	gid_t gid;
	if (name_to_gid(name, &gid) && gid != 0)
		return gid;
	return id;
}