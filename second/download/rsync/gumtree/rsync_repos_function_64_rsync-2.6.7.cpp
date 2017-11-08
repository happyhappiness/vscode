static int map_uid(int id, char *name)
{
	uid_t uid;
	if (id != 0 && name_to_uid(name, &uid))
		return uid;
	return id;
}