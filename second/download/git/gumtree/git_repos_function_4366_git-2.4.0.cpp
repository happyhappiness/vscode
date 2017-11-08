static int gitdiff_copydst(const char *line, struct patch *patch)
{
	patch->is_copy = 1;
	free(patch->new_name);
	patch->new_name = find_name(line, NULL, p_value ? p_value - 1 : 0, 0);
	return 0;
}