static void create_temp(mmfile_t *src, char *path)
{
	int fd;

	strcpy(path, ".merge_file_XXXXXX");
	fd = xmkstemp(path);
	if (write_in_full(fd, src->ptr, src->size) != src->size)
		die_errno("unable to write temp-file");
	close(fd);
}