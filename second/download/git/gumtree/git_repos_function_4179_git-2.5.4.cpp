static void write_filename_info(const char *path)
{
	printf("filename ");
	write_name_quoted(path, stdout, '\n');
}