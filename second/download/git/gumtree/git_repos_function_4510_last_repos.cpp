void argv_array_pop(struct argv_array *array)
{
	if (!array->argc)
		return;
	free((char *)array->argv[array->argc - 1]);
	array->argv[array->argc - 1] = NULL;
	array->argc--;
}