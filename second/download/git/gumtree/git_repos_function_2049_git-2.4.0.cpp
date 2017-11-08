int sq_dequote_to_argv_array(char *arg, struct argv_array *array)
{
	return sq_dequote_to_argv_internal(arg, NULL, NULL, NULL, array);
}