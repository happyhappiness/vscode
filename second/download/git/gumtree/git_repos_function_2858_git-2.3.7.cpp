static void store_pid(const char *path)
{
	FILE *f = fopen(path, "w");
	if (!f)
		die_errno("cannot open pid file '%s'", path);
	if (fprintf(f, "%"PRIuMAX"\n", (uintmax_t) getpid()) < 0 || fclose(f) != 0)
		die_errno("failed to write pid file '%s'", path);
}