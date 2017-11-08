static int entry_is_binary(const char *path, const void *buffer, size_t size)
{
	struct userdiff_driver *driver = userdiff_find_by_path(path);
	if (!driver)
		driver = userdiff_find_by_name("default");
	if (driver->binary != -1)
		return driver->binary;
	return buffer_is_binary(buffer, size);
}