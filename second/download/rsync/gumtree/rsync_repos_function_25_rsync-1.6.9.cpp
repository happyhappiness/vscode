static int map_gid(int id, char *name)
{
	gid_t gid = name_to_gid(name);
	if (gid != 0) return gid;
	return id;
}