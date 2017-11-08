static int map_gid(int id, char *name)
{
	gid_t gid;
	if (id != 0 && name_to_gid(name, &gid))
		return gid;
	return id;
}