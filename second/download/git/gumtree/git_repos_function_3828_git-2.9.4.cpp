void argv_array_init(struct argv_array *array)
{
	array->argv = empty_argv;
	array->argc = 0;
	array->alloc = 0;
}