static int write_error(const char *filename)
{
	error("failed to write new configuration file %s", filename);

	/* Same error code as "failed to rename". */
	return 4;
}