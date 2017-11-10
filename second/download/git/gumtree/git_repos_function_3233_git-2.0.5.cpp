struct remote *pushremote_get(const char *name)
{
	read_config();
	return remote_get_1(name, pushremote_name);
}