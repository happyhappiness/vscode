static int has_rerere_resolution(const char *hex)
{
	struct stat st;
	return !stat(rerere_path(hex, "postimage"), &st);
}