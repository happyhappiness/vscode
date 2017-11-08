static void show_file(const char * fmt, const char * name, int in_porcelain,
		      int * first, const char *header_msg)
{
	if (in_porcelain && *first && header_msg) {
		printf("%s\n", header_msg);
		*first = 0;
	}
	printf(fmt, name);
}