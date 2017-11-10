static int would_lose_untracked(const char *path)
{
	return !was_tracked(path) && file_exists(path);
}