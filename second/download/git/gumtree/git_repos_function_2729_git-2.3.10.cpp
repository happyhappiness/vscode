static void ferr_write(const void *p, size_t count, FILE *fp, int *err)
{
	if (!count || *err)
		return;
	if (fwrite(p, count, 1, fp) != 1)
		*err = errno;
}