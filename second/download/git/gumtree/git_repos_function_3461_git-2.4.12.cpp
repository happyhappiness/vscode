struct remote *remote_get(const char *name)
{
	read_config();
	return remote_get_1(name, NULL);
}