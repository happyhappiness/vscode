struct userdiff_driver *userdiff_find_by_name(const char *name) {
	int len = strlen(name);
	return userdiff_find_by_namelen(name, len);
}