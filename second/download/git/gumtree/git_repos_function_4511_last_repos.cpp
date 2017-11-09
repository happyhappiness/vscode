void argv_array_clear(struct argv_array *array)
{
	if (array->argv != empty_argv) {
		int i;
		for (i = 0; i < array->argc; i++)
			free((char *)array->argv[i]);
		free(array->argv);
	}
	argv_array_init(array);
}