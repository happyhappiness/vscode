static uid_t map_uid(uid_t id, const char *name)
{
	uid_t uid;
	if (id != 0 && name_to_uid(name, &uid))
		return uid;
	return id;
}