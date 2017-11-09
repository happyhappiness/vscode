static int exists_in_PATH(const char *file)
{
	char *r = locate_in_PATH(file);
	free(r);
	return r != NULL;
}