static void show_name(FILE *file,
		      const char *prefix, const char *name, int len)
{
	fprintf(file, " %s%-*s |", prefix, len, name);
}