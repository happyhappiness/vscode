void fast_export_modify(const char *path, uint32_t mode, const char *dataref)
{
	/* Mode must be 100644, 100755, 120000, or 160000. */
	if (!dataref) {
		fast_export_truncate(path, mode);
		return;
	}
	printf("M %06"PRIo32" %s ", mode, dataref);
	quote_c_style(path, NULL, stdout, 0);
	putchar('\n');
}