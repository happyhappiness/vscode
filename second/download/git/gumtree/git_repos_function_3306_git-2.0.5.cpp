const char **argv_array_detach(struct argv_array *array, int *argc)
{
	const char **argv =
		array->argv == empty_argv || array->argc == 0 ? NULL : array->argv;
	if (argc)
		*argc = array->argc;
	argv_array_init(array);
	return argv;
}