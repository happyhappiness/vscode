static int gitdiff_oldmode(const char *line, struct patch *patch)
{
	patch->old_mode = strtoul(line, NULL, 8);
	return 0;
}