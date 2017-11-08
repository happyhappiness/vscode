static gid_t map_gid(gid_t id, const char *name)
{
	gid_t gid;
	if (id != 0 && name_to_gid(name, &gid))
		return gid;
	return id;
}