static void loose_garbage(const char *path)
{
	if (verbose)
		report_garbage(PACKDIR_FILE_GARBAGE, path);
}