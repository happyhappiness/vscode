static int map_uid(int id, char *name)
{
	uid_t uid;
	if (name_to_uid(name, &uid) && uid != 0)
		return uid;
	return id;
}