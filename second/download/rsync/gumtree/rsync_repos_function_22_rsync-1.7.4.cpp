static int map_uid(int id, char *name)
{
	uid_t uid = name_to_uid(name);
	if (uid != 0) return uid;
	return id;
}