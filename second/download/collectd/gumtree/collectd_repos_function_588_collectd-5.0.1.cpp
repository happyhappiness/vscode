int read_file_contents (const char *filename, char *buf, int bufsize)
{
	FILE *fh;
	int n;

	if ((fh = fopen (filename, "r")) == NULL)
		return -1;

	n = fread(buf, 1, bufsize, fh);
	fclose(fh);

	return n;
}