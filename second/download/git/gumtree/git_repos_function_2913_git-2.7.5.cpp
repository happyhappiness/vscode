static int has_rerere_resolution(const struct rerere_id *id)
{
	struct stat st;

	return !stat(rerere_path(id, "postimage"), &st);
}