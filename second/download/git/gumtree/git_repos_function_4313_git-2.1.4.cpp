static void create_object_directory(void)
{
	const char *object_directory = get_object_directory();
	int len = strlen(object_directory);
	char *path = xmalloc(len + 40);

	memcpy(path, object_directory, len);

	safe_create_dir(object_directory, 1);
	strcpy(path+len, "/pack");
	safe_create_dir(path, 1);
	strcpy(path+len, "/info");
	safe_create_dir(path, 1);

	free(path);
}