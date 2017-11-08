const char *rerere_path(const char *hex, const char *file)
{
	return git_path("rr-cache/%s/%s", hex, file);
}