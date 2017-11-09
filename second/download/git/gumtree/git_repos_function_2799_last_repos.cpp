int sq_dequote_to_argv(char *arg, const char ***argv, int *nr, int *alloc)
{
	return sq_dequote_to_argv_internal(arg, argv, nr, alloc, NULL);
}